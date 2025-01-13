
CUSTOM_COMMAND_SIG(qol_startup)
CUSTOM_DOC("QOL command for responding to a startup event")
{
  ProfileScope(app, "qol startup");
  User_Input input = get_current_input(app);
  if (match_core_code(&input, CoreCode_Startup)){
    String_Const_u8_Array file_names = input.event.core.file_names;
    load_themes_default_folder(app);
    default_4coder_initialize(app, file_names);
    default_4coder_side_by_side_panels(app, file_names);

    /// NOTE(BYP): Not ideal, but I'd rather simplify others testing 4coder_qol
    String_ID global_map_id = vars_save_string_lit("keys_global");
    String_ID file_map_id = vars_save_string_lit("keys_file");
    String_ID code_map_id = vars_save_string_lit("keys_code");
    qol_setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
    qol_setup_essential_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);
    TAB_setup_default_mapping(&framework_mapping, global_map_id, file_map_id, code_map_id);

    b32 auto_load = def_get_config_b32(vars_save_string_lit("automatically_load_project"));
    if (auto_load){
      load_project(app);
    }

    qol_temp_buffer = create_buffer(app, string_u8_litexpr("*qol_temp*"),
                                    BufferCreate_Background | BufferCreate_AlwaysNew | BufferCreate_NeverAttachToFile);
    buffer_set_setting(app, qol_temp_buffer, BufferSetting_Unimportant, true);
    buffer_set_setting(app, qol_temp_buffer, BufferSetting_Unkillable, true);
    buffer_set_setting(app, qol_temp_buffer, BufferSetting_ReadOnly, false);

    TAB_startup_inner(app);
    qol_lister_init(app);
  }

  {
    def_audio_init();
  }

  {
    def_enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
    clear_all_layouts(app);
  }

  Face_Description desc = get_global_face_description(app);
  desc.parameters.pt_size -= 4;
  qol_small_face = try_create_new_face(app, &desc);

  {
    String_Const_u8 non_word_chars = string_u8_litexpr(" \t\n/\\()\"':,.;<>~!@#$%^&*|+=[]{}`?-");
    for (u64 i = 0; i < non_word_chars.size; i += 1){
      Character_Predicate pred = character_predicate_from_character(non_word_chars.str[i]);
      character_predicate_non_word = character_predicate_or(&pred, &character_predicate_non_word);
    }
    character_predicate_word = character_predicate_not(&character_predicate_non_word);
  }

  Scratch_Block scratch(app);
  set_active_color(get_color_table_by_name(def_get_config_string(scratch, vars_save_string_lit("default_theme_name"))));
  qol_cur_colors = qol_color_table_init(app);
  qol_nxt_colors = qol_color_table_init(app);
  qol_color_table_copy(qol_cur_colors, active_color_table);
  qol_color_table_copy(qol_nxt_colors, active_color_table);
}

function void
qol_code_index_update_tick(Application_Links *app){
  Scratch_Block scratch(app);
  for (Buffer_Modified_Node *node = global_buffer_modified_set.first;
       node != 0;
       node = node->next){
    Temp_Memory_Block temp(scratch);
    Buffer_ID buffer_id = node->buffer;

    String_Const_u8 contents = push_whole_buffer(app, scratch, buffer_id);
    Token_Array tokens = get_token_array_from_buffer(app, buffer_id);
    if (tokens.count == 0){
      continue;
    }

    Arena arena = make_arena_system(KB(16));
    Code_Index_File *index = push_array_zero(&arena, Code_Index_File, 1);
    index->buffer = buffer_id;

    Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
    Buffer_Lang language = *scope_attachment(app, scope, buffer_language, Buffer_Lang);
    Generic_Parse_State state = {};
    generic_parse_init(app, &arena, contents, &tokens, &state);
    state.do_cpp_parse = true;
    parse_full_input_lang(index, &state, max_i32, language);

    code_index_lock();
    code_index_set_file(buffer_id, arena, index);
    code_index_unlock();
    buffer_clear_layout_cache(app, buffer_id);
  }

  buffer_modified_set_clear();
}

function void
qol_tick(Application_Links *app, Frame_Info frame_info){
  qol_code_index_update_tick(app);
  code_index_update_tick(app);

  if (tick_all_fade_ranges(app, frame_info.animation_dt)){
    animate_in_n_milliseconds(app, 0);
  }

  {
    b32 enable_virtual_whitespace = def_get_config_b32(vars_save_string_lit("enable_virtual_whitespace"));
    if (enable_virtual_whitespace != def_enable_virtual_whitespace){
      def_enable_virtual_whitespace = enable_virtual_whitespace;
      clear_all_layouts(app);
    }
  }


  f32 dt = frame_info.animation_dt;

  qol_interp(qol_cur_cursor_pos, qol_nxt_cursor_pos, dt, 1e-14f);
  if (!near_zero(qol_cur_cursor_pos - qol_nxt_cursor_pos, 0.5f)){
    animate_in_n_milliseconds(app, 0);
  }

  qol_tick_colors(app, frame_info);

  qol_tick_lister(app, frame_info);

  MC_tick_inner(app, frame_info);
  TAB_tick_inner(app, frame_info);
}

