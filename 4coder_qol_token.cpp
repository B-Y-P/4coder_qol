
function b32
qol_highlight_token(Token_Base_Kind kind){
  switch(kind){
    case TokenBaseKind_Keyword:
    case TokenBaseKind_Identifier:
    case qol_TokenKind_Primitive:
    case qol_TokenKind_Control:
    case qol_TokenKind_Struct:
    return true;
  }
  return false;
}

function FColor
qol_get_token_color_cpp(Token token){
  Managed_ID color = defcolor_text_default;
  switch (token.kind){
    case TokenBaseKind_Preprocessor:   { color = defcolor_preproc;        }break;
    case TokenBaseKind_Keyword:        { color = defcolor_keyword;        }break;
    case TokenBaseKind_Comment:        { color = defcolor_comment;        }break;
    case TokenBaseKind_LiteralString:  { color = defcolor_str_constant;   }break;
    case TokenBaseKind_LiteralInteger: { color = defcolor_int_constant;   }break;
    case TokenBaseKind_LiteralFloat:   { color = defcolor_float_constant; }break;
    case TokenBaseKind_Operator:       { color = defcolor_operator;       }break;

    case TokenBaseKind_ScopeOpen:
    case TokenBaseKind_ScopeClose:
    case TokenBaseKind_ParentheticalOpen:
    case TokenBaseKind_ParentheticalClose:
    case TokenBaseKind_StatementClose:{ color = defcolor_non_text; } break;

    case qol_TokenKind_Control:{ color = defcolor_control; }break;
    case qol_TokenKind_Primitive:{ color = defcolor_primitive; }break;
    case qol_TokenKind_Struct:{ color = defcolor_struct; }break;
  }
  // specifics override generals
  switch (token.sub_kind){
    case TokenCppKind_LiteralTrue:
    case TokenCppKind_LiteralFalse:
    {
      color = defcolor_bool_constant;
    }break;
    case TokenCppKind_LiteralCharacter:
    case TokenCppKind_LiteralCharacterWide:
    case TokenCppKind_LiteralCharacterUTF8:
    case TokenCppKind_LiteralCharacterUTF16:
    case TokenCppKind_LiteralCharacterUTF32:
    {
      color = defcolor_char_constant;
    }break;
    case TokenCppKind_PPIncludeFile:
    {
      color = defcolor_include;
    }break;
  }
  return fcolor_id(color);
}

function void
qol_draw_cpp_token_colors(Application_Links *app, Text_Layout_ID text_layout_id, Token_Array *array){
  Range_i64 visible_range = text_layout_get_visible_range(app, text_layout_id);
  Token_Iterator_Array it = token_iterator_pos(0, array, visible_range.first);
  for (;;){
    Token *token = token_it_read(&it);
    if (token->pos > visible_range.max){ break; }
    FColor color = qol_get_token_color_cpp(*token);
    paint_text_color(app, text_layout_id, Ii64(token), fcolor_resolve(color));
    if(!token_it_inc_all(&it)){ break; }
  }
}
