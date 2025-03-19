
#define qol_interp(cur, nxt, dt, rate) (cur += (((nxt) - (cur))*(1.f - pow_f32(rate, dt))))

function Rect_f32 rect_vsplit(Rect_f32 r, f32 t, b32 c){ return !c ? rect_split_left_right(r, t).min : rect_split_left_right_neg(r, t).max; }
function Rect_f32 rect_hsplit(Rect_f32 r, f32 t, b32 c){ return !c ? rect_split_top_bottom(r, t).min : rect_split_top_bottom_neg(r, t).max; }