BUFFER_HOOK_SIG(qol_file_save){
  default_file_save(app, buffer_id);

  Scratch_Block scratch(app);
  String_Const_u8 path = push_buffer_file_name(app, scratch, buffer_id);
  String_Const_u8 name = string_front_of_path(path);

  if (qol_is_theme_file(name)){
    Color_Table color_table = make_color_table(app, &global_theme_arena);
    Config *config = theme_parse__buffer(app, scratch, buffer_id, &global_theme_arena, &color_table);
    String_Const_u8 error_text = config_stringize_errors(app, scratch, config);
    comp_error(app, error_text);

    if (error_text.size > 0){
      print_message(app, error_text);
    }
    else{
      qol_color_table_copy(qol_nxt_colors, color_table);
    }
  }

  if (string_match(name, string_u8_litexpr("config.4coder"))){
    View_ID view = get_active_view(app, Access_Always);
    view_enqueue_command_function(app, view, qol_reload_config);
  }

  if (string_match(name, string_u8_litexpr("project.4coder"))){
    View_ID view = get_active_view(app, Access_Always);
    view_enqueue_command_function(app, view, qol_reload_project);
  }

  if (string_match(name, string_u8_litexpr("bindings.4coder"))){
    View_ID view = get_active_view(app, Access_Always);
    view_enqueue_command_function(app, view, qol_reload_bindings);
  }

  return 0;
}

BUFFER_HOOK_SIG(qol_begin_buffer)
{
  ProfileScope(app, "begin buffer");

  Scratch_Block scratch(app);
  Buffer_Lang language = Lang_None;

  String_Const_u8 file_name = push_buffer_file_name(app, scratch, buffer_id);
  if (file_name.size > 0){
    String_Const_u8 treat_as_code_string = def_get_config_string(scratch, vars_save_string_lit("treat_as_code"));
    String_Const_u8_Array extensions = parse_extension_line_to_extension_list(scratch, treat_as_code_string);
    String_Const_u8 ext = string_file_extension(file_name);
    for (i32 i = 0; i < extensions.count; ++i){
      if (string_match(ext, extensions.strings[i])){
        if (string_match(ext, string_u8_litexpr("odin"))){
          language = Lang_Odin;
        }

        if (string_match(ext, string_u8_litexpr("cpp")) ||
            string_match(ext, string_u8_litexpr("h")) ||
            string_match(ext, string_u8_litexpr("c")) ||
            string_match(ext, string_u8_litexpr("hpp")) ||
            string_match(ext, string_u8_litexpr("cc")) ||
            string_match(ext, string_u8_litexpr("4coder"))){
          language = Lang_Cpp;
        }
        break;
      }
    }
  }

  String_ID file_map_id = vars_save_string_lit("keys_file");
  String_ID code_map_id = vars_save_string_lit("keys_code");

  b32 treat_as_code = (language != Lang_None);
  Command_Map_ID map_id = (treat_as_code)?(code_map_id):(file_map_id);
  Line_Ending_Kind setting = guess_line_ending_kind_from_buffer(app, buffer_id);

  Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
  *scope_attachment(app, scope, buffer_map_id, Command_Map_ID) = map_id;
  *scope_attachment(app, scope, buffer_language, Buffer_Lang) = language;
  *scope_attachment(app, scope, buffer_eol_setting, Line_Ending_Kind) = setting;

  // NOTE(allen): Decide buffer settings
  b32 wrap_lines = true;
  b32 use_lexer = false;
  if (treat_as_code){
    wrap_lines = def_get_config_b32(vars_save_string_lit("enable_code_wrapping"));
    use_lexer = true;
  }

  String_Const_u8 buffer_name = push_buffer_base_name(app, scratch, buffer_id);
  if (buffer_name.size > 0 && buffer_name.str[0] == '*' && buffer_name.str[buffer_name.size - 1] == '*'){
    wrap_lines = def_get_config_b32(vars_save_string_lit("enable_output_wrapping"));
  }

  if (language != Lang_None){
    ProfileBlock(app, "begin buffer kick off lexer");
    Async_Task *lex_task_ptr = scope_attachment(app, scope, buffer_lex_task, Async_Task);

    Async_Task_Function_Type *lex = (Async_Task_Function_Type*)lang_lex_async[language];
    *lex_task_ptr = async_task_no_dep(&global_async_system, lex, make_data_struct(&buffer_id));
  }

  {
    b32 *wrap_lines_ptr = scope_attachment(app, scope, buffer_wrap_lines, b32);
    *wrap_lines_ptr = wrap_lines;
  }

  if (use_lexer){
    buffer_set_layout(app, buffer_id, layout_virt_indent_index_generic);
  }
  else{
    if (treat_as_code){
      buffer_set_layout(app, buffer_id, layout_virt_indent_literal_generic);
    }
    else{
      buffer_set_layout(app, buffer_id, layout_generic);
    }
  }

  // no meaning for return
  return(0);
}

