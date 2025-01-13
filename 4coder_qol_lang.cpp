
function Token_List
lex_full_input_lang(Arena *arena, String8 text, Buffer_Lang lang){
    return (lang == Lang_Odin ? lex_full_input_odin(arena, text) :
            lang == Lang_Cpp  ? lex_full_input_cpp(arena, text) : Token_List{});
}

function b32
parse_full_input_lang(Code_Index_File *index, Generic_Parse_State *state, i32 limit, Buffer_Lang lang){
    return (lang == Lang_Odin ? odin_parse_full_input_breaks(index, state, limit) :
            lang == Lang_Cpp  ? generic_parse_full_input_breaks(index, state, limit) : false);
}


//- Odin

function void
odin_do_full_lex_async__inner(Async_Context *actx, Buffer_ID buffer_id){
	Application_Links *app = actx->app;
	ProfileScope(app, "async lex");
	Scratch_Block scratch(app);

	String_Const_u8 contents = {};
	{
		ProfileBlock(app, "async lex contents (before mutex)");
		acquire_global_frame_mutex(app);
		ProfileBlock(app, "async lex contents (after mutex)");
		contents = push_whole_buffer(app, scratch, buffer_id);
		release_global_frame_mutex(app);
	}

	i32 limit_factor = 10000;

	Token_List list = {};
	b32 canceled = false;

	Lex_State_Odin state = {};
	lex_full_input_odin_init(&state, contents);
	for (;;){
		ProfileBlock(app, "async lex block");
		if (lex_full_input_odin_breaks(scratch, &list, &state, limit_factor)){
			break;
		}
		if (async_check_canceled(actx)){
			canceled = true;
			break;
		}
	}

	if (!canceled){
		ProfileBlock(app, "async lex save results (before mutex)");
		acquire_global_frame_mutex(app);
		ProfileBlock(app, "async lex save results (after mutex)");
		Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
		if (scope != 0){
			Base_Allocator *allocator = managed_scope_allocator(app, scope);
			Token_Array *tokens_ptr = scope_attachment(app, scope, attachment_tokens, Token_Array);
			base_free(allocator, tokens_ptr->tokens);
			Token_Array tokens = {};
			tokens.tokens = base_array(allocator, Token, list.total_count);
			tokens.count = list.total_count;
			tokens.max = list.total_count;
			token_fill_memory_from_list(tokens.tokens, &list);
			block_copy_struct(tokens_ptr, &tokens);
		}
		buffer_mark_as_modified(buffer_id);
		release_global_frame_mutex(app);
	}
}

function void
odin_do_full_lex_async(Async_Context *actx, String_Const_u8 data){
	if (data.size == sizeof(Buffer_ID)){
		Buffer_ID buffer = *(Buffer_ID*)data.str;
		odin_do_full_lex_async__inner(actx, buffer);
	}
}

//- Cpp
function void
cpp_do_full_lex_async__inner(Async_Context *actx, Buffer_ID buffer_id){
	Application_Links *app = actx->app;
	ProfileScope(app, "async lex");
	Scratch_Block scratch(app);

	String_Const_u8 contents = {};
	{
		ProfileBlock(app, "async lex contents (before mutex)");
		acquire_global_frame_mutex(app);
		ProfileBlock(app, "async lex contents (after mutex)");
		contents = push_whole_buffer(app, scratch, buffer_id);
		release_global_frame_mutex(app);
	}

	i32 limit_factor = 10000;

	Token_List list = {};
	b32 canceled = false;

	Lex_State_Cpp state = {};
	lex_full_input_cpp_init(&state, contents);
	for (;;){
		ProfileBlock(app, "async lex block");
		if (lex_full_input_cpp_breaks(scratch, &list, &state, limit_factor)){
			break;
		}
		if (async_check_canceled(actx)){
			canceled = true;
			break;
		}
	}

	if (!canceled){
		ProfileBlock(app, "async lex save results (before mutex)");
		acquire_global_frame_mutex(app);
		ProfileBlock(app, "async lex save results (after mutex)");
		Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
		if (scope != 0){
			Base_Allocator *allocator = managed_scope_allocator(app, scope);
			Token_Array *tokens_ptr = scope_attachment(app, scope, attachment_tokens, Token_Array);
			base_free(allocator, tokens_ptr->tokens);
			Token_Array tokens = {};
			tokens.tokens = base_array(allocator, Token, list.total_count);
			tokens.count = list.total_count;
			tokens.max = list.total_count;
			token_fill_memory_from_list(tokens.tokens, &list);
			block_copy_struct(tokens_ptr, &tokens);
		}
		buffer_mark_as_modified(buffer_id);
		release_global_frame_mutex(app);
	}
}

function void
cpp_do_full_lex_async(Async_Context *actx, String_Const_u8 data){
	if (data.size == sizeof(Buffer_ID)){
		Buffer_ID buffer = *(Buffer_ID*)data.str;
		cpp_do_full_lex_async__inner(actx, buffer);
	}
}