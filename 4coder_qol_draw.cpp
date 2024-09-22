function void
qol_draw_hex_color(Application_Links *app, View_ID view, Buffer_ID buffer, Text_Layout_ID text_layout_id){
	Scratch_Block scratch(app);
	Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
	String_Const_u8 buffer_string = push_buffer_range(app, scratch, buffer, visible_range);

	for (i64 i = 0; i+9 < range_size(visible_range); i += 1){
		u8 *str = buffer_string.str+i;
		bool s0 = str[0] != '0';
		bool s1 = str[1] != 'x';
		if (s0 || s1){ continue; }

		b32 all_hex = true;
		for (i64 j = 0; j < 8; j += 1){
			u8 c = str[j+2];
			bool is_digit = '0' <= c && c <= '9';
			bool is_lower = 'a' <= c && c <= 'f';
			bool is_upper = 'A' <= c && c <= 'F';
			if (!(is_digit || is_lower || is_upper)) { all_hex=false; break; }
		}
		if (!all_hex){ continue; }

		i64 pos = visible_range.min + i;
		Rect_f32 r0 = text_layout_character_on_screen(app, text_layout_id, pos+0);
		Rect_f32 r1 = text_layout_character_on_screen(app, text_layout_id, pos+9);
		Rect_f32 rect = rect_inner(rect_union(r0, r1), -1.f);

		ARGB_Color color = ARGB_Color(string_to_integer(SCu8(str+2, 8), 16));
		u32 sum = ((color >> 16) & 0xFF) + ((color >> 8) & 0xFF) + (color & 0xFF);
		ARGB_Color contrast = ARGB_Color(0xFF000000 | (i32(sum > 330)-1));

		draw_rectangle_outline(app, rect_inner(rect, -2.f), 10.f, 4.f, contrast);
		draw_rectangle(app, rect, 8.f, color);
		paint_text_color(app, text_layout_id, Ii64_size(pos, 10), contrast);
		i += 9;
	}
}

function void
qol_draw_cursor_mark(Application_Links *app, View_ID view_id, b32 is_active_view,
					 Buffer_ID buffer, Text_Layout_ID text_layout_id,
					 f32 roundness, f32 outline_thickness){
	b32 has_highlight_range = draw_highlight_range(app, view_id, buffer, text_layout_id, roundness);

	i64 cursor_pos = view_get_cursor_pos(app, view_id);
	i64 mark_pos = view_get_mark_pos(app, view_id);
	Rect_f32 nxt_cursor_rect = text_layout_character_on_screen(app, text_layout_id, cursor_pos);
	Rect_f32 cur_cursor_rect = Rf32_xy_wh(qol_cur_cursor_pos, rect_dim(nxt_cursor_rect));
	if (is_active_view && nxt_cursor_rect.x1 > 0.f){
		qol_nxt_cursor_pos = nxt_cursor_rect.p0;
	}

	if (!has_highlight_range){
		ARGB_Color cl_cursor = fcolor_resolve(fcolor_id(defcolor_cursor, default_cursor_sub_id()));
		if (is_active_view && rect_overlap(nxt_cursor_rect, cur_cursor_rect)){
			// NOTE: Only paint once cursor is overlapping (from Jack Punter)
			paint_text_color_pos(app, text_layout_id, cursor_pos, fcolor_id(defcolor_at_cursor));
		}
		else if (!is_active_view){
			draw_rectangle_outline(app, nxt_cursor_rect, roundness, outline_thickness, cl_cursor);
		}
		draw_character_wire_frame(app, text_layout_id, mark_pos, roundness, outline_thickness, fcolor_id(defcolor_mark));
		draw_rectangle(app, cur_cursor_rect, roundness, cl_cursor);
	}
}

