// 4coder_multi_cursor.cpp
// BYP

#define MC_USE_STUB 0

#if MC_USE_STUB
// build.bat: `call %qol_dir%\custom\bin\buildsuper_x64-win.bat %qol_dir%\plugins\4coder_multi_cursor.cpp %1`
#include "4coder_default_include.h"
#include "4coder_default_include.cpp"
#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif
#endif

// TODO:
// MC search helpers to allow user to leave MC at each keyword or token
// MC Command Lister filtering and dispatch while MC active
// Core change to use ropes if this ever needs to be optimized

//- Declarations
// NOTE: Must be called, preferably right after custom_layer_init::default_framework_init(...)
function void MC_init(Application_Links *app);

// inner Hook functions, call from your own custom hooks
function void MC_tick_inner(Application_Links *app, Frame_Info frame_info);
function i32  MC_buffer_edit_range_inner(Application_Links *app, Buffer_ID buffer_id, Range_i64 new_range, Range_Cursor old_cursor_range);
function void MC_render_cursors(Application_Links *app, View_ID view, Text_Layout_ID layout);

// Hook functions, only pass to set_custom_hook(...) if using default hooks
function void MC_tick(Application_Links *app, Frame_Info frame_info);
function i32  MC_buffer_edit_range(Application_Links *app, Buffer_ID buffer_id, Range_i64 new_range, Range_Cursor old_cursor_range);
function void MC_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id);

// NOTE: You may safely ignore these if you don't override override default_implicit_map / implicit_map_function
function Implicit_Map_Result MC_implicit_map_inner(Application_Links *app, Implicit_Map_Result map_result);
function Implicit_Map_Result MC_implicit_map(Application_Links *app, String_ID lang, String_ID mode, Input_Event *event);

struct MC_Node{
	MC_Node *next;
	i64 cursor_pos;
	i64 mark_pos;
	Vec2_f32 cur_position;
	Vec2_f32 nxt_position;
	String_Const_u8 clipboard;
};

enum MC_Command_Kind{
	MC_Command_Cursor,       // Run on every cursor (no copy, paste)
	MC_Command_Global,       // Run once
	MC_Command_CursorCopy,   // Run copy-style func on every on cursor  (writes to clipboard)
	MC_Command_CursorPaste,  // Run paste-style func on every cursor    (reads from clipboard)
	// TODO: single-line-cursor commands for better lister text-fields?
};

struct MC_Context{
	Table_u64_u64 table;   //  Custom_Command_Function*  ->  MC_Command_Kind
	Arena arena_cursors;
	Arena arena_clipboard;
	History_Group history;
	b32 active;
	View_ID view;
	MC_Node *cursors;
	MC_Node *active_cursor;
	MC_Node *free_list;
	Vec2_f32 nxt_position;
};

global MC_Context mc_context;

#define for_mc(i, head) for(MC_Node *i=head; i != 0; i=i->next)

// API
function void MC_begin(Application_Links *app);
function void MC_end(Application_Links *app);
function void MC_insert(Application_Links *app, i64 cursor_pos, i64 mark_pos);
function void MC_insert(Application_Links *app, i64 pos);
function void MC_remove(Application_Links *app, i64 pos);

function void MC_no_op(Application_Links *app){ /* Does nothing... with style :P */ }
function void MC_register(Custom_Command_Function *func, MC_Command_Kind kind);
function void MC_pull(Application_Links *app, View_ID view, MC_Command_Kind kind, MC_Node *node);
function void MC_push(Application_Links *app, View_ID view, MC_Command_Kind kind, MC_Node *node);
function void MC_apply(Application_Links *app, Custom_Command_Function *func, MC_Command_Kind kind);

