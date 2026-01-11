// 4coder_minimap.cpp
// BYP

// Expected usage, at the end of render_buffer add
// draw_cpp_token_colors(app, buffer, MM_draw_text_id(app, view, face, buffer, tokens, region, visible_range));
// Where you may bring your own version of `draw_cpp_token_colors`

// If you'd like to be a good citizen, you can replace
//  -    paint_text_color (app, text_layout_id, Ii64(token), argb)
//  + MM_paint_token_color(app, text_layout_id, token,       argb)
// To remove a per-token binary search of token_from_pos(...)

// TODO: optimize core methods for line layout
// NOTE: Nests use defcolor_control, *technically* non-default. Deal with it

function Text_Layout_ID MM_draw_text_id(Application_Links *app, View_ID view, Face_ID face, Buffer_ID buffer, Token_Array tokens, Rect_f32 region, Range_i64 visible_range);

function void MM_paint_text_color (Application_Links* app, Text_Layout_ID layout_id, Range_i64 range, ARGB_Color color);
function void MM_paint_token_color(Application_Links* app, Text_Layout_ID layout_id, Token*    token, ARGB_Color color);

function b32 MM_will_handle(Application_Links *app);

// Only necessary if you want "minimap_scrollable"
#define MM_Wrap(f) ([](Application_Links *app){ if(!MM_will_handle(app)){ f(app); } })
// BindMouse(MM_Wrap(click_set_cursor_and_mark), MouseCode_Left);
// BindMouseRelease(MM_Wrap(click_set_cursor), MouseCode_Left);
// BindCore(click_set_cursor_and_mark, CoreCode_ClickActivateView);
// BindMouseMove(MM_Wrap(click_set_cursor_if_lbutton));

struct MM_Context{
  View_ID view;
  Buffer_ID buffer;
  Face_ID face;
  Text_Layout_ID layout;
  i64 line;
  Rect_f32 region;
  Range_i64 range;

  Token_Array tokens;
  Vec2_f32 s_p0;
  Vec2_f32 s_str;

  custom_paint_text_color_type *core_paint_text_color;
  Token* hint;

  Vec2_f32 rel_dim;
  Vec2_f32 rel_delta;

  View_ID  hot_view;
  Rect_f32 hot_rect;
  f32      hot_y_offset;

  // Cached to minimize calls to Layout_Function*
  Rect_f32  _rect;
  Range_i64 _range;
  Vec2_f32  _p0;
};
global MM_Context g_mm_ctx;

function Vec2_f32 MM_get_xy(Application_Links *app, i64 pos){
  if (!range_contains(g_mm_ctx._range, pos)){
    g_mm_ctx._rect      = view_relative_box_of_pos(app, g_mm_ctx.view, g_mm_ctx.line, pos);
    g_mm_ctx._range.min = view_pos_at_relative_xy (app, g_mm_ctx.view, g_mm_ctx.line, V2f32(0.f,     g_mm_ctx._rect.y0));
    g_mm_ctx._range.max = view_pos_at_relative_xy (app, g_mm_ctx.view, g_mm_ctx.line, V2f32(max_f32, g_mm_ctx._rect.y0));
    g_mm_ctx._p0 = g_mm_ctx.region.p0 + hadamard(g_mm_ctx.s_p0, g_mm_ctx._rect.p0);
  }
  return g_mm_ctx._p0 + g_mm_ctx.s_str.x * V2f32(f32(pos - g_mm_ctx._range.min), 0);
}

function Rect_f32 MM_rect(Application_Links *app, Range_i64 range){
  Rect_f32 r0 = Rf32_xy_wh(view_relative_xy_of_pos(app, g_mm_ctx.view, g_mm_ctx.line, range.min) - g_mm_ctx.rel_delta, g_mm_ctx.rel_dim);
  Rect_f32 r1 = Rf32_xy_wh(view_relative_xy_of_pos(app, g_mm_ctx.view, g_mm_ctx.line, range.max) - g_mm_ctx.rel_delta, g_mm_ctx.rel_dim);
  return rect_union(r0, r1);
}

