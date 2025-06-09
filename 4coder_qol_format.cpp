
CUSTOM_COMMAND_SIG(qol_reformat)
{
    View_ID view = get_active_view(app, Access_ReadWrite);
        Buffer_ID buffer = view_get_buffer(app, view, Access_ReadWrite);
    
        code_index_lock();
Code_Index_File *index = code_index_get_file(buffer);
    Code_Index_Nest *nest = index->nest_list.first;
    
  CodeIndexNest_Scope,
  CodeIndexNest_Paren,
  CodeIndexNest_Preprocessor,
  CodeIndexNest_Statement,

            code_index_unlock();
}