#define                                   MC_BindTextInput(F)   MC_register(F, MC_Command_Cursor); BindTextInput(F)
#if COMPILER_CL
#define                                   MC_Bind(F, K, ...)    MC_register(F, MCi_kind(map));     Bind(F, K, __VA_ARGS__)
#elif COMPILER_GCC | COMPILER_CLANG
#define                                   MC_Bind(F, K, ...)    MC_register(F, MCi_kind(map));     Bind(F, K, ##__VA_ARGS__)
#else
#error "Unsupported compiler"
#endif

function MC_Command_Kind MCi_kind(Command_Map *map){
	return MC_Command_Kind(map->id == (Command_Map_ID)vars_save_string_lit("keys_global"));
}


//- Implementation
function void MC_init(Application_Links *app){
	mc_context.arena_cursors   = make_arena_system();
	mc_context.arena_clipboard = make_arena_system();
	mc_context.table = make_table_u64_u64(get_base_allocator_system(), 128);
	implicit_map_function = MC_implicit_map;
}

function void MC_tick_inner(Application_Links *app, Frame_Info frame_info){
	for_mc(node, mc_context.cursors){
		if (node->cur_position == V2f32(min_f32, min_f32)){
			node->cur_position = node->nxt_position - V2f32(10.f, 0.f);
		}
		Vec2_f32 delta = node->nxt_position - node->cur_position;
		node->cur_position += delta*(1.f - powf(1e-14f, frame_info.animation_dt));
		if (!near_zero(delta, 0.5f)){
			animate_in_n_milliseconds(app, 0);
		}
	}
}

function void MC_render_cursors(Application_Links *app, View_ID view, Text_Layout_ID layout){
	if (view!= mc_context.view){ return; }
	Range_i64 visible_range = text_layout_get_visible_range(app, layout);
	ARGB_Color cl_cursor = fcolor_resolve(fcolor_change_alpha(fcolor_id(defcolor_cursor), mc_context.active ? 1.f : 0.8f));
	ARGB_Color cl_mark   = fcolor_resolve(fcolor_change_alpha(fcolor_id(defcolor_mark),   mc_context.active ? 1.f : 0.8f));

	for_mc(node, mc_context.cursors){
		if (range_contains(visible_range, node->cursor_pos)){
			Rect_f32 rect = text_layout_character_on_screen(app, layout, node->cursor_pos);
			node->nxt_position = rect.p0;
			draw_rectangle_outline(app, Rf32_xy_wh(node->cur_position, rect_dim(rect)), 0.f, 3.f, cl_cursor);
		}
		if (range_contains(visible_range, node->mark_pos)){
			draw_character_i_bar(app, layout, node->mark_pos, cl_mark);
		}
	}
}

function Implicit_Map_Result MC_implicit_map_inner(Application_Links *app, Input_Event *event, Implicit_Map_Result map_result){
	if (map_result.command != 0 && mc_context.active && mc_context.view == get_this_ctx_view(app, Access_Always)){
		if (event->kind == InputEventKind_Core && event->core.code == CoreCode_NewClipboardContents){
			linalloc_clear(&mc_context.arena_clipboard);
			String_Const_u8 string = push_string_copy(&mc_context.arena_clipboard, event->core.string);
			for_mc(node, mc_context.cursors){
				node->clipboard = string;
			}
		}

		Table_Lookup lookup = table_lookup(&mc_context.table, HandleAsU64(map_result.command));
		if (lookup.found_match){
			u64 val = mc_context.table.vals[lookup.index];
			MC_apply(app, map_result.command, MC_Command_Kind(val));
			map_result.command = MC_no_op;  // NOTE: no-op prevents erroneous leave_current_input_unhandled()
		}
		else{
			// NOTE: this is where you'd screen-shake and all the bells and whistles :P
			MC_apply(app, MC_error_fade, MC_Command_Cursor);
			Command_Metadata *meta = get_command_metadata(map_result.command);
			print_message(app, string_u8_litexpr("[MC] <"));
			print_message(app, meta ? SCu8(meta->name, meta->name_len) : string_u8_litexpr("Command"));
			print_message(app, string_u8_litexpr("> not available during multi-cursor mode\n"));
			map_result.command = MC_no_op;
		}
	}
	return(map_result);
}

