
#include "4coder_default_include.h"

//#define SNIPPET_EXPANSION "path/to/snippet.inc"

#define AUTO_CENTER_AFTER_JUMPS false

#include "4coder_qol_token.h"
#include "4coder_qol_lister.h"
#define run_lister qol_run_lister

CUSTOM_ID(colors, defcolor_type);
CUSTOM_ID(colors, defcolor_function);
CUSTOM_ID(colors, defcolor_macro);
CUSTOM_ID(colors, defcolor_enum);
CUSTOM_ID(colors, defcolor_global);
CUSTOM_ID(colors, defcolor_control);
CUSTOM_ID(colors, defcolor_primitive);
CUSTOM_ID(colors, defcolor_struct);
CUSTOM_ID(colors, defcolor_non_text);
CUSTOM_ID(colors, defcolor_operator);

#include "4coder_default_include.cpp"

#include "4coder_qol_jumps.cpp"

global b32 qol_opened_brace = false;
global u8 qol_target_char;
global Buffer_Cursor qol_col_cursor = {-1};

global Vec2_f32 qol_cur_cursor_pos;
global Vec2_f32 qol_nxt_cursor_pos;

global Color_Table qol_cur_colors;
global Color_Table qol_nxt_colors;

global Face_ID qol_small_face;

global Buffer_ID qol_temp_buffer;

global u8 g_qol_bot_buffer[1024];
global String_u8 g_qol_bot_string = Su8(g_qol_bot_buffer, 0, sizeof(g_qol_bot_buffer));

global Character_Predicate character_predicate_word = {};
global Character_Predicate character_predicate_non_word = {};

#include "4coder_qol_helper.h"
#include "4coder_qol_block.cpp"

#include "4coder_qol_colors.cpp"
#include "4coder_qol_token.cpp"

function void qol_setup_essential_mapping(Mapping *mapping, i64 global_id, i64 file_id, i64 code_id);
function void qol_setup_default_mapping(Mapping *mapping, i64 global_id, i64 file_id, i64 code_id);

#include "4coder_qol_commands.cpp"
#include "4coder_qol_draw.cpp"
#include "4coder_qol_lister.cpp"

#include "4coder_qol_bindings.cpp"
#include "4coder_qol_hooks.cpp"

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

void custom_layer_init(Application_Links *app){
  Thread_Context *tctx = get_thread_context(app);

  default_framework_init(app);

  // Set up custom layer hooks
  {
    set_custom_hook(app, HookID_BufferViewerUpdate, default_view_adjust);

    set_custom_hook(app, HookID_ViewEventHandler, qol_view_input_handler);
    set_custom_hook(app, HookID_Tick, qol_tick);
    set_custom_hook(app, HookID_RenderCaller, qol_render_caller);
    set_custom_hook(app, HookID_WholeScreenRenderCaller, qol_whole_screen_render_caller);

    set_custom_hook(app, HookID_DeltaRule, fixed_time_cubic_delta);
    set_custom_hook_memory_size(app, HookID_DeltaRule,
                                delta_ctx_size(fixed_time_cubic_delta_memory_size));

    set_custom_hook(app, HookID_BufferNameResolver, default_buffer_name_resolution);

    set_custom_hook(app, HookID_BeginBuffer, default_begin_buffer);
    set_custom_hook(app, HookID_EndBuffer, end_buffer_close_jump_list);
    set_custom_hook(app, HookID_NewFile, default_new_file);
    set_custom_hook(app, HookID_SaveFile, qol_file_save);
    set_custom_hook(app, HookID_BufferEditRange, default_buffer_edit_range);
    set_custom_hook(app, HookID_BufferRegion, qol_buffer_region);
    set_custom_hook(app, HookID_ViewChangeBuffer, default_view_change_buffer);

    set_custom_hook(app, HookID_Layout, layout_unwrapped);
  }

  mapping_init(tctx, &framework_mapping);
  String_ID global_map_id = vars_save_string_lit("keys_global");
  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");
  qol_setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
}
