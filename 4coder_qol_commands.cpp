
CUSTOM_COMMAND_SIG(qol_clear_jumps)
CUSTOM_DOC("[QOL] Clears any jump highlights")
{
  unlock_jump_buffer();
}

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

CUSTOM_COMMAND_SIG(qol_loc)
CUSTOM_DOC("[QOL] Prints Lines of Code")
{
  i64 loc = 0;
  Command_Map_ID code_map_id = vars_save_string_lit("keys_code");
  for (Buffer_ID buffer = get_buffer_next(app, 0, Access_Read);
       buffer != 0;
       buffer = get_buffer_next(app, buffer, Access_Read)){
    Managed_Scope scope = buffer_get_managed_scope(app, buffer);
    Command_Map_ID *map_id_ptr = scope_attachment(app, scope, buffer_map_id, Command_Map_ID);
    if (map_id_ptr != 0 && *map_id_ptr == code_map_id){
      loc += buffer_get_line_count(app, buffer);
    }
  }
  printf_message(app, "LOC: %'lld lines\n", loc);
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
  range.max += 1;
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
  View_ID view = get_active_view(app, Access_ReadWriteVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
  i64 max_line = buffer_get_line_count(app, buffer)-1;
  i64 cursor_pos = view_get_cursor_pos(app, view);
  i64 mark_pos = view_get_mark_pos(app, view);
  b32 is_up = direction == Scan_Backward;

  Range_i64 range = range_union(get_line_range_from_pos(app, buffer, cursor_pos),
                                get_line_range_from_pos(app, buffer, mark_pos));
  i64 line0 = get_line_number_from_pos(app, buffer, range.min);
  i64 line1 = get_line_number_from_pos(app, buffer, range.max);
  if ((is_up && line0 <= 1) || (!is_up && line1 >= max_line)){ return; }
  range.max += 1 + (buffer_get_char(app, buffer, range.max) == '\r');

  i64 target_pos = (is_up ?
                    get_line_pos_range(app, buffer, line0 - 1).min :
                    get_line_pos_range(app, buffer, line1 + 1).max + 1);

  Scratch_Block scratch(app);
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
  i64 offset = target_pos - (is_up ? range.min : range.max);
  view_set_cursor_and_preferred_x(app, view, seek_pos(cursor_pos + offset));
  view_set_mark(app, view, seek_pos(mark_pos + offset));
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

function void
qol_find_divider(Application_Links *app, Scan_Direction direction){
  View_ID view = get_active_view(app, Access_ReadVisible);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  Token_Array tokens = get_token_array_from_buffer(app, buffer);
  if (tokens.tokens == 0){ return; }

  i64 pos = view_get_cursor_pos(app, view);
  Token_Iterator_Array it = token_iterator_pos(buffer, &tokens, pos);
  for (;;){
    Scratch_Block scratch(app);
    Token *token = token_it_read(&it);

    b32 correct_direction = ((token->pos < pos && direction == Scan_Backward) ||
                             (token->pos > pos && direction == Scan_Forward));

    String_Const_u8 tail = {};
    if (correct_direction && token_it_check_and_get_lexeme(app, scratch, &it, TokenBaseKind_Comment, &tail)){
      String_Const_u8 match = string_u8_litexpr("//-");
      String_Const_u8 prefix = string_prefix(tail, match.size);
      if (block_match(prefix.str, match.str, match.size)){
        view_set_cursor(app, view, seek_pos(token->pos));
        return;
      }
    }

    b32 has_next = (direction == Scan_Forward ?
                    token_it_inc_non_whitespace(&it) :
                    token_it_dec_non_whitespace(&it));
    if (!has_next){ break; }
  }
}

CUSTOM_COMMAND_SIG(qol_find_divider_up)
CUSTOM_DOC("[QOL] Find //- divider above cursor")
{
  qol_find_divider(app, Scan_Backward);
}

CUSTOM_COMMAND_SIG(qol_find_divider_down)
CUSTOM_DOC("[QOL] Find //- divider below cursor")
{
  qol_find_divider(app, Scan_Forward);
}

function void
qol_render_kill_rect(Application_Links *app, Frame_Info frame_info, View_ID view){
  Render_Caller_Function *custom_render = (Render_Caller_Function*)get_custom_hook(app, HookID_RenderCaller);
  custom_render(app, frame_info, view);

  Rect_f32 view_rect = view_get_screen_rect(app, view);
  Rect_f32 region = view_get_buffer_region(app, view);

  Face_ID face_id = get_face_id(app, 0);
  Face_Metrics metrics = get_face_metrics(app, face_id);
  f32 line_height = metrics.line_height;

  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
  Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
  Buffer_Point buffer_point = scroll.position;
  Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);
  Range_i64 range = get_view_range(app, view);
  Rect_f32 r0 = text_layout_character_on_screen(app, text_layout_id, range.min);
  Rect_f32 r1 = text_layout_character_on_screen(app, text_layout_id, range.max);
  Rect_f32 rect = rect_union(r0, r1);
  FColor f_color = fcolor_id(defcolor_highlight);

  String_Const_u8 prompt = string_u8_litexpr("Kill Rectangle: Yes: (Y) No: (N)");
  Vec2_f32 p = rect.p0 - V2f32(0, line_height);
  f32 advance = get_string_advance(app, face_id, prompt);
  Rect_f32 prompt_rect = Rf32(p - V2f32(10.f, 10.f), p + V2f32(advance + 10.f, line_height));
  draw_rectangle(app, prompt_rect, 5.f, 0xDD000000);
  draw_string(app, face_id, prompt, p, 0xFFFFFFFF);
  draw_rectangle_fcolor(app, rect, 5.f, fcolor_change_alpha(f_color, 0.5f));
  text_layout_free(app, text_layout_id);
}

CUSTOM_COMMAND_SIG(qol_kill_rectangle)
CUSTOM_DOC("[QOL] Prompt deletion of text in the cursor/mark rectangle")
{
  View_ID view = get_active_view(app, Access_Always);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWriteVisible);
  if (buffer == 0){
    return qol_block_apply(app, view, view_get_buffer(app, view, Access_Always), get_view_range(app, view), qol_range_fade);
  }

  View_Context ctx = view_current_context(app, view);
  ctx.render_caller = qol_render_kill_rect;
  ctx.hides_buffer = false;
  View_Context_Block ctx_block(app, view, &ctx);

  for (;;){
    User_Input in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
    if (in.abort){ break; }
    else if (in.event.kind == InputEventKind_CustomFunction){ return in.event.custom_func(app); }
    else if (match_core_code(&in, CoreCode_TryExit)){ return implicit_map_function(app, 0, 0, &in.event).command(app); }
    else if (match_key_code(&in, KeyCode_Y)){ return qol_block_delete(app, view, buffer, get_view_range(app, view)); }
    else if (match_key_code(&in, KeyCode_N)){ return; }
  }
}
