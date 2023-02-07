
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
