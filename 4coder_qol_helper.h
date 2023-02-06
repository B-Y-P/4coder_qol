
#define qol_interp(cur, nxt, dt, rate) (cur += (((nxt) - (cur))*(1.f - pow_f32(rate, dt))))
