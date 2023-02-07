
#define qol_interp(cur, nxt, dt, rate) (cur += (((nxt) - (cur))*(1.f - pow_f32(rate, dt))))

function Rect_f32 rect_vsplit(Rect_f32 r, f32 t, b32 c){ return !c ? rect_split_left_right(r, t).min : rect_split_left_right_neg(r, t).max; }
function Rect_f32 rect_hsplit(Rect_f32 r, f32 t, b32 c){ return !c ? rect_split_top_bottom(r, t).min : rect_split_top_bottom_neg(r, t).max; }

function void
printf_message(Application_Links *app, char *format, ...){
  Scratch_Block scratch(app);
  va_list args;
  va_start(args, format);
  String_Const_u8 result = push_stringfv(scratch, format, args);
  print_message(app, result);
  va_end(args);
}
