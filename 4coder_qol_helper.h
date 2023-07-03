
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

function Range_i64
get_line_range_from_pos(Application_Links *app, Buffer_ID buffer, i64 pos){
  i64 line = get_line_number_from_pos(app, buffer, pos);
  return get_line_pos_range(app, buffer, line);
}

function void
qol_bot_text_set(String_Const_u8 string){
  block_copy(g_qol_bot_buffer, string.str, string.size);
  g_qol_bot_string.size = string.size;
}

function void
qol_bot_text_append(String_Const_u8 string){
  string_append(&g_qol_bot_string, string);
}

function f32
qol_bot_line_count(Application_Links *app){
  f32 line = def_get_config_f32(app, vars_save_string_lit("bot_line_count"));
  return clamp(1.f, line, 5.f);
}

function f32
qol_bot_text_height(Application_Links *app, Face_Metrics metrics){
  f32 height_char     = metrics.ascent - metrics.descent;
  f32 height_initial  = qol_bot_line_count(app)*height_char;
  f32 height_baseline = 0.5f*height_initial;
  f32 height_required = height_baseline + 0.5f*height_char;
  return 2.f + Max(height_initial, height_required) + 2.f;
}

function f32
qol_bot_text_y_offset(Application_Links *app, Face_Metrics metrics){
  f32 height_char     = metrics.ascent - metrics.descent;
  f32 height_initial  = qol_bot_line_count(app)*height_char;
  f32 height_baseline = 0.5f*height_initial;
  return 2.f + height_baseline + 0.5f*height_char;
}