function Implicit_Map_Result MC_implicit_map(Application_Links *app, String_ID lang, String_ID mode, Input_Event *event){
	Implicit_Map_Result result = default_implicit_map(app, lang, mode, event);
	return MC_implicit_map_inner(app, event, result);
}

function i32 MC_buffer_edit_range_inner(Application_Links *app, Buffer_ID buffer_id, Range_i64 new_range, Range_Cursor old_cursor_range){
	if (!mc_context.active || buffer_id != view_get_buffer(app, mc_context.view, Access_Always)){
		return 0;
	}

	Range_i64 old_range = Ii64(old_cursor_range.min.pos, old_cursor_range.max.pos);
	i64 insert_size = range_size(new_range);

	for_mc(node, mc_context.cursors){
		/// TODO: handle case when cursor-mark overlaps other cursors and delete...
		//if (range_contains(old_range) && node != mc_context.active){}
		index_shift(&node->cursor_pos, old_range, insert_size);
		index_shift(&node->mark_pos, old_range, insert_size);
	}

	return 0;
}

function void MC_begin(Application_Links *app){
	View_ID view = get_active_view(app, Access_ReadVisible);
	if (mc_context.view != view){
		return MC_end(app);
	}

	// Remove any multi-cursor overlapping with real cursor
	i64 cursor_pos = view_get_cursor_pos(app, view);
	view_set_mark(app, view, seek_pos(cursor_pos));
	MC_remove(app, cursor_pos);

	// If there are no multi-cursors, don't start
	if (mc_context.cursors == NULL){
		return MC_end(app);
	}

	Buffer_ID buffer = view_get_buffer(app, view, Access_ReadVisible);
	mc_context.active = true;
	mc_context.view = view;
	mc_context.history = history_group_begin(app, buffer);

	String_Const_u8 string = push_clipboard_index(&mc_context.arena_clipboard, 0, 0);
	for_mc(node, mc_context.cursors){
		node->clipboard = string;
	}
}

function void MC_end(Application_Links *app){
	if (mc_context.active){
		history_group_end(mc_context.history);
	}
	linalloc_clear(&mc_context.arena_cursors);
	linalloc_clear(&mc_context.arena_clipboard);
	mc_context.active        = false;
	mc_context.view          = 0;
	mc_context.cursors       = NULL;
	mc_context.active_cursor = NULL;
	mc_context.free_list     = NULL;
}

function void MC_insert(Application_Links *app, i64 cursor_pos, i64 mark_pos){
	View_ID view = get_active_view(app, Access_Always);
	if (mc_context.active_cursor){ return; }
	if (mc_context.view == 0){
		mc_context.view = view;
	}
	else if (mc_context.view != view){
		return;
	}

	for_mc(node, mc_context.cursors){
		if (node->cursor_pos == cursor_pos){ return; }
	}

	MC_Node *node = mc_context.free_list;
	if (node){
		sll_stack_pop(mc_context.free_list);
	}
	else {
		node = push_array_zero(&mc_context.arena_cursors, MC_Node, 1);
	}
	sll_stack_push(mc_context.cursors, node);

	node->cursor_pos = cursor_pos;
	node->mark_pos = mark_pos;
	node->cur_position = node->nxt_position = V2f32(min_f32, min_f32);
}

function void MC_insert(Application_Links *app, i64 pos){
	MC_insert(app, pos, pos);
}

function void MC_insert(Application_Links *app){
	View_ID view = get_active_view(app, Access_Always);
	i64 pos = view_get_cursor_pos(app, view);
	MC_insert(app, pos, pos);
}

