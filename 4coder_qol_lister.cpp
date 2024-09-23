
global Lister_Node* g_qol_mouse_node;

function Vec2_i32
qol_lister_grid_dim(Application_Links *app, View_ID view, Lister *lister){
	Face_ID face_id = get_face_id(app, 0);
	Face_Metrics metrics = get_face_metrics(app, face_id);
	Rect_f32 region = view_get_screen_rect(app, view);

	u64 max_size = 0;
	for (i32 i = 0; i < lister->filtered.count; i += 1){
		Lister_Node *node = lister->filtered.node_ptrs[i];
		max_size = Max(max_size, node->string.size);
	}

	f32 f_wid = rect_width(region) / (metrics.normal_advance*f32(max_size + 2));
	i32 wid = clamp(3, i32(f_wid), 5);
	i32 hit = (lister->filtered.count + wid-1) / wid;

	return V2i32(wid, hit);
}

function void
qol_lister_render(Application_Links *app, Frame_Info frame_info, View_ID view){
	Scratch_Block scratch(app);

	Render_Caller_Function *render_caller = (Render_Caller_Function*)get_custom_hook(app, HookID_RenderCaller);
	render_caller(app, frame_info, view);

	g_qol_mouse_node = 0;
	Lister *lister = view_get_lister(app, view);
	if (lister == 0){ return; }
	Rect_f32 region = view_get_screen_rect(app, view);
	Rect_f32 prev_clip = draw_set_clip(app, region);
	b32 is_active_view = (view == get_active_view(app, Access_Always));

	Face_ID face_id = get_face_id(app, 0);
	Face_Metrics metrics = get_face_metrics(app, face_id);
	f32 line_height = metrics.line_height;
	f32 block_height = lister_get_block_height(line_height);
	f32 text_field_height = lister_get_text_field_height(line_height) + 2.f;
	Vec2_i32 grid = qol_lister_grid_dim(app, view, lister);
	f32 block_width = rect_width(region) / f32(grid.x);

	{
		Rect_f32_Pair pair = rect_split_top_bottom(region, 0.5f*rect_height(region));
		draw_rectangle(app, pair.min, 0.f, 0x55000000);
		draw_rectangle(app, pair.max, 0.f, fcolor_resolve(fcolor_id(defcolor_margin_active)));
		region = rect_inner(pair.max, 3.f);
		draw_rectangle_fcolor(app, region, 0.f, fcolor_id(defcolor_back));
	}

	// NOTE(allen): file bar
	// TODO(allen): What's going on with 'showing_file_bar'? I found it like this.
	b64 showing_file_bar = false;
	b32 hide_file_bar_in_ui = def_get_config_b32(vars_save_string_lit("hide_file_bar_in_ui"));
	if (view_get_setting(app, view, ViewSetting_ShowFileBar, &showing_file_bar) &&
		showing_file_bar && !hide_file_bar_in_ui){
		Rect_f32_Pair pair = layout_file_bar_on_bot(region, line_height);
		Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
		draw_file_bar(app, view, buffer, face_id, pair.max);
		region = pair.min;
	}

	Mouse_State mouse = get_mouse_state(app);
	Vec2_f32 m_p = V2f32(mouse.p);
	Vec2_f32 cursor_pos = {};

	Rect_f32 text_field_rect = {};
	Rect_f32 list_rect = {};
	{
		Rect_f32_Pair pair = rect_split_top_bottom_neg(region, text_field_height);
		text_field_rect = pair.max;
		list_rect = pair.min;
	}

	{
		Vec2_f32 p = V2f32(text_field_rect.x0 + 3.f, text_field_rect.y0);
		Fancy_Line text_field = {};
		push_fancy_string(scratch, &text_field, fcolor_id(defcolor_pop1), lister->query.string);
		push_fancy_stringf(scratch, &text_field, " ");
		p = draw_fancy_line(app, face_id, fcolor_zero(), &text_field, p);

		// TODO(allen): This is a bit of a hack. Maybe an upgrade to fancy to focus
		// more on being good at this and less on overriding everything 10 ways to sunday
		// would be good.
		block_zero_struct(&text_field);
		push_fancy_string(scratch, &text_field, fcolor_id(defcolor_text_default),
						  lister->text_field.string);
		f32 width = get_fancy_line_width(app, face_id, &text_field);
		f32 cap_width = text_field_rect.x1 - p.x - 6.f;
		if (cap_width < width){
			Rect_f32 prect = draw_set_clip(app, Rf32(p.x, text_field_rect.y0, p.x + cap_width, text_field_rect.y1));
			p.x += cap_width - width;
			cursor_pos = draw_fancy_line(app, face_id, fcolor_zero(), &text_field, p);
			draw_set_clip(app, prect);
		}
		else{
			cursor_pos = draw_fancy_line(app, face_id, fcolor_zero(), &text_field, p);
		}
		if (is_active_view){
			qol_nxt_cursor_pos = cursor_pos;
		}
	}

	draw_set_clip(app, list_rect);

	lister->visible_count = grid.x*(i32)(rect_height(list_rect)/block_height);
	lister->visible_count = clamp_bot(1, lister->visible_count);

	i32 count = lister->filtered.count;
	f32 scroll_y = lister->scroll.position.y;
	f32 scroll_h = grid.y*block_height;
	f32 view_h = rect_height(list_rect);
	Range_f32 scroll_range = If32(0.f, scroll_h);

	// NOTE(allen): auto scroll to the item if the flag is set.
	if (lister->set_vertical_focus_to_item){
		lister->set_vertical_focus_to_item = false;
		i32 yi = (lister->item_index / grid.x);
		f32 item_center = (yi + 0.5f)*block_height;
		lister->scroll.target.y = item_center - 0.5f*view_h;
	}

	// NOTE(allen): clamp scroll target and position; smooth scroll rule
	lister->scroll.target.y = clamp_range(scroll_range, lister->scroll.target.y);
	lister->scroll.target.x = 0.f;

	Vec2_f32_Delta_Result delta = delta_apply(app, view, frame_info.animation_dt, lister->scroll);
	lister->scroll.position = delta.p;
	if (delta.still_animating){
		animate_in_n_milliseconds(app, 0);
	}

	lister->scroll.position.y = clamp_range(scroll_range, lister->scroll.position.y);
	lister->scroll.position.x = 0.f;

	scroll_y = lister->scroll.position.y;
	f32 y_pos = list_rect.y0 - scroll_y;
	i32 xi = grid.x-1;

	i32 first_index = (i32)(scroll_y/block_height);
	y_pos += first_index*block_height;
	first_index *= grid.x;

	Fancy_Block block = {};
	for (i32 i = first_index; i < count; i += 1){
		Lister_Node *node = lister->filtered.node_ptrs[i];

		if (y_pos >= region.y1){ break; }
		xi = i % grid.x;
		f32 x_pos = list_rect.x0 + xi*block_width;

		Rect_f32 item_rect = Rf32_xy_wh(x_pos, y_pos, block_width, block_height);
		Rect_f32 item_inner = rect_inner(item_rect, 3.f);
		y_pos += block_height*(xi == grid.x-1);

		b32 hovered = rect_contains_point(item_rect, m_p);
		UI_Highlight_Level highlight = UIHighlight_None;
		if (node == lister->highlighted_node){
			highlight = UIHighlight_Active;
		}
		else if (node->user_data == lister->hot_user_data){
			highlight = (hovered ? UIHighlight_Active : UIHighlight_Hover);
		}
		else if (hovered){
			highlight = UIHighlight_Hover;
		}

		if (hovered){
			g_qol_mouse_node = node;
			Fancy_Line *line1 = push_fancy_line(scratch, &block, face_id);
			u64 index = string_find_last(node->status, '\n');

			if(index < node->status.size){
				push_fancy_string(scratch, line1, fcolor_id(defcolor_pop2), string_prefix(node->status, index));
				Fancy_Line *line2 = push_fancy_line(scratch, &block, face_id);
				push_fancy_string(scratch, line2, fcolor_id(defcolor_text_default), string_postfix(node->status, node->status.size-1 - index));
			}else{
				push_fancy_string(scratch, line1, fcolor_id(defcolor_pop2), node->status);
			}
		}

		u64 lister_roundness_100 = def_get_config_u64(app, vars_save_string_lit("lister_roundness"));
		f32 roundness = block_height*lister_roundness_100*0.01f;
		draw_rectangle_fcolor(app, item_rect, roundness, get_item_margin_color(highlight, 1));

		Fancy_Line line = {};
		push_fancy_string(scratch, &line, fcolor_id(defcolor_text_default), node->string);
		push_fancy_stringf(scratch, &line, " ");
		push_fancy_string(scratch, &line, fcolor_id(defcolor_pop2), node->status);

		Vec2_f32 p = item_inner.p0 + V2f32(3.f, (block_height - line_height)*0.5f);
		draw_fancy_line(app, face_id, fcolor_zero(), &line, p);

		draw_rectangle_outline_fcolor(app, item_rect, roundness, 5.f, get_item_margin_color(highlight));
	}

	if (xi != grid.x-1){
		f32 x_pos = (xi+1)*block_width;
		Rect_f32 cover_rect = Rf32(x_pos, y_pos+3.f, list_rect.x1, y_pos+block_height);
		draw_rectangle_fcolor(app, cover_rect, 0.f, fcolor_id(defcolor_back));
	}

	if (g_qol_mouse_node){
		f32 x_padding = metrics.normal_advance;
		f32 x_half_padding = x_padding*0.5f;
		draw_drop_down(app, face_id, &block, m_p, region, x_padding, x_half_padding, fcolor_id(defcolor_margin_hover), fcolor_id(defcolor_back));
	}

	{
		draw_set_clip(app, region);
		f32 line_diff = abs_f32(qol_cur_cursor_pos.y - cursor_pos.y)/line_height;
		f32 interp_t = unlerp(2.f, line_diff, 8.f);
		f32 cursor_wid = lerp(2.f, cubic_reinterpolate(clamp(0.f, interp_t, 1.f)), metrics.normal_advance);
		Rect_f32 cursor_rect = Rf32_xy_wh(qol_cur_cursor_pos, V2f32(cursor_wid, line_height));
		Rect_f32 dividor_rect = rect_split_top_bottom_neg(list_rect, 2.f).max;
		draw_rectangle_fcolor(app, cursor_rect, 0.f, fcolor_id(defcolor_cursor, 0));
		draw_rectangle_fcolor(app, dividor_rect, 0.f, get_item_margin_color(UIHighlight_Active));
	}

	draw_set_clip(app, prev_clip);
}

