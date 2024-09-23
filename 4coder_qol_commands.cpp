
CUSTOM_COMMAND_SIG(qol_home)
CUSTOM_DOC("[QOL] Seeks the cursor to the beginning of the visual line.")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	seek_pos_of_visual_line(app, Side_Min);
	Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
	scroll.target.pixel_shift.x = 0.f;
	view_set_buffer_scroll(app, view, scroll, SetBufferScroll_NoCursorChange);
}

// TODO(BYP): Currently checks [prj dir, user dir, 4ed dir] in that order
CUSTOM_COMMAND_SIG(qol_reload_config)
CUSTOM_DOC("[QOL] Reloads the config.4coder file")
{
    Scratch_Block scratch(app);
    View_ID view = get_active_view(app, Access_Always);
	Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    String_Const_u8 path = push_buffer_file_name(app, scratch, buffer);
    String_Const_u8 file = string_front_of_path(path);
    if (string_match(file, string_u8_litexpr("config.4coder"))){
        Face_ID face = get_face_id(app, buffer);
        Face_Description desc = get_face_description(app, face);
        load_config_and_apply(app, &global_config_arena, desc.parameters.pt_size, desc.parameters.hinting);
    }
}

CUSTOM_COMMAND_SIG(qol_reload_project)
CUSTOM_DOC("[QOL] Reloads the project.4coder file")
{
    Scratch_Block scratch(app);
	View_ID view = get_active_view(app, Access_Always);
	Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    String_Const_u8 path = push_buffer_file_name(app, scratch, buffer);
    String_Const_u8 file = string_front_of_path(path);
    if (string_match(file, string_u8_litexpr("project.4coder"))){
        File_Name_Data dump = dump_file(scratch, path);
        parse_project(app, scratch, dump);
    }
}

CUSTOM_COMMAND_SIG(qol_reload_bindings)
CUSTOM_DOC("[QOL] Reloads the bindings.4coder file")
{
	Scratch_Block scratch(app);
	View_ID view = get_active_view(app, Access_Always);
	Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    String_Const_u8 path = push_buffer_file_name(app, scratch, buffer);
    String_Const_u8 file = string_front_of_path(path);
	b32 is_bindings = string_match(file, string_u8_litexpr("bindings.4coder"));
	if (is_bindings && dynamic_binding_load_from_path(app, scratch, &framework_mapping, path)){
		String_ID global_map_id = vars_save_string_lit("keys_global");
		String_ID file_map_id = vars_save_string_lit("keys_file");
		String_ID code_map_id = vars_save_string_lit("keys_code");
		qol_setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
	}
}

CUSTOM_COMMAND_SIG(qol_reopen_all_buffers)
CUSTOM_DOC("[QOL] Reloads the project.4coder file")
{
	View_ID views[32];
	Buffer_Scroll scrolls[32];
	i64 count = 0;

	for (View_ID view = get_view_next(app, 0, Access_Always);
		 view != 0;
		 view = get_view_next(app, view, Access_Always)){
		i64 idx = count++;
		views[idx] = view;
		scrolls[idx] = view_get_buffer_scroll(app, view);
	}

	for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Always);
		 buffer != 0;
		 buffer = get_buffer_next(app, buffer, Access_Always)){
		if (buffer_has_name_with_star(app, buffer)){ continue; }
		buffer_reopen(app, buffer, 0);
	}

	for (i64 i = 0; i < count; i += 1){
		view_set_buffer_scroll(app, views[i], scrolls[i], SetBufferScroll_NoCursorChange);
	}
}

CUSTOM_COMMAND_SIG(qol_format_all_buffers)
CUSTOM_DOC("[QOL] Auto-indent and remove blank lines for all loaded buffers")
{
	b32 auto_indent = def_get_config_b32(vars_save_string_lit("automatically_indent_text_on_save"));
	b32 is_virtual = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
	for (Buffer_ID buffer = get_buffer_next(app, 0, Access_ReadWrite);
		 buffer != 0;
		 buffer = get_buffer_next(app, buffer, Access_ReadWrite)){
        if (buffer_has_name_with_star(app, buffer)){ continue; }
		if (auto_indent && is_virtual){
			auto_indent_buffer(app, buffer, buffer_range(app, buffer));
		}
		clean_all_lines_buffer(app, buffer, CleanAllLinesMode_RemoveBlankLines);
	}
	save_all_dirty_buffers(app);
}

