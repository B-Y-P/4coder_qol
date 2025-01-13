
enum Buffer_Lang{
  Lang_None,
  Lang_Odin,
  Lang_Cpp,
  Lang_COUNT,
};

/// TODO: there's prob a better way to wrap this stuff
//union Lex_State{
//	Lex_State_Cpp cpp;
//    Lex_State_Odin odin;
//};

function void odin_do_full_lex_async__inner(Async_Context *actx, Buffer_ID buffer_id);
function void odin_do_full_lex_async(Async_Context *actx, String_Const_u8 data);
function void cpp_do_full_lex_async__inner(Async_Context *actx, Buffer_ID buffer_id);
function void cpp_do_full_lex_async(Async_Context *actx, String_Const_u8 data);

function Token_List lex_full_input_lang(Arena *arena, String8 text, Buffer_Lang lang);

function b32 odin_parse_full_input_breaks(Code_Index_File *index, Generic_Parse_State *state, i32 limit);

void* lang_lex_async[Lang_COUNT] = {
  NULL,
  (void*)odin_do_full_lex_async,
  (void*)cpp_do_full_lex_async,
};