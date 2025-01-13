function bool
odin_insert_semi(Token *token){
  switch(token->kind){
    case qol_TokenKind_Control:         // if else return defer etc.
    case TokenBaseKind_LiteralInteger:  // .Integer
    case TokenBaseKind_LiteralFloat:    // .Float, .Imag
    case TokenBaseKind_LiteralString:   // .Rune, .String
    return true;
    default: break;
  }

  switch(token->sub_kind){
    case TokenOdinKind_Identifier:   // .Ident
    case TokenOdinKind_Directive:    // .Ident
    case TokenOdinKind_Ignore:       // '_'
    case TokenOdinKind_Context:      // .Context
    case TokenOdinKind_TypeID:       // .Typeid
    case TokenOdinKind_Break:        // .Break
    case TokenOdinKind_Continue:     // .Continue
    case TokenOdinKind_Fallthrough:  // .Fallthrough
    case TokenOdinKind_Return:       // .Return
    case TokenOdinKind_Undef:        // .Undef
    case TokenOdinKind_Question:     // .Question
    case TokenOdinKind_Ptr:          // .Pointer
    case TokenOdinKind_ParenCl:      // .Close_Paren
    case TokenOdinKind_BrackCl:      // .Close_Bracket
    case TokenOdinKind_BraceCl:      // .Close_Brace
    case TokenOdinKind_Inc:          // .Increment
    case TokenOdinKind_Dec:          // .Decrement
    return true;
    default: break;
  }
  return false;
}

function void
odin_parse_enum_list(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent, Token* open){
  generic_parse_inc(state);
  Code_Index_Nest *nest = push_array_zero(state->arena, Code_Index_Nest, 1);
  nest->kind = CodeIndexNest_Scope;
  nest->is_closed = false;
  nest->open = Ii64(open);
  nest->close = Ii64(max_i64);
  nest->file = index;
  nest->parent = parent;
  state->scope_counter += 1;

  for(;;){
    generic_parse_skip_soft_tokens(index, state);
    Token *token = token_it_read(&state->it);
    if (token == 0 || state->finished){ break; }

    if (token->kind == TokenBaseKind_ScopeClose){
      nest->is_closed = true;
      nest->close = Ii64(token);
      generic_parse_inc(state);
      generic_parse_skip_soft_tokens(index, state);
      break;
    }
    if (token->kind == TokenBaseKind_Identifier){
      index_new_note(index, state, Ii64(token), CodeIndexNote_Enum, parent);
      generic_parse_inc(state);
      generic_parse_scan_comma(index, state);
      continue;
    }

    generic_parse_inc(state);
  }

  state->scope_counter -= 1;
  nest->nest_array = code_index_nest_ptr_array_from_list(state->arena, &nest->nest_list);
  code_index_push_nest(&index->nest_list, nest);
}

function void
odin_parse_enum(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(index, state);
  if (state->finished){ return; }

  Token *token = token_it_read(&state->it);
  if (token == 0){ return; }

  if (token->kind == qol_TokenKind_Primitive || token->sub_kind == TokenOdinKind_Identifier){
    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(index, state);
    token = token_it_read(&state->it);
  }

  if (token->sub_kind == TokenOdinKind_BraceOp){
    odin_parse_enum_list(index, state, parent, token);
  }
}

