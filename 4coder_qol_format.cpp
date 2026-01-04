
Range_i64 range_nest(Code_Index_Nest *nest){ return range_union(nest->open, nest->close); }
//Range_i64 range_nest(Code_Index_Nest *nest){ return Ii64(nest->open.min, nest->close.min); }

global Code_Index_Nest* g_nest;

function void qol_render_nest_inner(Application_Links *app, View_ID view, Buffer_ID buffer, Text_Layout_ID text_layout_id, ARGB_Color cl, f32 t, Code_Index_Nest* nest){
  if (PtrAsInt(nest) <= 100){ return; }
  Range_i64 r = range_nest(nest);
  Rect_f32 r0 = text_layout_character_on_screen(app, text_layout_id, r.min);
  Rect_f32 r1 = text_layout_character_on_screen(app, text_layout_id, r.max-1);
  Rect_f32 rect = qol_get_abs_block_rect(app, view, buffer, text_layout_id, Ii64(r.min, r.max-1));
  Rect_f32 prev_clip = draw_set_clip(app, Rect_f32{});
  f32 wid = get_view_face_metrics(app, view).normal_advance;
  draw_set_clip(app, rect_height(rect) <= rect_height(r1) ? prev_clip : Rf32(rect.p0, V2f32(rect.x0 + 3.f + wid, rect.y1)));
  draw_rectangle_outline(app, r0,   2.f, t, cl);
  draw_rectangle_outline(app, r1,   2.f, t, cl);
  draw_rectangle_outline(app, rect, 0.f, t, cl);
  draw_set_clip(app, prev_clip);
}

function void qol_render_nest(Application_Links *app, View_ID view, Buffer_ID buffer, Text_Layout_ID text_layout_id){
  if (view != get_active_view(app, Access_Always)){ return; }
  if(g_nest == 0){ return; }
  {
    ARGB_Color cl_cursor = fcolor_resolve(fcolor_id(defcolor_cursor));
    qol_render_nest_inner(app, view, buffer, text_layout_id, cl_cursor,  4.f, g_nest);
    qol_render_nest_inner(app, view, buffer, text_layout_id, 0xFFFF0000, 4.f, g_nest->parent);
    qol_render_nest_inner(app, view, buffer, text_layout_id, 0xFF00FF00, 3.f, g_nest->next);
  }
  for(Code_Index_Nest* n = g_nest->nest_list.first; n; n = n->next){
    qol_render_nest_inner(app, view, buffer, text_layout_id, 0xFF00AAFF, 2.f, n);
  }
}

function void qol_assign_nest(Application_Links *app, Code_Index_Nest* nest){
  if (nest == 0){ return; }
  Range_i64 r = range_nest(nest);
  View_ID view = get_active_view(app, Access_Always);
  view_set_cursor(app, view, seek_pos(r.min));
  view_set_mark(app, view, seek_pos(r.max-1));
}

CUSTOM_COMMAND_SIG(qol_nest_test)
CUSTOM_DOC("")
{
  View_ID view = get_active_view(app, Access_ReadWrite);
  Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWrite);

  code_index_lock();
  Code_Index_File *index = code_index_get_file(buffer);
  qol_assign_nest(app, g_nest = code_index_get_nest(index, view_get_cursor_pos(app, view)));
  code_index_unlock();
}

CUSTOM_COMMAND_SIG(qol_nest_first)  { if(g_nest){ qol_assign_nest(app, g_nest = g_nest->nest_list.first); } }
CUSTOM_COMMAND_SIG(qol_nest_next)   { if(g_nest){ qol_assign_nest(app, g_nest = g_nest->next); } }
CUSTOM_COMMAND_SIG(qol_nest_parent) { if(g_nest){ qol_assign_nest(app, g_nest = g_nest->parent); } }
