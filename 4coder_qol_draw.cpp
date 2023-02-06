
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
    Rect_f32_Pair pair = layout_file_bar_on_bot(region, line_height);
    draw_file_bar(app, view_id, buffer, face_id, pair.max);
    region = pair.min;
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

  // NOTE(allen): begin buffer render
  Buffer_Point buffer_point = scroll.position;
  Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, buffer_point);

  // NOTE(allen): draw line numbers
  if (show_line_number_margins){
    draw_line_number_margin(app, view_id, buffer, face_id, text_layout_id, line_number_rect);
  }

  // NOTE(allen): draw the buffer
  default_render_buffer(app, view_id, face_id, buffer, text_layout_id, region);

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
    Rect_f32_Pair pair = layout_file_bar_on_bot(region, line_height);
    region = pair.min;
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

  return(region);
}