function Code_Index_Nest* MM_last_nest(Code_Index_Nest_Ptr_Array *array, Range_i64 range, Code_Index_Nest *nest){
  for (i64 i=0; i < array->count; i++){
    Code_Index_Nest *n = array->ptrs[array->count-1 - i];
    if (range_overlap(range, Ii64(n->open.min, n->close.min)) && n->kind == CodeIndexNest_Scope){
      return MM_last_nest(&n->nest_array, range, n);
    }
  }
  return nest;
}

function b32 MM_draw_scopes(Application_Links *app, Code_Index_Nest_Ptr_Array *array, Code_Index_Nest *last, Range_i64 range, ARGB_Color color){
  for (i64 i=0; i < array->count; i++){
    Code_Index_Nest *nest = array->ptrs[i];
    if (range_overlap(range, Ii64(nest->open.min, nest->close.min)) && nest->kind == CodeIndexNest_Scope){
      Rect_f32 r = MM_rect(app, Ii64(nest->open.min, nest->close.min));
      Vec2_f32 p0  = g_mm_ctx.region.p0 + hadamard(g_mm_ctx.s_p0, r.p0);
      Vec2_f32 dim = V2f32(1.f, g_mm_ctx.s_p0.y * rect_height(r));
      draw_rectangle(app, Rf32_xy_wh(p0, dim), 0.f, color);
      if (nest == last || MM_draw_scopes(app, &nest->nest_array, last, range, color)){ return true; }
    }
    if (range.max <= nest->open.min){ break; }
  }
  return false;
}

function void MM_paint_token_color(Application_Links* app, Text_Layout_ID layout_id, Token* token, ARGB_Color color){
  paint_text_color(app, layout_id, Ii64(g_mm_ctx.hint = token), color);
}

function void MM_paint_text_color(Application_Links* app, Text_Layout_ID layout_id, Range_i64 range, ARGB_Color color){
  if (g_mm_ctx.layout == 0){ return paint_text_color(app, layout_id, range, color); }
  if (g_mm_ctx.layout != layout_id){ return g_mm_ctx.core_paint_text_color(app, layout_id, range, color); }
  if (!range_overlap(range, g_mm_ctx.range)){ return; }

  b32 use_hint = (g_mm_ctx.hint && g_mm_ctx.hint->pos == range.min);
  Token *t = (use_hint ? g_mm_ctx.hint : token_from_pos(&g_mm_ctx.tokens, range.min));
  if (t == 0 || range.max <= t->pos || t->kind == TokenBaseKind_Whitespace){ return; }

  i64 pos = t->pos;
  Vec2_f32 p = MM_get_xy(app, pos);
  for(i64 i=range.min; i<range.max+1; i++){  // bail if there are somehow more lines than chars
    i64 end = Min(range.max, g_mm_ctx._range.max);
    Rect_f32 rect = Rf32_xy_wh(p, hadamard(g_mm_ctx.s_str, V2f32(Max(2.f/1.1f, f32(end-pos)), 1.f)));
    if (rect_overlap(rect, g_mm_ctx.region)){
      draw_rectangle_fcolor(app, rect, 0.f, fcolor_change_alpha(fcolor_argb(color), 0.8f));
    }

    if (range.max <= end){ break; }  // Which ends first: the visual line, or the token?
    g_mm_ctx._range.min = view_pos_at_relative_xy (app, g_mm_ctx.view, g_mm_ctx.line, V2f32(0.f,     g_mm_ctx._rect.y1 + g_mm_ctx.rel_dim.y));
    g_mm_ctx._range.max = view_pos_at_relative_xy (app, g_mm_ctx.view, g_mm_ctx.line, V2f32(max_f32, g_mm_ctx._rect.y1 + g_mm_ctx.rel_dim.y));
    g_mm_ctx._rect      = view_relative_box_of_pos(app, g_mm_ctx.view, g_mm_ctx.line, g_mm_ctx._range.min);
    g_mm_ctx._p0 = g_mm_ctx.region.p0 + hadamard(g_mm_ctx.s_p0, g_mm_ctx._rect.p0);
    pos = g_mm_ctx._range.min;
    p = g_mm_ctx._p0;
  }
}

