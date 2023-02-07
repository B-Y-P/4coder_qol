
function void
qol_tick(Application_Links *app, Frame_Info frame_info){
  default_tick(app, frame_info);

  f32 dt = frame_info.animation_dt;

  qol_interp(qol_cur_cursor_pos, qol_nxt_cursor_pos, dt, 1e-14f);
  if (!near_zero(qol_cur_cursor_pos - qol_nxt_cursor_pos, 0.5f)){
    animate_in_n_milliseconds(app, 0);
  }
}

BUFFER_HOOK_SIG(qol_file_save){
  default_file_save(app, buffer_id);

  Scratch_Block scratch(app);
  String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer_id);
  String_Const_u8 name = string_front_of_path(file_name);

  String_Const_u8 target_prefix = string_u8_litexpr("theme-");
  String_Const_u8 target_suffix = string_u8_litexpr(".4coder");
  String_Const_u8 actual_prefix = string_prefix(name, target_prefix.size);
  String_Const_u8 actual_suffix = string_postfix(name, target_suffix.size);

  if (string_match(actual_prefix, target_prefix) && string_match(actual_suffix, target_suffix)){
    Color_Table color_table = make_color_table(app, &global_theme_arena);
    Config *config = theme_parse__buffer(app, scratch, buffer_id, &global_theme_arena, &color_table);
    String_Const_u8 error_text = config_stringize_errors(app, scratch, config);
    print_message(app, error_text);

    u64 problem_score = 0;
    if (color_table.count < defcolor_line_numbers_text){
      problem_score = defcolor_line_numbers_text - color_table.count;
    }
    for (i32 i = 0; i < color_table.count; i += 1){
      if (color_table.arrays[i].count == 0){
        problem_score += 1;
      }
    }

    if (error_text.size > 0 || problem_score >= 10){
      String_Const_u8 string = push_u8_stringf(scratch, "There appears to be a problem parsing %S; no theme change applied\n", file_name);
      print_message(app, string);
    }
    else{
      name = string_chop(name, 7);
      save_theme(color_table, name);

      Color_Table_Node *node = global_theme_list.last;
      if (node != 0 && string_match(node->name, name)){
        active_color_table = node->table;
      }
    }
  }

  return 0;
}