CUSTOM_COMMAND_SIG(qol_explorer)
CUSTOM_DOC("[QOL] Opens file explorer in cwd")
{
	Scratch_Block scratch(app);
	String_Const_u8 hot = push_hot_directory(app, scratch);
	String_Const_u8 explorer = def_get_config_string(scratch, vars_save_string_lit("file_explorer_cli"));
	exec_system_command(app, 0, buffer_identifier(0), hot, push_stringf(scratch, "%S .", explorer), 0);
}

function i64
qol_seek_char(Application_Links *app, Buffer_ID buffer, Scan_Direction direction, i64 start_pos, u8 target_char){
	Scratch_Block scratch(app);
	i64 line = get_line_number_from_pos(app, buffer, start_pos);
	Range_i64 range = get_line_pos_range(app, buffer, line);
	String_Const_u8 string = push_buffer_range(app, scratch, buffer, range);
	i64 pos = start_pos;
	while(range_contains(range, pos)){
		pos += direction;
		u8 current_char = string.str[pos - range.min];
		if (current_char == target_char){ return pos; }
	}
	return start_pos;
}

CUSTOM_COMMAND_SIG(qol_char_forward)
CUSTOM_DOC("[QOL] Seeks forward in current line to the selected char")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	i64 cursor_pos = view_get_cursor_pos(app, view);
	i64 pos = qol_seek_char(app, buffer, Scan_Forward, cursor_pos, qol_target_char);
	view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
}

CUSTOM_COMMAND_SIG(qol_char_backward)
CUSTOM_DOC("[QOL] Seeks back in current line to the selected char")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	i64 cursor_pos = view_get_cursor_pos(app, view);
	i64 pos = qol_seek_char(app, buffer, Scan_Backward, cursor_pos, qol_target_char);
	view_set_cursor_and_preferred_x(app, view, seek_pos(pos));
}

CUSTOM_COMMAND_SIG(qol_column_toggle)
CUSTOM_DOC("[QOL] Toggles the column for bumping and selects hovered char")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	if (qol_col_cursor.pos < 0){
		i64 pos = view_get_cursor_pos(app, view);
		qol_target_char = buffer_get_char(app, buffer, pos);
		qol_col_cursor = buffer_compute_cursor(app, buffer, seek_pos(pos));
	}
	else{
		qol_col_cursor.pos = -1;
	}
}

CUSTOM_COMMAND_SIG(qol_write_space)
CUSTOM_DOC("[QOL] Writes as many spaces needed for bumping to column")
{
	Scratch_Block scratch(app);
	if (qol_col_cursor.pos > 0){
		View_ID view = get_active_view(app, Access_ReadVisible);
		Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);

		qol_col_cursor = buffer_compute_cursor(app, buffer, seek_line_col(qol_col_cursor.line, qol_col_cursor.col));

		i64 pos = view_get_cursor_pos(app, view);
		i64 line = get_line_number_from_pos(app, buffer, pos);
		f32 col_x = view_relative_xy_of_pos(app, view, line, qol_col_cursor.pos).x;
		f32 cur_x = view_relative_xy_of_pos(app, view, line, pos).x;
		Face_ID face = get_face_id(app, buffer);
		f32 space_advance = get_face_metrics(app, face).space_advance;

		i64 N = i64((col_x - cur_x) / space_advance);
		if (N < 0){ N = 1; }
		String_Const_u8 spaces = string_const_u8_push(scratch, N);
		block_fill_u8(spaces.str, N, ' ');
		write_text(app, spaces);
	}
	else{
		write_space(app);
	}
}

CUSTOM_COMMAND_SIG(qol_write_text_input)
CUSTOM_DOC("[QOL] Inserts whatever text was used to trigger this command.")
{
	User_Input in = get_current_input(app);
	String_Const_u8 insert = to_writable(&in);
	write_text(app, insert);
	qol_opened_brace = insert.size > 0 && insert.str[0] == '{';
}

