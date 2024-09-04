
CUSTOM_COMMAND_SIG(qol_startup)
CUSTOM_DOC("QOL command for responding to a startup event")
{
  ProfileScope(app, "qol startup");
  User_Input input = get_current_input(app);
  if (match_core_code(&input, CoreCode_Startup)){
    String_Const_u8_Array file_names = input.event.core.file_names;
    load_themes_default_folder(app);
    default_4coder_initialize(app, file_names);
    default_4coder_side_by_side_panels(app, file_names);

    /// NOTE(BYP): Not ideal, but I'd rather simplify others testing 4coder_qol
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
    qol_setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);

    b32 auto_load = def_get_config_b32(vars_save_string_lit("automatically_load_project"));
    if (auto_load){
      load_project(app);
    }
  }

  {
    def_audio_init();
  }

  {
    def_enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
    clear_all_layouts(app);
  }

  Scratch_Block scratch(app);
  set_active_color(get_color_table_by_name(def_get_config_string(scratch, vars_save_string_lit("default_theme_name"))));
  qol_cur_colors = qol_color_table_init(app);
  qol_nxt_colors = qol_color_table_init(app);
  qol_color_table_copy(qol_cur_colors, active_color_table);
  qol_color_table_copy(qol_nxt_colors, active_color_table);
}

function void
qol_tick(Application_Links *app, Frame_Info frame_info){
  default_tick(app, frame_info);

  f32 dt = frame_info.animation_dt;

  qol_interp(qol_cur_cursor_pos, qol_nxt_cursor_pos, dt, 1e-14f);
  if (!near_zero(qol_cur_cursor_pos - qol_nxt_cursor_pos, 0.5f)){
    animate_in_n_milliseconds(app, 0);
  }

  qol_tick_colors(app, frame_info);
}

BUFFER_HOOK_SIG(qol_file_save){
  default_file_save(app, buffer_id);

  Scratch_Block scratch(app);
  String_Const_u8 path = push_buffer_file_name(app, scratch, buffer_id);
  String_Const_u8 name = string_front_of_path(path);

  if (qol_is_theme_file(name)){
    Color_Table color_table = make_color_table(app, &global_theme_arena);
    Config *config = theme_parse__buffer(app, scratch, buffer_id, &global_theme_arena, &color_table);
    String_Const_u8 error_text = config_stringize_errors(app, scratch, config);
    comp_error(app, error_text);

    if (error_text.size > 0){
      print_message(app, error_text);
    }
    else{
      qol_color_table_copy(qol_nxt_colors, color_table);
    }
  }

  if (string_match(name, string_u8_litexpr("config.4coder"))){
    View_ID view = get_active_view(app, Access_Always);
    view_enqueue_command_function(app, view, qol_reload_config);
  }

  if (string_match(name, string_u8_litexpr("project.4coder"))){
    View_ID view = get_active_view(app, Access_Always);
    view_enqueue_command_function(app, view, qol_reload_project);
  }

  if (string_match(name, string_u8_litexpr("bindings.4coder"))){
    View_ID view = get_active_view(app, Access_Always);
    view_enqueue_command_function(app, view, qol_reload_bindings);
  }

  return 0;
}
