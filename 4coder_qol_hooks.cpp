
function void
qol_tick(Application_Links *app, Frame_Info frame_info){
  default_tick(app, frame_info);

  f32 dt = frame_info.animation_dt;

  qol_interp(qol_cur_cursor_pos, qol_nxt_cursor_pos, dt, 1e-14f);
  if (!near_zero(qol_cur_cursor_pos - qol_nxt_cursor_pos, 0.5f)){
    animate_in_n_milliseconds(app, 0);
  }
}