CUSTOM_COMMAND_SIG(qol_write_text_and_auto_indent)
CUSTOM_DOC("[QOL] Inserts whatever text was used to trigger this command.")
{
	User_Input in = get_current_input(app);
	String_Const_u8 insert = to_writable(&in);
	write_text_and_auto_indent(app);
	qol_opened_brace = insert.size > 0 && insert.str[0] == '{';
}

CUSTOM_COMMAND_SIG(qol_modal_return)
CUSTOM_DOC("[QOL] Either goto_jump_at_cursor or writes newline and completes {} when appropriate")
{
	View_ID view = get_active_view(app, Access_ReadVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);

	if (buffer == 0){
		buffer = view_get_buffer(app, view, Access_ReadVisible);
		if (buffer != 0){
			goto_jump_at_cursor(app);
			lock_jump_buffer(app, buffer);
		}
	}
	else{
		i64 p0 = view_get_cursor_pos(app, view);
		u8 c = buffer_get_char(app, buffer, p0-1);
		if (qol_opened_brace && c == '{'){
			write_text(app, string_u8_litexpr("\n\n}"));
			i64 p1 = view_get_cursor_pos(app, view);
			view_set_cursor_and_preferred_x(app, view, seek_pos(p0+1));
			auto_indent_buffer(app, buffer, Ii64(p0, p1));
			seek_end_of_line(app);
		}
		else{
			write_text(app, string_u8_litexpr("\n"));
		}
	}
}

function void
qol_move_selection(Application_Links *app, Scan_Direction direction){
	Scratch_Block scratch(app);
	View_ID view = get_active_view(app, Access_ReadWriteVisible);
	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
	i64 max_line = buffer_get_line_count(app, buffer)-1;
	i64 cursor_pos = view_get_cursor_pos(app, view);
	i64 mark_pos = view_get_mark_pos(app, view);
	b32 is_up = direction == Scan_Backward;

	Range_i64 cursor_range = get_line_range_from_pos(app, buffer, cursor_pos);
	Range_i64 mark_range = get_line_range_from_pos(app, buffer, mark_pos);
	Range_i64 range = range_union(cursor_range, mark_range);
	i64 line0 = get_line_number_from_pos(app, buffer, range.min);
	i64 line1 = get_line_number_from_pos(app, buffer, range.max);
	if ((is_up && line0 <= 1) || (!is_up && line1 >= max_line)){ return; }
	range.max += 1 + (buffer_get_char(app, buffer, range.max) == '\r');

	i64 target_pos = is_up ? range.min-1 : range.max+1;
	Range_i64 line_range = get_line_range_from_pos(app, buffer, target_pos);
	target_pos = is_up ? line_range.min : line_range.max + 1;
	i64 diff = direction*(range_size(line_range) + 1);

	String_Const_u8 string_selection = push_buffer_range(app, scratch, buffer, range);
	History_Group group = history_group_begin(app, buffer);
	if (is_up){
		buffer_replace_range(app, buffer, range, string_u8_empty);
		buffer_replace_range(app, buffer, Ii64(target_pos), string_selection);
	}
	else{
		buffer_replace_range(app, buffer, Ii64(target_pos), string_selection);
		buffer_replace_range(app, buffer, range, string_u8_empty);
	}
	cursor_pos += diff;
	mark_pos += diff;
	view_set_cursor_and_preferred_x(app, view, seek_pos(cursor_pos));
	view_set_mark(app, view, seek_pos(mark_pos));
	history_group_end(group);
}

CUSTOM_COMMAND_SIG(qol_move_selection_up)
CUSTOM_DOC("[QOL] Move selected lines up 1 line")
{
	qol_move_selection(app, Scan_Backward);
}

CUSTOM_COMMAND_SIG(qol_move_selection_down)
CUSTOM_DOC("[QOL] Move selected lines down 1 line")
{
	qol_move_selection(app, Scan_Forward);
}