function void
odin_parse_iden(Code_Index_File *index, Generic_Parse_State *state, Code_Index_Nest *parent){
  Token *iden = token_it_read(&state->it);
  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(index, state);
  if (state->finished){ return; }

  Token *peek = token_it_read(&state->it);
  if (peek == 0 || peek->sub_kind != TokenOdinKind_Colon){ return; }

  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(index, state);
  peek = token_it_read(&state->it);
  if (peek == 0 || peek->sub_kind != TokenOdinKind_Colon){ return; }

  generic_parse_inc(state);
  generic_parse_skip_soft_tokens(index, state);
  Token *token = token_it_read(&state->it);
  if (token == 0){ return; }

  while (token->sub_kind == TokenOdinKind_Directive){
    generic_parse_inc(state);
    generic_parse_skip_soft_tokens(index, state);
    token = token_it_read(&state->it);
    if (token == 0){ return; }
  }

  if (token->sub_kind == TokenOdinKind_Ptr ||
      token->sub_kind == TokenOdinKind_Distinct ||
      token->sub_kind == TokenOdinKind_BraceOp ||
      token->kind == qol_TokenKind_Struct){
    generic_parse_inc(state);
    index_new_note(index, state, Ii64(iden), CodeIndexNote_Type, parent);
    if (token->sub_kind == TokenOdinKind_Enum){
      odin_parse_enum(index, state, parent);
    }
  }
  else if (token->sub_kind == TokenOdinKind_Proc){
    generic_parse_inc(state);
    index_new_note(index, state, Ii64(iden), CodeIndexNote_Function, parent);
  }
  else {
    index_new_note(index, state, Ii64(iden), CodeIndexNote_Global, parent);
  }
}

function Code_Index_Nest*
odin_parse_statement(Code_Index_File *index, Generic_Parse_State *state){
  Token *token = token_it_read(&state->it);
  Code_Index_Nest *result = push_array_zero(state->arena, Code_Index_Nest, 1);
  result->kind = CodeIndexNest_Statement;
  result->open = Ii64(token->pos);
  result->close = Ii64(max_i64);
  result->file = index;
  state->in_statement = true;

  for (;;){
    Token *token_prev = token;
    u8 *line_before = state->prev_line_start;
    generic_parse_skip_soft_tokens(index, state);
    token = token_it_read(&state->it);
    if (token == 0 || state->finished){
      break;
    }
    b32 newline = (line_before != state->prev_line_start);

    if (token->kind == TokenBaseKind_ScopeOpen ||
        token->kind == TokenBaseKind_ScopeClose ||
        token->kind == TokenBaseKind_ParentheticalOpen ||
        token->kind == TokenBaseKind_ParentheticalClose ||
        (newline && odin_insert_semi(token)))
    {
      result->is_closed = true;
      result->close = Ii64(token_prev->pos);
      break;
    }

    if (token->kind == TokenBaseKind_StatementClose){
      result->is_closed = true;
      result->close = Ii64(token);
      generic_parse_inc(state);
      break;
    }

    generic_parse_inc(state);
  }

  state->in_statement = false;

  return(result);
}