function void
qol_lister__backspace_text_field__default(Application_Links *app){
	View_ID view = get_active_view(app, Access_Always);
	Lister *lister = view_get_lister(app, view);
	User_Input input = get_current_input(app);
	b32 mod_ctl = has_modifier(&input, KeyCode_Control);
	b32 mod_sft = has_modifier(&input, KeyCode_Shift);
	if (lister != 0){
		lister->text_field.string = (mod_ctl &&  mod_sft ? string_prefix(lister->text_field.string, 0) :
									 mod_ctl && !mod_sft ? qol_ctrl_backspace_string(app, lister->text_field.string) :
									 backspace_utf8(lister->text_field.string));
		lister->key_string.string = (mod_ctl &&  mod_sft ? string_prefix(lister->key_string.string, 0) :
									 mod_ctl && !mod_sft ? qol_ctrl_backspace_string(app, lister->key_string.string) :
									 backspace_utf8(lister->key_string.string));
		lister->item_index = 0;
		lister_zero_scroll(lister);
		lister_update_filtered_list(app, lister);
    }
}

function void
qol_lister__backspace_text_field__file_path(Application_Links *app){
	View_ID view = get_this_ctx_view(app, Access_Always);
	Lister *lister = view_get_lister(app, view);
	User_Input input = get_current_input(app);
	b32 mod_ctl = has_modifier(&input, KeyCode_Control);
	b32 mod_sft = has_modifier(&input, KeyCode_Shift);
	if (lister != 0){
		if (lister->text_field.size > 0){
			String_Const_u8 string = lister->text_field.string;
			char last_char = string.str[string.size - 1];
			lister->text_field.string = (mod_ctl &&  mod_sft ? string_prefix(string, string_find_first_slash(string)) :
										 mod_ctl && !mod_sft ? qol_ctrl_backspace_string(app, string) :
										 backspace_utf8(string));
			if (character_is_slash(last_char)){
				String_Const_u8 text_field = lister->text_field.string;
				String_Const_u8 new_hot = string_remove_last_folder(text_field);
				b32 use_mod_ctl = def_get_config_b32(vars_save_string_lit("lister_whole_word_backspace_when_modified"));
				if (use_mod_ctl && (mod_ctl && !mod_sft)){
					lister->text_field.size = new_hot.size;
				}
				set_hot_directory(app, new_hot);
				// TODO(allen): We have to protect against lister_call_refresh_handler
				// changing the text_field here. Clean this up.
				String_u8 dingus = lister->text_field;
				lister_call_refresh_handler(app, lister);
				lister->text_field = dingus;
			}
			else{
				String_Const_u8 text_field = lister->text_field.string;
				String_Const_u8 new_key = string_front_of_path(text_field);
				lister_set_key(lister, new_key);
			}

			lister->item_index = 0;
			lister_zero_scroll(lister);
			lister_update_filtered_list(app, lister);
		}
    }
}