function void MC_remove(Application_Links *app, i64 pos){
	MC_Node **ptr = &mc_context.cursors;
	while (*ptr){
		if (pos == (*ptr)->cursor_pos){
			MC_Node *node = *ptr;
			*ptr = node->next;
			sll_stack_push(mc_context.free_list, node);
			break;
		}
		ptr = &(*ptr)->next;
	}
}

function void MC_register(Custom_Command_Function *func, MC_Command_Kind kind){
	table_insert(&mc_context.table, HandleAsU64(func), u64(kind));
}

function String_Const_u8 MCi_clipboard_pull(){
	return get_clipboard_index(&clipboard0, 0);
}

function void MCi_clipboard_push(String_Const_u8 string){
	u32 top = Min(clipboard0.clip_index, clipboard0.clip_capacity);
	if (top > 0){
		i32 array_index = (clipboard0.clip_index - 1) % top;
		clipboard0.clips[array_index] = string;
	}
}

function void MC_pull(Application_Links *app, View_ID view, MC_Command_Kind kind, MC_Node *node){
	node->cursor_pos = view_get_cursor_pos(app, view);
	node->mark_pos = view_get_mark_pos(app, view);
	if (kind == MC_Command_CursorCopy){
		node->clipboard = push_clipboard_index(&mc_context.arena_clipboard, 0, 0);
	}
}

function void MC_push(Application_Links *app, View_ID view, MC_Command_Kind kind, MC_Node *node){
	view_set_cursor(app, view, seek_pos(node->cursor_pos));
	view_set_mark(app, view, seek_pos(node->mark_pos));
	if (kind == MC_Command_CursorPaste){
		MCi_clipboard_push(node->clipboard);
	}
}

function void MC_apply(Application_Links *app, Custom_Command_Function *func, MC_Command_Kind kind){
	View_ID view = mc_context.view;
	Buffer_ID buffer = view_get_buffer(app, view, Access_Always);

	func(app);  // Run standard cursor

	// Check that `func` should be safe to re-run
	if (view != get_active_view(app, Access_Always) ||
		buffer != view_get_buffer(app, view, Access_Always))
	{
		MC_end(app);
		return;
	}

	if (kind == MC_Command_CursorCopy){
		// Since copy doesn't read from MC clipboards, clear it before doing multiple copies
		// _CopyPaste would require double-buffering arenas, rather not complicate for nothing
		linalloc_clear(&mc_context.arena_clipboard);
	}

	Buffer_Scroll scroll = view_get_buffer_scroll(app, mc_context.view);
	MC_Node prev = {mc_context.cursors};
	MC_pull(app, mc_context.view, kind, &prev);
	mc_context.cursors = &prev;

	for (MC_Node *n=prev.next; n; n=n->next){
		MC_push(app, mc_context.view, kind, n);
		mc_context.active_cursor = n;
		func(app);
		MC_pull(app, mc_context.view, kind, n);
	}
	mc_context.active_cursor = NULL;
	mc_context.cursors = prev.next;

	MC_push(app, mc_context.view, kind, &prev);
	view_set_buffer_scroll(app, mc_context.view, scroll, SetBufferScroll_NoCursorChange);
}

//- Commands
CUSTOM_COMMAND_SIG(MC_error_fade)
CUSTOM_DOC("[MC] display error fades")
{
	View_ID view = get_active_view(app, Access_Always);
	Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
	Range_i64 range = get_view_range(app, view);
	buffer_post_fade(app, buffer, 0.667f, Ii64(range.min, range.max+1), fcolor_resolve(fcolor_id(defcolor_pop2)));
}

CUSTOM_COMMAND_SIG(MC_add_at_pos)
CUSTOM_DOC("[MC] adds multi-cursor at current pos")
{
	MC_insert(app);
}

CUSTOM_COMMAND_SIG(MC_del_at_pos)
CUSTOM_DOC("[MC] deletes multi-cursor at current pos")
{
	View_ID view = get_active_view(app, Access_Always);
	MC_remove(app, view_get_cursor_pos(app, view));
}