function b32
odin_parse_full_input_breaks(Code_Index_File *index, Generic_Parse_State *state, i32 limit){
  b32 result = false;

  i64 first_index = token_it_index(&state->it);
  i64 one_past_last_index = first_index + limit;

  // TODO: Move the stack into Generic_Parse_State, and abstract some helpers
  Code_Index_Nest *stack = 0;

  for (;;){
    generic_parse_skip_soft_tokens(index, state);
    Token *token = token_it_read(&state->it);
    String_Const_u8 lexeme = string_substring(state->contents, Ii64(token));

    if (token == 0 || state->finished){
      result = true;
      break;
    }

    /// Potentially index at global scope
    if (stack == 0 && token->sub_kind == TokenOdinKind_Import){
      generic_parse_inc(state);
      generic_parse_skip_soft_tokens(index, state);
      Token *peek = token_it_read(&state->it);
      if (peek == 0 || peek->kind == TokenBaseKind_Identifier){
        index_new_note(index, state, Ii64(peek), CodeIndexNote_Type, 0);
        generic_parse_inc(state);
      }
    }
    if (stack == 0 && token->sub_kind == TokenOdinKind_Identifier){
      odin_parse_iden(index, state, 0);
    }
    else if (token->kind == TokenBaseKind_ScopeOpen){
      Code_Index_Nest *nest = push_array_zero(state->arena, Code_Index_Nest, 1);
      nest->kind = CodeIndexNest_Scope;
      nest->open = Ii64(token);
      nest->close = Ii64(max_i64);
      nest->file = index;
      nest->parent = stack;
      state->scope_counter += 1;
      sll_stack_push(stack, nest);
      generic_parse_inc(state);
    }
    else if (token->kind == TokenBaseKind_ScopeClose){
      for (;;){
        if (stack == 0 || stack->kind == CodeIndexNest_Scope){ break; }
        state->paren_counter -= 1;

        Code_Index_Nest *nest = stack;
        sll_stack_pop(stack);
        nest->next = 0;
        nest->nest_array = code_index_nest_ptr_array_from_list(state->arena, &nest->nest_list);
        state->paren_counter -= 1;
        nest->parent = stack;
        Code_Index_Nest_List *list = (stack ? &stack->nest_list : &index->nest_list);
        code_index_push_nest(list, nest);
      }

      if (stack && stack->kind == CodeIndexNest_Scope){
        Code_Index_Nest *nest = stack;
        nest->is_closed = true;
        nest->close = Ii64(token);
        sll_stack_pop(stack);
        nest->next = 0;
        nest->nest_array = code_index_nest_ptr_array_from_list(state->arena, &nest->nest_list);
        state->scope_counter -= 1;
        Code_Index_Nest_List *list = (stack ? &stack->nest_list : &index->nest_list);
        code_index_push_nest(list, nest);
      }
      generic_parse_inc(state);
    }
    else if (token->kind == TokenBaseKind_ParentheticalOpen){
      Code_Index_Nest *nest = push_array_zero(state->arena, Code_Index_Nest, 1);
      nest->kind = CodeIndexNest_Paren;
      nest->open = Ii64(token);
      nest->close = Ii64(max_i64);
      nest->file = index;
      nest->parent = stack;
      state->paren_counter += 1;
      sll_stack_push(stack, nest);
      generic_parse_inc(state);
    }
    else if (token->kind == TokenBaseKind_ParentheticalClose){
      if (stack && stack->kind == CodeIndexNest_Paren){
        Code_Index_Nest *nest = stack;
        nest->is_closed = true;
        nest->close = Ii64(token);
        sll_stack_pop(stack);
        nest->next = 0;
        nest->nest_array = code_index_nest_ptr_array_from_list(state->arena, &nest->nest_list);
        state->paren_counter -= 1;
        Code_Index_Nest_List *list = (stack ? &stack->nest_list : &index->nest_list);
        code_index_push_nest(list, nest);
      }
      generic_parse_inc(state);
    }
    else if (stack != 0){
      Code_Index_Nest *stmnt = odin_parse_statement(index, state);
      stmnt->parent = stack;
      code_index_push_nest(&stack->nest_list, stmnt);
    }
    else{
      generic_parse_inc(state);
    }

    i64 index = token_it_index(&state->it);
    if (index >= one_past_last_index){
      token = token_it_read(&state->it);
      if (token == 0){
        result = true;
      }
      break;
    }
  }

  for (;;){
    if (stack == 0){ break; }

    Code_Index_Nest *nest = stack;
    state->paren_counter -= (nest->kind == CodeIndexNest_Paren);
    state->scope_counter -= (nest->kind == CodeIndexNest_Scope);

    sll_stack_pop(stack);
    nest->next = 0;
    nest->nest_array = code_index_nest_ptr_array_from_list(state->arena, &nest->nest_list);
    state->paren_counter -= 1;
    nest->parent = stack;
    Code_Index_Nest_List *list = (stack ? &stack->nest_list : &index->nest_list);
    code_index_push_nest(list, nest);
  }

  if (result){
    index->nest_array = code_index_nest_ptr_array_from_list(state->arena, &index->nest_list);
    index->note_array = code_index_note_ptr_array_from_list(state->arena, &index->note_list);
  }

  return result;
}