function void
qol_render_buffer(Application_Links *app, View_ID view_id, Face_ID face_id, Buffer_ID buffer, Text_Layout_ID text_layout_id, Rect_f32 rect){
	ProfileScope(app, "qol render buffer");

	View_ID active_view = get_active_view(app, Access_Always);
	b32 is_active_view = (active_view == view_id);
	Rect_f32 prev_clip = draw_set_clip(app, rect);

	Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);

	// NOTE(allen): Cursor shape
	Face_Metrics metrics = get_face_metrics(app, face_id);
	u64 cursor_roundness_100 = def_get_config_u64(app, vars_save_string_lit("cursor_roundness"));
	f32 cursor_roundness = metrics.normal_advance*cursor_roundness_100*0.01f;
	f32 mark_thickness = (f32)def_get_config_u64(app, vars_save_string_lit("mark_thickness"));

	// NOTE(allen): Token colorizing
	Token_Array token_array = get_token_array_from_buffer(app, buffer);
	if (token_array.tokens != 0){
		draw_cpp_token_colors(app, text_layout_id, &token_array);

		// NOTE(allen): Scan for TODOs and NOTEs
		b32 use_comment_keyword = def_get_config_b32(vars_save_string_lit("use_comment_keyword"));
		if (use_comment_keyword){
			Comment_Highlight_Pair pairs[] = {
				{string_u8_litexpr("NOTE"), finalize_color(defcolor_comment_pop, 0)},
				{string_u8_litexpr("TODO"), finalize_color(defcolor_comment_pop, 1)},
			};
			draw_comment_highlights(app, buffer, text_layout_id, &token_array, pairs, ArrayCount(pairs));
		}

#if 0
		// TODO(allen): Put in 4coder_draw.cpp
		// NOTE(allen): Color functions

		Scratch_Block scratch(app);
		ARGB_Color argb = 0xFFFF00FF;

		Token_Iterator_Array it = token_iterator_pos(0, &token_array, visible_range.first);
		for (;;){
			if (!token_it_inc_non_whitespace(&it)){
				break;
			}
			Token *token = token_it_read(&it);
			String_Const_u8 lexeme = push_token_lexeme(app, scratch, buffer, token);
			Code_Index_Note *note = code_index_note_from_string(lexeme);
			if (note != 0 && note->note_kind == CodeIndexNote_Function){
				paint_text_color(app, text_layout_id, Ii64_size(token->pos, token->size), argb);
			}
		}
#endif
	}
	else{
		paint_text_color_fcolor(app, text_layout_id, visible_range, fcolor_id(defcolor_text_default));
	}

	i64 cursor_pos = view_correct_cursor(app, view_id);
	view_correct_mark(app, view_id);

	// NOTE(allen): Scope highlight
	b32 use_scope_highlight = def_get_config_b32(vars_save_string_lit("use_scope_highlight"));
	if (use_scope_highlight){
		Color_Array colors = finalize_color_array(defcolor_back_cycle);
		draw_scope_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
	}

	b32 use_error_highlight = def_get_config_b32(vars_save_string_lit("use_error_highlight"));
	b32 use_jump_highlight = def_get_config_b32(vars_save_string_lit("use_jump_highlight"));
	if (use_error_highlight || use_jump_highlight){
		// NOTE(allen): Error highlight
		String_Const_u8 name = string_u8_litexpr("*compilation*");
		Buffer_ID compilation_buffer = get_buffer_by_name(app, name, Access_Always);
		if (use_error_highlight){
			draw_jump_highlights(app, buffer, text_layout_id, compilation_buffer,
								 fcolor_id(defcolor_highlight_junk));
		}

		// NOTE(allen): Search highlight
		if (use_jump_highlight){
			Buffer_ID jump_buffer = get_locked_jump_buffer(app);
			if (jump_buffer != compilation_buffer){
				draw_jump_highlights(app, buffer, text_layout_id, jump_buffer,
									 fcolor_id(defcolor_highlight_white));
			}
		}
	}

	// NOTE(allen): Color parens
	b32 use_paren_helper = def_get_config_b32(vars_save_string_lit("use_paren_helper"));
	if (use_paren_helper){
		Color_Array colors = finalize_color_array(defcolor_text_cycle);
		draw_paren_highlight(app, buffer, text_layout_id, cursor_pos, colors.vals, colors.count);
	}

	// NOTE(allen): Line highlight
	b32 highlight_line_at_cursor = def_get_config_b32(vars_save_string_lit("highlight_line_at_cursor"));
	if (highlight_line_at_cursor && is_active_view){
		i64 line_number = get_line_number_from_pos(app, buffer, cursor_pos);
		draw_line_highlight(app, text_layout_id, line_number, fcolor_id(defcolor_highlight_cursor_line));
	}

	// NOTE(allen): Whitespace highlight
	b64 show_whitespace = false;
	view_get_setting(app, view_id, ViewSetting_ShowWhitespace, &show_whitespace);
	if (show_whitespace){
		if (token_array.tokens == 0){
			draw_whitespace_highlight(app, buffer, text_layout_id, cursor_roundness);
		}
		else{
			draw_whitespace_highlight(app, text_layout_id, &token_array, cursor_roundness);
		}
	}

	b32 show_hex_colors = def_get_config_b32(vars_save_string_lit("show_hex_colors"));
	if (show_hex_colors){
		qol_draw_hex_color(app, view_id, buffer, text_layout_id);
	}

	// NOTE(allen): Cursor
	switch (fcoder_mode){
		case FCoderMode_Original:
		{
			qol_draw_cursor_mark(app, view_id, is_active_view, buffer, text_layout_id, cursor_roundness, mark_thickness);
		}break;
		case FCoderMode_NotepadLike:
		{
			draw_notepad_style_cursor_highlight(app, view_id, buffer, text_layout_id, cursor_roundness);
		}break;
	}

	// NOTE(allen): Fade ranges
	paint_fade_ranges(app, text_layout_id, buffer);

	// NOTE(allen): put the actual text on the actual screen
	draw_text_layout_default(app, text_layout_id);

	draw_set_clip(app, prev_clip);
}