function Text_Layout_ID MM_draw_text_id(Application_Links *app, View_ID view, Face_ID face, Buffer_ID buffer, Token_Array tokens, Rect_f32 region, Range_i64 visible_range){
  if (!def_get_config_b32(vars_save_string_lit("minimap_enabled")) || 
      def_get_config_b32(vars_save_string_lit("minimap_only_active")) && view != get_active_view(app, Access_Always)){ 
    return 0;
  }

  if (g_mm_ctx.layout){ text_layout_free(app, g_mm_ctx.layout); }
  Face_Metrics metrics = get_face_metrics(app, face);
  f32 minimap_line_height = 4.f;
  f32 minimap_char_width  = 1.1f;
  f32 width = Min(0.3f*rect_width(region), 15.f*metrics.normal_advance);
  Rect_f32 outer = rect_split_left_right_neg(region, width).b;

  i64 buf_line_count = buffer_get_line_count(app, buffer);
  f32 view_line_count = rect_height(region) / metrics.line_height;
  f32   mm_line_count = rect_height(region) / minimap_line_height;
  mm_line_count = Min(mm_line_count, f32(buf_line_count));
  i64 mm_scroll_line_count = Max(0, buf_line_count - i64(mm_line_count));

  Buffer_Scroll scroll = view_get_buffer_scroll(app, view);
  f32 y  = metrics.line_height * f32(scroll.position.line_number) + scroll.position.pixel_shift.y;
  f32 y1 = metrics.line_height * f32(buf_line_count) - rect_height(region);

  f32 top = (y1 <= 0.f ? 0.f : clamp(0.f, y/y1, 1.f) * f32(mm_scroll_line_count));
  i64 top_line = i64(top);
  f32 y_shift = top - f32_integer(top);

  g_mm_ctx.view   = view;
  g_mm_ctx.face   = face;
  g_mm_ctx.buffer = buffer;
  g_mm_ctx.tokens = tokens;
  g_mm_ctx.layout = text_layout_create(app, buffer, Rf32(0, 0, rect_width(region), metrics.line_height*mm_line_count), {top_line, V2f32(0, y_shift)});
  g_mm_ctx.line   = top_line;
  g_mm_ctx.region = Rf32(outer.x0+8, outer.y0+1, outer.x1, Min(outer.y1-1, outer.y0+minimap_line_height*mm_line_count));
  g_mm_ctx.range = text_layout_get_visible_range(app, g_mm_ctx.layout);
  g_mm_ctx.s_p0  = V2f32(minimap_char_width / metrics.normal_advance, minimap_line_height / metrics.line_height);
  g_mm_ctx.s_str = V2f32(minimap_char_width, minimap_line_height-1.f);

  if (paint_text_color != MM_paint_text_color){
    g_mm_ctx.core_paint_text_color = paint_text_color;
    paint_text_color = MM_paint_text_color;
  }

  draw_rectangle_fcolor(app, outer, 0.f, fcolor_change_alpha(fcolor_blend(fcolor_id(defcolor_back), 0.3f, fcolor_id(defcolor_highlight_cursor_line)), 0.8f));

  Vec2_f32 p0 = MM_get_xy(app, get_line_end_pos(app, buffer, get_line_number_from_pos(app, buffer, visible_range.min+0)));
  Vec2_f32 p1 = MM_get_xy(app, get_line_end_pos(app, buffer, get_line_number_from_pos(app, buffer, visible_range.max-1)));
  Vec2_f32 a  = MM_get_xy(app, view_get_cursor_pos(app, view));
  Vec2_f32 b  = MM_get_xy(app, view_get_mark_pos(app, view));
  Rect_f32 r  = Rf32(rect_range_x(outer), If32(p0.y, p1.y + minimap_line_height));
  Rect_f32 ra = Rf32(rect_range_x(outer), If32_size(a.y, minimap_line_height));
  Rect_f32 rb = Rf32(rect_range_x(outer), If32_size(b.y, minimap_line_height));
  draw_rectangle_fcolor(app, r,  0.f, fcolor_change_alpha(fcolor_id(defcolor_highlight_cursor_line), 0.8f));
  draw_rectangle_fcolor(app, ra, 0.f, fcolor_change_alpha(fcolor_id(defcolor_cursor), 0.2f));
  draw_rectangle_fcolor(app, rb, 0.f, fcolor_change_alpha(fcolor_id(defcolor_mark), 0.2f));

  i64 pos = get_line_end_pos(app, buffer, g_mm_ctx.line);
  Vec2_f32 rel_p = view_relative_xy_of_pos(app, view, g_mm_ctx.line, pos);
  Rect_f32 rel_r = text_layout_character_on_screen(app, g_mm_ctx.layout, pos);
  g_mm_ctx.rel_dim = rect_dim(rel_r);
  g_mm_ctx.rel_delta = rel_p - rel_r.p0;

  if (def_get_config_b32(vars_save_string_lit("minimap_render_nests"))){
    code_index_lock();
    Code_Index_File *file = code_index_get_file(buffer);
    if (file){
      FColor cl = fcolor_change_alpha(fcolor_id(defcolor_control), 0.5f);
      Code_Index_Nest* last = MM_last_nest(&file->nest_array, g_mm_ctx.range, NULL);
      MM_draw_scopes(app, &file->nest_array, last, g_mm_ctx.range, fcolor_resolve(cl));
    }
    code_index_unlock();
  }

  if (def_get_config_b32(vars_save_string_lit("minimap_scrollable"))){
    Mouse_State m = get_mouse_state(app);
    if (g_mm_ctx.hot_view == 0 && rect_contains_point(outer, V2f32(m.p)) && m.press_l){
      g_mm_ctx.hot_view = view;
      g_mm_ctx.hot_rect = outer;
      g_mm_ctx.hot_y_offset = rect_contains_point(r, V2f32(m.p)) ? f32(m.p.y) - rect_center(r).y : 0.f;
    }

    if (g_mm_ctx.hot_view == view){
      if(m.l == false){ g_mm_ctx.hot_view = 0; }
      f32 dy = 0.5f*minimap_line_height*view_line_count;
      f32 t = unlerp(g_mm_ctx.region.y0 + dy, f32(m.p.y) - g_mm_ctx.hot_y_offset, g_mm_ctx.region.y1 - dy);
      i64 line = i64(clamp(0,t,1)*y1 / metrics.line_height);
      scroll.target.line_number = Max(1, line);
      scroll.target.pixel_shift = V2f32(0,0);
      scroll.position = scroll.target;
      view_set_buffer_scroll(app, view, scroll, SetBufferScroll_SnapCursorIntoView);
      if (0.f <= t && t <= 1.f){
        view_set_cursor_and_preferred_x(app, view, seek_line_col(line + i64(view_line_count)/2, 0));
      }
    }
  }

  return g_mm_ctx.layout;
}

function b32 MM_will_handle(Application_Links *app){
  Mouse_State m = get_mouse_state(app);
  return (g_mm_ctx.hot_view == get_this_ctx_view(app, Access_Always) || 
          g_mm_ctx.hot_view == 0 && rect_contains_point(g_mm_ctx.hot_rect, V2f32(m.p)));
}