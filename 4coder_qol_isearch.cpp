
// TODO(BYP): regex

function void
qol_isearch(Application_Links *app, Scan_Direction start_scan, i64 first_pos, String_Const_u8 query_init){
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	if (!buffer_exists(app, buffer)){
		return;
	}

	i64 buffer_size = buffer_get_size(app, buffer);

	Query_Bar_Group group(app);
	Query_Bar bar = {};
	if (start_query_bar(app, &bar, 0) == 0){
		return;
	}

	Vec2_f32 old_margin = {};
	Vec2_f32 old_push_in = {};
	view_get_camera_bounds(app, view, &old_margin, &old_push_in);

	Vec2_f32 margin = old_margin;
	margin.y = clamp_bot(200.f, margin.y);
	view_set_camera_bounds(app, view, margin, old_push_in);

	Scan_Direction scan = start_scan;
	i64 pos = first_pos;

	u8 bar_string_space[256];
	bar.string = SCu8(bar_string_space, query_init.size);
	block_copy(bar.string.str, query_init.str, query_init.size);

	String_Const_u8 isearch_str = string_u8_litexpr("I-Search: ");
	String_Const_u8 rsearch_str = string_u8_litexpr("Reverse-I-Search: ");

	u64 match_size = bar.string.size;

	User_Input in = {};
	for (;;){
		bar.prompt = (scan == Scan_Forward ? isearch_str : rsearch_str);
		isearch__update_highlight(app, view, Ii64_size(pos, match_size));

		in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
		if (in.abort){
			break;
		}

		String_Const_u8 string = to_writable(&in);

		b32 string_change = false;
		if (match_key_code(&in, KeyCode_Return) ||
			match_key_code(&in, KeyCode_Tab)){
			Input_Modifier_Set *mods = &in.event.key.modifiers;
			if (has_modifier(mods, KeyCode_Control)){
				bar.string.size = cstring_length(previous_isearch_query);
				block_copy(bar.string.str, previous_isearch_query, bar.string.size);
			}
			else{
				u64 size = bar.string.size;
				size = clamp_top(size, sizeof(previous_isearch_query) - 1);
				block_copy(previous_isearch_query, bar.string.str, size);
				previous_isearch_query[size] = 0;
				break;
			}
		}
		else if (string.str != 0 && string.size > 0){
			String_u8 bar_string = Su8(bar.string, sizeof(bar_string_space));
			string_append(&bar_string, string);
			bar.string = bar_string.string;
			string_change = true;
		}
		else if (match_key_code(&in, KeyCode_Backspace)){
			String_Const_u8 old_string = bar.string;
			b32 mod_ctl = has_modifier(&in.event.key.modifiers, KeyCode_Control);
			b32 mod_sft = has_modifier(&in.event.key.modifiers, KeyCode_Shift);
			if (is_unmodified_key(&in.event)){
				bar.string = backspace_utf8(bar.string);
			}
			else if (mod_ctl && !mod_sft){
				bar.string = qol_ctrl_backspace_string(app, bar.string);
			}
			else if(mod_ctl && mod_sft){
				bar.string.size = 0;
			}
			string_change = (bar.string.size < old_string.size);
		}

		b32 do_scan_action = false;
		b32 do_scroll_wheel = false;
		Scan_Direction change_scan = scan;
		if (!string_change){
			if (match_key_code(&in, KeyCode_PageDown) ||
				match_key_code(&in, KeyCode_Down)){
				change_scan = Scan_Forward;
				do_scan_action = true;
			}
			else if (match_key_code(&in, KeyCode_PageUp) ||
					 match_key_code(&in, KeyCode_Up)){
				change_scan = Scan_Backward;
				do_scan_action = true;
			}
			else{
				// NOTE(allen): is the user trying to execute another command?
				View_Context ctx = view_current_context(app, view);
				Mapping *mapping = ctx.mapping;
				Command_Map *map = mapping_get_map(mapping, ctx.map_id);
				Command_Binding binding = map_get_binding_recursive(mapping, map, &in.event);
				if (binding.custom != 0){
					if (binding.custom == search){
						change_scan = Scan_Forward;
						do_scan_action = true;
					}
					else if (binding.custom == reverse_search){
						change_scan = Scan_Backward;
						do_scan_action = true;
					}
					else{
						Command_Metadata *metadata = get_command_metadata(binding.custom);
						if (metadata != 0){
							if (metadata->is_ui){
								view_enqueue_command_function(app, view, binding.custom);
								break;
							}
						}
						binding.custom(app);
					}
				}
				else{
					leave_current_input_unhandled(app);
				}
			}
		}

		if (string_change){
			switch (scan){
				case Scan_Forward:
				{
					i64 new_pos = 0;
					seek_string_insensitive_forward(app, buffer, pos - 1, 0, bar.string, &new_pos);
					if (new_pos < buffer_size){
						pos = new_pos;
						match_size = bar.string.size;
					}
				}break;

				case Scan_Backward:
				{
					i64 new_pos = 0;
					seek_string_insensitive_backward(app, buffer, pos + 1, 0, bar.string, &new_pos);
					if (new_pos >= 0){
						pos = new_pos;
						match_size = bar.string.size;
					}
				}break;
			}
		}
		else if (do_scan_action){
			scan = change_scan;
			switch (scan){
				case Scan_Forward:
				{
					i64 new_pos = 0;
					seek_string_insensitive_forward(app, buffer, pos, 0, bar.string, &new_pos);
					if (new_pos < buffer_size){
						pos = new_pos;
						match_size = bar.string.size;
					}
				}break;

				case Scan_Backward:
				{
					i64 new_pos = 0;
					seek_string_insensitive_backward(app, buffer, pos, 0, bar.string, &new_pos);
					if (new_pos >= 0){
						pos = new_pos;
						match_size = bar.string.size;
					}
				}break;
			}
		}
		else if (do_scroll_wheel){
			mouse_wheel_scroll(app);
		}
	}

	view_disable_highlight_range(app, view);

	if (in.abort){
		u64 size = bar.string.size;
		size = clamp_top(size, sizeof(previous_isearch_query) - 1);
		block_copy(previous_isearch_query, bar.string.str, size);
		previous_isearch_query[size] = 0;
		view_set_cursor_and_preferred_x(app, view, seek_pos(first_pos));
	}

	view_set_camera_bounds(app, view, old_margin, old_push_in);
}

CUSTOM_COMMAND_SIG(qol_search_identifier)
CUSTOM_DOC("[QOL] I-search identifier under cursor")
{
	Scratch_Block scratch(app);
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	Token_Array array = get_token_array_from_buffer(app, buffer);
	i64 cursor = view_get_cursor_pos(app, view);
	Token *token = get_token_from_pos(app, &array, cursor);
	String_Const_u8 query = push_token_lexeme(app, scratch, buffer, token);
	qol_isearch(app, Scan_Forward, token->pos, query);
}

CUSTOM_COMMAND_SIG(qol_search)
CUSTOM_DOC("[QOL] I-search")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	i64 cursor = view_get_cursor_pos(app, view);
	qol_isearch(app, Scan_Forward, cursor, string_u8_empty);
}