function void
qol_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id){
	ProfileScope(app, "qol render caller");
	View_ID active_view = get_active_view(app, Access_Always);
	b32 is_active_view = (active_view == view_id);

	Rect_f32 region = draw_background_and_margin(app, view_id, is_active_view);
	Rect_f32 prev_clip = draw_set_clip(app, region);

	Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
	Face_ID face_id = get_face_id(app, buffer);
	Face_Metrics face_metrics = get_face_metrics(app, face_id);
	f32 line_height = face_metrics.line_height;
	f32 digit_advance = face_metrics.decimal_digit_advance;

	// NOTE(allen): file bar
	b64 showing_file_bar = false;
	if (view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) && showing_file_bar){
        b32 on_top = def_get_config_b32(vars_save_string_lit("filebar_on_top"));
		Rect_f32_Pair pair = (on_top ?
                              layout_file_bar_on_top(region, line_height) :
                              layout_file_bar_on_bot(region, line_height));
		draw_file_bar(app, view_id, buffer, face_id, pair.e[1-on_top]);
        region = pair.e[on_top];
    }

	Buffer_Scroll scroll = view_get_buffer_scroll(app, view_id);

	Buffer_Point_Delta_Result delta = delta_apply(app, view_id, frame_info.animation_dt, scroll);
	if (!block_match_struct(&scroll.position, &delta.point)){
		block_copy_struct(&scroll.position, &delta.point);
		view_set_buffer_scroll(app, view_id, scroll, SetBufferScroll_NoCursorChange);
	}
	if (delta.still_animating){
		animate_in_n_milliseconds(app, 0);
	}

	// NOTE(allen): query bars
	region = default_draw_query_bars(app, region, view_id, face_id);

	// NOTE(allen): FPS hud
	if (show_fps_hud){
		Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
		draw_fps_hud(app, frame_info, face_id, pair.max);
		region = pair.min;
		animate_in_n_milliseconds(app, 1000);
	}

	// NOTE(allen): layout line numbers
	b32 show_line_number_margins = def_get_config_b32(vars_save_string_lit("show_line_number_margins"));
	Rect_f32 line_number_rect = {};
	if (show_line_number_margins){
		Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
		line_number_rect = pair.min;
		region = pair.max;
	}
	region = rect_split_left_right(region, 4.f).max;

	// NOTE(allen): begin buffer render
	Buffer_Point buffer_point = scroll.position;
	Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);

	// NOTE(allen): draw line numbers
	if (show_line_number_margins){
		draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
	}

	// NOTE(allen): draw the buffer
	qol_render_buffer(app, view_id, face_id, buffer, text_layout_id, region);

	text_layout_free(app, text_layout_id);
	draw_set_clip(app, prev_clip);
}

function Rect_f32
qol_buffer_region(Application_Links *app, View_ID view_id, Rect_f32 region){
	Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
	Face_ID face_id = get_face_id(app, buffer);
	Face_Metrics metrics = get_face_metrics(app, face_id);
	f32 line_height = metrics.line_height;
	f32 digit_advance = metrics.decimal_digit_advance;

	// NOTE(allen): margins
	region = rect_inner(region, 3.f);

	// NOTE(allen): file bar
	b64 showing_file_bar = false;
	if (view_get_setting(app, view_id, ViewSetting_ShowFileBar, &showing_file_bar) &&
		showing_file_bar){
        b32 on_top = def_get_config_b32(vars_save_string_lit("filebar_on_top"));
		Rect_f32_Pair pair = (on_top ?
                              layout_file_bar_on_top(region, line_height) :
                              layout_file_bar_on_bot(region, line_height));
		region = pair.e[on_top];
	}

	// NOTE(allen): query bars
	{
		Query_Bar *space[32];
		Query_Bar_Ptr_Array query_bars = {};
		query_bars.ptrs = space;
		if (get_active_query_bars(app, view_id, ArrayCount(space), &query_bars)){
			Rect_f32_Pair pair = layout_query_bar_on_top(region, line_height, query_bars.count);
			region = pair.max;
		}
	}

	// NOTE(allen): FPS hud
	if (show_fps_hud){
		Rect_f32_Pair pair = layout_fps_hud_on_bottom(region, line_height);
		region = pair.min;
	}

	// NOTE(allen): line numbers
	b32 show_line_number_margins = def_get_config_b32(vars_save_string_lit("show_line_number_margins"));
	if (show_line_number_margins){
		Rect_f32_Pair pair = layout_line_number_margin(app, buffer, region, digit_advance);
		region = pair.max;
	}
	region = rect_split_left_right(region, 4.f).max;

	return(region);
}
