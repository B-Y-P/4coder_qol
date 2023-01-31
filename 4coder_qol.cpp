
#include "4coder_default_include.cpp"

#if !defined(META_PASS)
#include "generated/managed_id_metadata.cpp"
#endif

void custom_layer_init(Application_Links *app){
  Thread_Context *tctx = get_thread_context(app);

  default_framework_init(app);

  // Set up custom layer hooks
  {
    set_custom_hook(app, HookID_BufferViewerUpdate, default_view_adjust);

    set_custom_hook(app, HookID_ViewEventHandler, default_view_input_handler);
    set_custom_hook(app, HookID_Tick, default_tick);
    set_custom_hook(app, HookID_RenderCaller, default_render_caller);
    set_custom_hook(app, HookID_WholeScreenRenderCaller, default_whole_screen_render_caller);

    set_custom_hook(app, HookID_DeltaRule, fixed_time_cubic_delta);
    set_custom_hook_memory_size(app, HookID_DeltaRule,
                                delta_ctx_size(fixed_time_cubic_delta_memory_size));

    set_custom_hook(app, HookID_BufferNameResolver, default_buffer_name_resolution);

    set_custom_hook(app, HookID_BeginBuffer, default_begin_buffer);
    set_custom_hook(app, HookID_EndBuffer, end_buffer_close_jump_list);
    set_custom_hook(app, HookID_NewFile, default_new_file);
    set_custom_hook(app, HookID_SaveFile, default_file_save);
    set_custom_hook(app, HookID_BufferEditRange, default_buffer_edit_range);
    set_custom_hook(app, HookID_BufferRegion, default_buffer_region);
    set_custom_hook(app, HookID_ViewChangeBuffer, default_view_change_buffer);

    set_custom_hook(app, HookID_Layout, layout_unwrapped);
  }

  mapping_init(tctx, &framework_mapping);
  String_ID global_map_id = vars_save_string_lit("keys_global");
  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");

#if OS_MAC
  setup_mac_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#else
  setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
#endif
  setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
}