CUSTOM_COMMAND_SIG(MC_begin_multi)
CUSTOM_DOC("[MC] begins multi-cursors")
{
	MC_begin(app);
}

CUSTOM_COMMAND_SIG(MC_end_multi)
CUSTOM_DOC("[MC] ends multi-cursors")
{
	MC_end(app);
}

CUSTOM_COMMAND_SIG(MC_up_trail)
CUSTOM_DOC("[MC] moves up, leaving a multi-cursor behind it")
{
	MC_insert(app);
	move_up(app);
}

CUSTOM_COMMAND_SIG(MC_down_trail)
CUSTOM_DOC("[MC] moves down, leaving a multi-cursor behind it")
{
	MC_insert(app);
	move_down(app);
}

CUSTOM_COMMAND_SIG(MC_begin_multi_block)
CUSTOM_DOC("[MC] begins multi-cursor using cursor-mark block-rect")
{
	MC_end(app);

	View_ID view = get_active_view(app, Access_Always);
	Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
	i64 cursor_pos = view_get_cursor_pos(app, view);
	i64 mark_pos = view_get_mark_pos(app, view);
	Range_i64 range = Ii64(cursor_pos, mark_pos);

	i64 line_min = get_line_number_from_pos(app, buffer, range.min);
	i64 line_max = get_line_number_from_pos(app, buffer, range.max);
	Vec2_f32 p0 = view_relative_xy_of_pos(app, view, line_min, range.min);
	Vec2_f32 p1 = view_relative_xy_of_pos(app, view, line_min, range.max);
	Rect_f32 block_rect = Rf32(Min(p0.x, p1.x), Min(p0.y, p1.y), Max(p0.x, p1.x), Max(p0.y, p1.y));

	f32 line_advance = rect_height(block_rect)/f32(Max(1, line_max-line_min));
	f32 wid = rect_width(block_rect);
	block_rect = rect_inner(block_rect, -0.1f);

	b32 cursor_is_top = cursor_pos < mark_pos;
	i64 top_min_pos = max_i64;
	i64 top_max_pos = max_i64;
	i64 bot_min_pos = -1;
	i64 bot_max_pos = -1;
	for(i64 i=line_max; i>=line_min; i--){
		if(line_is_valid_and_blank(app, buffer, i)){ continue; }
		Vec2_f32 min_point = block_rect.p0 + V2f32(0, line_advance*(i-line_min));
		Vec2_f32 max_point = min_point + V2f32(wid,0);
		i64 min_pos = view_pos_at_relative_xy(app, view, line_min, min_point);
		i64 max_pos = view_pos_at_relative_xy(app, view, line_min, max_point);

		Vec2_f32 min_p = view_relative_xy_of_pos(app, view, line_min, min_pos);
		Vec2_f32 max_p = view_relative_xy_of_pos(app, view, line_min, max_pos);
		if(!rect_contains_point(block_rect, min_p) || !rect_contains_point(block_rect, max_p)){ continue; }

		top_min_pos = Min(top_min_pos, min_pos);
		top_max_pos = Min(top_max_pos, max_pos);
		bot_min_pos = Max(bot_min_pos, min_pos);
		bot_max_pos = Max(bot_max_pos, max_pos);
		MC_insert(app, min_pos, max_pos);
	}
	// Ensure all view cursor is along the left-edge of the block rect
	view_set_cursor(app, view, seek_pos(cursor_is_top ? top_min_pos : bot_min_pos));
	MC_begin(app);
	view_set_mark(app, view, seek_pos(cursor_is_top ? top_max_pos : bot_max_pos));
}

//- STUB
function void MC_tick(Application_Links *app, Frame_Info frame_info){
	default_tick(app, frame_info);
	MC_tick_inner(app, frame_info);
}