BUFFER_EDIT_RANGE_SIG(qol_buffer_edit_range)
{
  MC_buffer_edit_range_inner(app, buffer_id, new_range, old_cursor_range);
  // buffer_id, new_range, original_size
  ProfileScope(app, "qol edit range");

  Range_i64 old_range = Ii64(old_cursor_range.min.pos, old_cursor_range.max.pos);

  buffer_shift_fade_ranges(buffer_id, old_range.max, (new_range.max - old_range.max));

  {
    code_index_lock();
    Code_Index_File *file = code_index_get_file(buffer_id);
    if (file != 0){
      code_index_shift(file, old_range, range_size(new_range));
    }
    code_index_unlock();
  }

  i64 insert_size = range_size(new_range);
  i64 text_shift = replace_range_shift(old_range, insert_size);

  Scratch_Block scratch(app);

  Managed_Scope scope = buffer_get_managed_scope(app, buffer_id);
  Async_Task *lex_task_ptr = scope_attachment(app, scope, buffer_lex_task, Async_Task);
  Buffer_Lang language = *scope_attachment(app, scope, buffer_language, Buffer_Lang);

  Base_Allocator *allocator = managed_scope_allocator(app, scope);
  b32 do_full_relex = false;

  if (async_task_is_running_or_pending(&global_async_system, *lex_task_ptr)){
    async_task_cancel(app, &global_async_system, *lex_task_ptr);
    buffer_unmark_as_modified(buffer_id);
    do_full_relex = true;
    *lex_task_ptr = 0;
  }

  Token_Array *ptr = scope_attachment(app, scope, attachment_tokens, Token_Array);
  if (ptr != 0 && ptr->tokens != 0){
    ProfileBlockNamed(app, "attempt resync", profile_attempt_resync);

    i64 token_index_first = token_relex_first(ptr, old_range.first, 1);
    i64 token_index_resync_guess =
      token_relex_resync(ptr, old_range.one_past_last, 16);

    if (token_index_resync_guess - token_index_first >= 4000){
      do_full_relex = true;
    }
    else{
      Token *token_first = ptr->tokens + token_index_first;
      Token *token_resync = ptr->tokens + token_index_resync_guess;

      Range_i64 relex_range = Ii64(token_first->pos, token_resync->pos + token_resync->size + text_shift);
      String_Const_u8 partial_text = push_buffer_range(app, scratch, buffer_id, relex_range);

      Token_List relex_list = lex_full_input_lang(scratch, partial_text, language);
      if (relex_range.one_past_last < buffer_get_size(app, buffer_id)){
        token_drop_eof(&relex_list);
      }

      Token_Relex relex = token_relex(relex_list, relex_range.first - text_shift, ptr->tokens, token_index_first, token_index_resync_guess);

      ProfileCloseNow(profile_attempt_resync);

      if (!relex.successful_resync){
        do_full_relex = true;
      }
      else{
        ProfileBlock(app, "apply resync");

        i64 token_index_resync = relex.first_resync_index;

        Range_i64 head = Ii64(0, token_index_first);
        Range_i64 replaced = Ii64(token_index_first, token_index_resync);
        Range_i64 tail = Ii64(token_index_resync, ptr->count);
        i64 resynced_count = (token_index_resync_guess + 1) - token_index_resync;
        i64 relexed_count = relex_list.total_count - resynced_count;
        i64 tail_shift = relexed_count - (token_index_resync - token_index_first);

        i64 new_tokens_count = ptr->count + tail_shift;
        Token *new_tokens = base_array(allocator, Token, new_tokens_count);

        Token *old_tokens = ptr->tokens;
        block_copy_array_shift(new_tokens, old_tokens, head, 0);
        token_fill_memory_from_list(new_tokens + replaced.first, &relex_list, relexed_count);
        for (i64 i = 0, index = replaced.first; i < relexed_count; i += 1, index += 1){
          new_tokens[index].pos += relex_range.first;
        }
        for (i64 i = tail.first; i < tail.one_past_last; i += 1){
          old_tokens[i].pos += text_shift;
        }
        block_copy_array_shift(new_tokens, ptr->tokens, tail, tail_shift);

        base_free(allocator, ptr->tokens);

        ptr->tokens = new_tokens;
        ptr->count = new_tokens_count;
        ptr->max = new_tokens_count;

        buffer_mark_as_modified(buffer_id);
      }
    }
  }

  if (do_full_relex){
    Async_Task_Function_Type *lex = (Async_Task_Function_Type*)lang_lex_async[language];
    *lex_task_ptr = async_task_no_dep(&global_async_system, lex, make_data_struct(&buffer_id));
  }

  // no meaning for return
  return(0);
}
