
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