function i32 MC_buffer_edit_range(Application_Links *app, Buffer_ID buffer_id, Range_i64 new_range, Range_Cursor old_cursor_range){
	MC_buffer_edit_range_inner(app, buffer_id, new_range, old_cursor_range);
	return default_buffer_edit_range(app, buffer_id, new_range, old_cursor_range);
}

function void MC_render_caller(Application_Links *app, Frame_Info frame_info, View_ID view_id){
	default_render_caller(app, frame_info, view_id);
	if (view_id != mc_context.view){ return; }

	Buffer_ID buffer = view_get_buffer(app, view_id, Access_Always);
	Rect_f32 region = view_get_screen_rect(app, view_id);
	region = default_buffer_region(app, view_id, region);
	Rect_f32 prev_clip = draw_set_clip(app, region);

	Buffer_Scroll scroll = view_get_buffer_scroll(app, view_id);
	Text_Layout_ID text_layout_id = text_layout_create(app, buffer, region, scroll.position);

	MC_render_cursors(app, view_id, text_layout_id);

	text_layout_free(app, text_layout_id);
	draw_set_clip(app, prev_clip);
}

//- These are more to serve as an example
function void MC_setup_essential_mapping(Mapping *mapping, i64 global_id, i64 file_id, i64 code_id){
	MappingScope();
	SelectMapping(mapping);

	SelectMap(file_id);
	ParentMap(global_id);
	MC_BindTextInput(write_text_input);

	SelectMap(code_id);
	ParentMap(file_id);
	MC_BindTextInput(write_text_and_auto_indent);
}

function void MC_setup_default_mapping(Mapping *mapping, i64 global_id, i64 file_id, i64 code_id){
	MappingScope();
	SelectMapping(mapping);

	SelectMap(global_id);
	MC_Bind(save_all_dirty_buffers,        KeyCode_S, KeyCode_Control, KeyCode_Shift);
	MC_Bind(close_build_panel,             KeyCode_Comma, KeyCode_Alt);
	MC_Bind(build_in_build_panel,          KeyCode_M, KeyCode_Alt);
	MC_Bind(toggle_filebar,                KeyCode_B, KeyCode_Alt);

	MC_Bind(MC_end_multi,          KeyCode_Escape);

	SelectMap(file_id);
	Bind(MC_add_at_pos,            KeyCode_BackwardSlash, KeyCode_Control);
	Bind(MC_begin_multi,           KeyCode_Return, KeyCode_Control);
	Bind(MC_begin_multi_block,     KeyCode_L, KeyCode_Control, KeyCode_Shift);
	Bind(MC_up_trail,              KeyCode_Up, KeyCode_Control, KeyCode_Alt);
	Bind(MC_down_trail,            KeyCode_Down, KeyCode_Control, KeyCode_Alt);

	MC_Bind(delete_char,            KeyCode_Delete);
	MC_Bind(backspace_char,         KeyCode_Backspace);
	MC_Bind(move_up,                KeyCode_Up);
	MC_Bind(move_down,              KeyCode_Down);
	MC_Bind(move_left,              KeyCode_Left);
	MC_Bind(move_right,             KeyCode_Right);
	MC_Bind(seek_end_of_line,       KeyCode_End);
	MC_Bind(seek_beginning_of_line, KeyCode_Home);
	MC_Bind(move_line_up,                     KeyCode_Up, KeyCode_Alt);
	MC_Bind(move_line_down,                   KeyCode_Down, KeyCode_Alt);
	MC_Bind(backspace_alpha_numeric_boundary, KeyCode_Backspace, KeyCode_Control);
	MC_Bind(delete_alpha_numeric_boundary,    KeyCode_Delete, KeyCode_Control);
	MC_Bind(snipe_backward_whitespace_or_token_boundary, KeyCode_Backspace, KeyCode_Alt);
	MC_Bind(snipe_forward_whitespace_or_token_boundary,  KeyCode_Delete, KeyCode_Alt);
	MC_Bind(set_mark,                    KeyCode_Space, KeyCode_Control);
	MC_Bind(delete_range,                KeyCode_D, KeyCode_Control);
	MC_Bind(delete_line,                 KeyCode_D, KeyCode_Control, KeyCode_Shift);
	MC_Bind(center_view,                 KeyCode_E, KeyCode_Control);
	MC_Bind(left_adjust_view,            KeyCode_E, KeyCode_Control, KeyCode_Shift);
	MC_Bind(cursor_mark_swap,            KeyCode_M, KeyCode_Control);
	MC_Bind(save,                        KeyCode_S, KeyCode_Control);
	MC_Bind(save_all_dirty_buffers,      KeyCode_S, KeyCode_Control, KeyCode_Shift);

	SelectMap(code_id);
	ParentMap(file_id);
	MC_Bind(move_left_alpha_numeric_boundary,           KeyCode_Left, KeyCode_Control);
	MC_Bind(move_right_alpha_numeric_boundary,          KeyCode_Right, KeyCode_Control);
	MC_Bind(move_left_alpha_numeric_or_camel_boundary,  KeyCode_Left, KeyCode_Alt);
	MC_Bind(move_right_alpha_numeric_or_camel_boundary, KeyCode_Right, KeyCode_Alt);
	MC_Bind(comment_line_toggle,        KeyCode_Semicolon, KeyCode_Control);
	MC_Bind(auto_indent_range,          KeyCode_Tab, KeyCode_Control);
	MC_Bind(auto_indent_line_at_cursor, KeyCode_Tab, KeyCode_Shift);
	MC_Bind(write_block,                KeyCode_R, KeyCode_Alt);
	MC_Bind(write_todo,                 KeyCode_T, KeyCode_Alt);
	MC_Bind(write_note,                 KeyCode_Y, KeyCode_Alt);
	MC_Bind(open_long_braces,           KeyCode_LeftBracket, KeyCode_Control);
	MC_Bind(open_long_braces_semicolon, KeyCode_LeftBracket, KeyCode_Control, KeyCode_Shift);
	MC_Bind(open_long_braces_break,     KeyCode_RightBracket, KeyCode_Control, KeyCode_Shift);
}

