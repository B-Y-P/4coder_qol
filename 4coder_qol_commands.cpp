
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