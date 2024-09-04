
CUSTOM_COMMAND_SIG(qol_home)
CUSTOM_DOC("[QOL] Seeks the cursor to the beginning of the visual line")
{
  View_ID view = get_active_view(app, Access_ReadVisible);
  seek_pos_of_visual_line(app, Side_Min);
  Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
  scroll.target.pixel_shift.x = 0.f;
  view_set_buffer_scroll(app, view, scroll, SetBufferScroll_NoCursorChange);
}

CUSTOM_COMMAND_SIG(qol_scroll_hovered)
CUSTOM_DOC("[QOL] Scrolls hovered view")
{
  Mouse_State mouse = get_mouse_state(app);
  View_ID active_view = get_active_view(app, Access_ReadVisible);
  if (mouse.wheel != 0){
    for (View_ID view = get_view_next(app, 0, Access_ReadVisible);
         view != 0;
         view = get_view_next(app, view, Access_ReadVisible)) {
      Rect_f32 view_rect = view_get_screen_rect(app, view);
      if (rect_contains_point(view_rect, V2f32(mouse.p))){
        Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
        scroll.target = view_move_buffer_point(app, view, scroll.target, V2f32(0.f, (f32)mouse.wheel));
        view_set_buffer_scroll(app, view, scroll, SetBufferScroll_NoCursorChange);
        active_view = view;

        f32 dy = view_point_difference(app, view, scroll.target, scroll.position).y;
        i64 pos = view_get_cursor_pos(app, view);
        Buffer_Cursor cursor = view_compute_cursor(app, view, seek_pos(pos));

        f32 line_height = get_view_line_height(app, view);
        f32 pad = line_height*def_get_config_f32(app, vars_save_string_lit("scroll_margin_y"));
        f32 y = line_height*cursor.line;
        f32 y0 = scroll.position.line_number*line_height - scroll.target.pixel_shift.y;
        f32 y1 = y0 + rect_height(view_get_buffer_region(app, view));
        y0 = y0 + pad + dy;
        y1 = y1 - pad + dy;

        Vec2_f32 delta = V2f32(0,0);
        delta += (y>y0 ? V2f32(0,0) : V2f32(y0-y+line_height, 1));
        delta += (y<y1 ? V2f32(0,0) : V2f32(y1-y-line_height, 1));
        if (delta.y > 0){
          i64 line_delta = i64(delta.x / (delta.y*line_height));
          view_set_cursor(app, view, seek_line_col(cursor.line + line_delta, cursor.col));
        }

        break;
      }
    }
  }
  if (mouse.l){
    no_mark_snap_to_cursor(app, active_view);
  }
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