function Custom_Command_Function*
qol_lister_backspace_replace(Custom_Command_Function *func){
	return (func == lister__backspace_text_field__default   ? qol_lister__backspace_text_field__default   :
			func == lister__backspace_text_field__file_path ? qol_lister__backspace_text_field__file_path : func);
}

function Lister_Result
qol_run_lister(Application_Links *app, Lister *lister){
	lister->handlers.backspace = qol_lister_backspace_replace(lister->handlers.backspace);
	lister->filter_restore_point = begin_temp(lister->arena);
	lister_update_filtered_list(app, lister);

	View_ID view = get_this_ctx_view(app, Access_Always);
	View_Context ctx = view_current_context(app, view);
	ctx.render_caller = qol_lister_render;
	ctx.hides_buffer = true;
	View_Context_Block ctx_block(app, view, &ctx);

	for (;;){
		User_Input in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
		if (in.abort){
			block_zero_struct(&lister->out);
			lister->out.canceled = true;
			break;
		}

		Vec2_i32 grid = qol_lister_grid_dim(app, view, lister);

		Lister_Activation_Code result = ListerActivation_Continue;
		b32 handled = true;
		switch (in.event.kind){
			case InputEventKind_TextInsert:{
				if (lister->handlers.write_character != 0){
					result = lister->handlers.write_character(app);
				}
			}break;

			case InputEventKind_KeyStroke:{
				Key_Code code = in.event.key.code;
				switch (code){
					case KeyCode_Return:{
						void *user_data = 0;
						if (0 <= lister->raw_item_index &&
							lister->raw_item_index < lister->options.count){
							user_data = lister_get_user_data(lister, lister->raw_item_index);
						}
						lister_activate(app, lister, user_data, false);
						result = ListerActivation_Finished;
					}break;

					case KeyCode_Backspace:{
						if (lister->handlers.backspace != 0){
							lister->handlers.backspace(app);
						}
						else if (lister->handlers.key_stroke != 0){
							result = lister->handlers.key_stroke(app);
						}
						else{
							handled = false;
						}
					}break;

					case KeyCode_Tab:{
						if (lister->handlers.navigate != 0){
							i32 delta = (has_modifier(&in.event.key.modifiers, KeyCode_Shift) ? -1 : 1);
							lister->handlers.navigate(app, view, lister, delta);
						}
					}break;

					case KeyCode_PageUp:
					case KeyCode_PageDown:
					case KeyCode_Up:
					case KeyCode_Down:
					case KeyCode_Left:
					case KeyCode_Right:{
						if (lister->handlers.navigate != 0){
							i32 delta = (code == KeyCode_PageUp   ? -lister->visible_count :
										 code == KeyCode_PageDown ?  lister->visible_count :
										 code == KeyCode_Up       ? -grid.x :
										 code == KeyCode_Down     ?  grid.x :
										 code == KeyCode_Left     ? -1 :
										 code == KeyCode_Right    ?  1 : 0);
							lister->handlers.navigate(app, view, lister, delta);
						}
						else if (lister->handlers.key_stroke != 0){
							result = lister->handlers.key_stroke(app);
						}
						else{
							handled = false;
						}
					}break;

					default:{
						if (lister->handlers.key_stroke != 0){
							result = lister->handlers.key_stroke(app);
						}
						else{
							handled = false;
						}
					}break;
				}
			}break;

			case InputEventKind_MouseButton:{
				switch (in.event.mouse.code){
					case MouseCode_Left:{
						Vec2_f32 p = V2f32(in.event.mouse.p);
						void *clicked = lister_user_data_at_p(app, view, lister, p);
						lister->hot_user_data = clicked;
					}break;

					default:{ handled = false; }break;
				}
			}break;

			case InputEventKind_MouseButtonRelease:{
				switch (in.event.mouse.code){
					case MouseCode_Left:{
						if (g_qol_mouse_node){
							lister_activate(app, lister, g_qol_mouse_node->user_data, true);
							result = ListerActivation_Finished;
						}
						lister->hot_user_data = 0;
					}break;

					default:{ handled = false; }break;
				}
			}break;

			case InputEventKind_MouseWheel:{
				Mouse_State mouse = get_mouse_state(app);
				lister->scroll.target.y += mouse.wheel;
				lister_update_filtered_list(app, lister);
			}break;

			case InputEventKind_MouseMove:{
				lister_update_filtered_list(app, lister);
			}break;

			case InputEventKind_Core:{
				switch (in.event.core.code){
					case CoreCode_Animate:{
						lister_update_filtered_list(app, lister);
					}break;

					default:{ handled = false; }break;
				}
			}break;

			default:{ handled = false; }break;
		}

		if (result == ListerActivation_Finished){
			break;
		}

		if (!handled){
			Mapping *mapping = lister->mapping;
			Command_Map *map = lister->map;

			Fallback_Dispatch_Result disp_result =
				fallback_command_dispatch(app, mapping, map, &in);
			if (disp_result.code == FallbackDispatch_DelayedUICall){
				call_after_ctx_shutdown(app, view, disp_result.func);
				break;
			}
			if (disp_result.code == FallbackDispatch_Unhandled){
				leave_current_input_unhandled(app);
			}
			else{
				lister_call_refresh_handler(app, lister);
			}
		}
	}

	return lister->out;
}