#if MC_USE_STUB
function void MC_STUB_startup(Application_Links *app){
	default_startup(app);

	String_ID global_map_id = vars_save_string_lit("keys_global");
	String_ID file_map_id = vars_save_string_lit("keys_file");
	String_ID code_map_id = vars_save_string_lit("keys_code");
	MC_setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);

	MC_register(exit_4coder,                  MC_Command_Global);
	MC_register(default_try_exit,             MC_Command_Global);
	MC_register(mouse_wheel_change_face_size, MC_Command_Global);
	MC_register(swap_panels,                  MC_Command_Global);

	MC_register(copy,             MC_Command_CursorCopy);
	MC_register(cut,              MC_Command_CursorCopy);
	MC_register(paste_and_indent, MC_Command_CursorPaste);
}

void custom_layer_init(Application_Links *app){
	Thread_Context *tctx = get_thread_context(app);
	default_framework_init(app);

	MC_init(app);

	set_all_default_hooks(app);

	set_custom_hook(app, HookID_Tick, MC_tick);
	set_custom_hook(app, HookID_RenderCaller, MC_render_caller);
	set_custom_hook(app, HookID_BufferEditRange, MC_buffer_edit_range);

	String_ID global_map_id = vars_save_string_lit("keys_global");
	String_ID file_map_id = vars_save_string_lit("keys_file");
	String_ID code_map_id = vars_save_string_lit("keys_code");

	mapping_init(tctx, &framework_mapping);

	setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
	setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);

	MC_setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);

	{
		MappingScope();
		SelectMapping(&framework_mapping);
		SelectMap(global_map_id);
		BindCore(MC_STUB_startup, CoreCode_Startup);
	}
}
#endif