
#define qol_interp(cur, nxt, dt, rate) (cur += (((nxt) - (cur))*(1.f - pow_f32(rate, dt))))

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
