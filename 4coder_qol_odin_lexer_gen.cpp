
#define LANG_NAME_LOWER odin
#define LANG_NAME_CAMEL Odin

#include "lexer_generator/4coder_lex_gen_main.cpp"
#include "4coder_qol_token.h"

internal void
build_language_model(void){
  u8 utf8[129];
  smh_utf8_fill(utf8);

  smh_set_base_character_names();
  smh_typical_tokens();

  /// NOTE: to have any chance of doing this "correctly"
  // the documentation is only good for self-induced gaslighting
  // You will have to sift through odin's tokenizer.cpp and tokenizer.odin

  // Odin Names
  sm_char_name('!', "Not");
  sm_char_name('&', "And");
  sm_char_name('|', "Or");
  sm_char_name('%', "Mod");
  sm_char_name('~', "Xor");
  sm_char_name('^', "Ptr");
  sm_char_name('?', "Question");
  sm_char_name('/', "Div");

  // Odin Direct Token Kinds
  sm_select_base_kind(TokenBaseKind_Identifier);
  sm_direct_token_kind("Parametric");
  sm_direct_token_kind("Directive");

  sm_select_base_kind(TokenBaseKind_Comment);
  sm_direct_token_kind("MultiComment");
  sm_direct_token_kind("LineComment");

  sm_select_base_kind(TokenBaseKind_Whitespace);
  sm_direct_token_kind("Backslash");

  sm_select_base_kind(TokenBaseKind_LiteralInteger);
  sm_direct_token_kind("LiteralIntegerBin");  // 0b
  sm_direct_token_kind("LiteralIntegerOct");  // 0o
  sm_direct_token_kind("LiteralIntegerDec");  // 0d or default
  sm_direct_token_kind("LiteralIntegerDoz");  // 0z
  sm_direct_token_kind("LiteralIntegerHex");  // 0x   or 0h for hex-float

  sm_select_base_kind(TokenBaseKind_LiteralFloat);
  sm_direct_token_kind("LiteralFloat");
  sm_direct_token_kind("LiteralQuaternion");  // 1i + 1j + 1k

  sm_select_base_kind(TokenBaseKind_LiteralString);
  sm_direct_token_kind("LiteralString");
  sm_direct_token_kind("LiteralStringRaw");
  sm_direct_token_kind("LiteralCharacter");

  sm_select_base_kind(TokenBaseKind_Keyword);
  sm_direct_token_kind("KeywordGeneric");

  // Odin Operators
  Operator_Set *main_ops = sm_begin_op_set();

  sm_select_base_kind(TokenBaseKind_ScopeOpen);
  sm_op("{");
  sm_select_base_kind(TokenBaseKind_ScopeClose);
  sm_op("}");
  sm_select_base_kind(TokenBaseKind_ParentheticalOpen);
  sm_op("(");
  sm_op("[");
  sm_select_base_kind(TokenBaseKind_ParentheticalClose);
  sm_op(")");
  sm_op("]");
  sm_select_base_kind(TokenBaseKind_StatementClose);
  sm_op(";");

  sm_select_base_kind(TokenBaseKind_Operator);
  //sm_op(":=");    // "Type-inference is stored in the balls"
  sm_op(":");
  sm_op(".");
  sm_op("@");
  sm_op("^");
  sm_op("->", "Arrow");
  sm_op("+");
  sm_op("-");
  sm_op("!");
  sm_op("~");
  sm_op("*");
  sm_op("&");
  sm_op("&~", "AndNot");
  sm_op("/");
  sm_op("%");
  sm_op("%%");
  sm_op("---", "Undef");

  sm_char_name('<', "Less");
  sm_char_name('>', "Grtr");
  sm_op("<");
  sm_op("<=");
  sm_op(">");
  sm_op(">=");
  sm_op("==");
  sm_op("!=");
  sm_op("..=", "RangeFull");
  sm_op("..<", "RangeHalf");
  sm_op("..", "Variadic");

  sm_op("<<", "Shl");
  sm_op(">>", "Shr");
  sm_op("|");
  sm_op("&&");
  sm_op("||");
  sm_op("?");
  sm_op("=");

  sm_op("+=");
  sm_op("-=");
  sm_op("*=");
  sm_op("/=");
  sm_op("%=");
  sm_op("%%=");
  sm_op("&~=", "AndNotEq");
  sm_op("&=");
  sm_op("|=");
  sm_op("~=");
  sm_op("<<=");
  sm_op(">>=");
  sm_op("&&=");
  sm_op("||=");
  sm_op("++", "Inc");
  sm_op("--", "Dec");

  sm_char_name('<', "Left");
  sm_char_name('>', "Right");

  sm_select_base_kind(TokenBaseKind_StatementClose);
  sm_op(",");
  // ^ TODO: Maybe not this, for Virt. WS reasons

  // Odin Keywords
  Keyword_Set *main_keys = sm_begin_key_set("main_keys");

  /// TODO: Add a separate Keyword_Set and Token SubKind for this...
  sm_select_base_kind(TokenBaseKind_Preprocessor);
  sm_key("Odin_OS", "ODIN_OS");
  sm_key("Odin_Arch", "ODIN_ARCH");
  sm_key("Odin_Endian", "ODIN_ENDIAN");
  sm_key("Odin_Build_Mode", "ODIN_BUILD_MODE");
  sm_key("Odin_Error_Pos_Style", "ODIN_ERROR_POS_STYLE");
  sm_key("Odin_Platform_Subtarget", "ODIN_PLATFORM_SUBTARGET");
  sm_key("Odin_Windows_Subsystem", "ODIN_WINDOWS_SUBSYSTEM");
  sm_key("Odin_Vendor", "ODIN_VENDOR");
  sm_key("Odin_Version", "ODIN_VERSION");
  sm_key("Odin_Root", "ODIN_ROOT");
  sm_key("Odin_Debug", "ODIN_DEBUG");
  sm_key("Odin_Disable_Assert", "ODIN_DISABLE_ASSERT");
  sm_key("Odin_Default_To_Nil_Allocator", "ODIN_DEFAULT_TO_NIL_ALLOCATOR");
  sm_key("Odin_Default_To_Panic_Allocator", "ODIN_DEFAULT_TO_PANIC_ALLOCATOR");
  sm_key("Odin_No_CRT", "ODIN_NO_CRT");
  sm_key("Odin_No_Entry_Point", "ODIN_NO_ENTRY_POINT");
  sm_key("Odin_No_RTTI", "ODIN_NO_RTTI");
  sm_key("Odin_Compile_Timestamp", "ODIN_COMPILE_TIMESTAMP");

  sm_select_base_kind(TokenBaseKind_Operator);
  sm_key("In");
  sm_key("NotIn", "not_in");
  sm_key("Ignore", "_");

  sm_select_base_kind(TokenBaseKind_Keyword);
  sm_key("Asm");
  sm_key("AutoCast", "auto_cast");
  sm_key("Cast");
  sm_key("Context");
  sm_key("Distinct");
  sm_key("Dynamic");
  sm_key("Foreign");
  sm_key("Import");
  sm_key("Maybe", "Maybe");
  sm_key("Package");
  sm_key("Proc");
  sm_key("Transmute");
  sm_key("Using");

  // Builtin
  sm_key("Len");
  sm_key("Cap");
  sm_key("SizeOf", "size_of");
  sm_key("AlignOf", "align_of");
  sm_key("OffsetOf", "offset_of");
  sm_key("OffsetOfSelector", "offset_of_selector");
  sm_key("OffsetOfMember", "offset_of_member");
  sm_key("OffsetOfByString", "offset_of_by_string");

  sm_key("RawData", "raw_data");
  sm_key("TypeOf", "type_of");
  sm_key("TypeInfoOf", "type_info_of");
  sm_key("TypeidOf", "typeid_of");

  sm_key("Complex");
  sm_key("Quaternion");
  sm_key("Real");
  sm_key("Imag");
  sm_key("Jmag");
  sm_key("Kmag");
  sm_key("Conj");
  sm_key("ExpandValues", "expand_values");

  sm_key("Min");
  sm_key("Max");
  sm_key("Abs");
  sm_key("Clamp");

  sm_key("Swizzle");
  sm_key("SoaZip", "soa_zip");
  sm_key("SoaUnzip", "soa_unzip");
  sm_key("Unreachable");

  sm_select_base_kind(qol_TokenKind_Struct);
  sm_key("BitSet", "bit_set");
  sm_key("BitField", "bit_field");
  sm_key("Enum");
  sm_key("Struct");
  sm_key("Union");

  sm_select_base_kind(qol_TokenKind_Primitive);
  sm_key("Map");
  sm_key("Matrix");

  sm_key("Byte");
  sm_key("Rune");
  sm_key("UIntPtr");
  sm_key("RawPtr");
  sm_key("Any");
  sm_key("CString");
  sm_key("String");
  sm_key("TypeID");

  sm_key("Bool");
  sm_key("B8");
  sm_key("B16");
  sm_key("B32");
  sm_key("B64");

  sm_key("Int");
  sm_key("I8");
  sm_key("I16");
  sm_key("I32");
  sm_key("I64");
  sm_key("I128");
  sm_key("I8BE");
  sm_key("I16BE");
  sm_key("I32BE");
  sm_key("I64BE");
  sm_key("I128BE");
  sm_key("I8LE");
  sm_key("I16LE");
  sm_key("I32LE");
  sm_key("I64LE");
  sm_key("I128LE");

  sm_key("UInt");
  sm_key("U8");
  sm_key("U16");
  sm_key("U32");
  sm_key("U64");
  sm_key("U128");
  sm_key("U8LE");
  sm_key("U16LE");
  sm_key("U32LE");
  sm_key("U64LE");
  sm_key("U128LE");
  sm_key("U8BE");
  sm_key("U16BE");
  sm_key("U32BE");
  sm_key("U64BE");
  sm_key("U128BE");

  sm_key("F16");
  sm_key("F32");
  sm_key("F64");
  sm_key("F16BE");
  sm_key("F32BE");
  sm_key("F64BE");
  sm_key("F16LE");
  sm_key("F32LE");
  sm_key("F64LE");

  sm_key("Complex32");
  sm_key("Complex64");
  sm_key("Complex128");
  sm_key("Quaternion64");
  sm_key("Quaternion128");
  sm_key("Quaternion256");

  sm_select_base_kind(qol_TokenKind_Control);
  sm_key("Break");
  sm_key("Case");
  sm_key("Continue");
  sm_key("Defer");
  sm_key("Do");
  sm_key("Else");
  sm_key("Fallthrough");
  sm_key("For");
  sm_key("If");
  sm_key("OrElse", "or_else");
  sm_key("OrReturn", "or_return");
  sm_key("OrBreak", "or_break");
  sm_key("OrContinue", "or_continue");
  sm_key("Return");
  sm_key("Switch");
  sm_key("When");
  sm_key("Where");

  sm_select_base_kind(TokenBaseKind_LiteralInteger);
  sm_key("LiteralTrue", "true");
  sm_key("LiteralFalse", "false");
  sm_key("LiteralNull", "nil");

  sm_select_base_kind(TokenBaseKind_Identifier);
  sm_key_fallback("Identifier");

  // State Machine
  State *root = sm_begin_state_machine();

  Flag *is_char = sm_add_flag(FlagResetRule_AutoZero);
  Flag *is_raw  = sm_add_flag(FlagResetRule_AutoZero);

  sm_custom_decl(str8_lit("i64 counter;"));
  sm_custom_init(str8_lit("state_ptr->counter = 0;"));

#define AddState(N) State *N = sm_add_state(#N)

  AddState(identifier);
  AddState(parametric);
  AddState(directive);

  AddState(whitespace);
  AddState(backslash);

  AddState(operator_or_fnumber_dot);
  AddState(operator_or_comment_slash);

  AddState(number);
  AddState(znumber);

  /// Odin requires more resolves on operators
  // 0..=10  ->  Int(0), Operator(..=), Int(10)
  // Currently -> Float(0.), Operator(.), Operator(=), Int(10)
  AddState(fnumber_decimal_or_range);
  AddState(fnumber_decimal);
  AddState(fnumber_exponent);
  AddState(fnumber_exponent_sign);
  AddState(fnumber_exponent_digits);

  AddState(number_bin_first);
  AddState(number_oct_first);
  AddState(number_dec_first);
  AddState(number_doz_first);
  AddState(number_hex_first);
  AddState(number_bin);
  AddState(number_oct);
  AddState(number_doz);
  AddState(number_hex);

  AddState(character);
  AddState(raw_string);
  AddState(string);
  AddState(string_esc);
  AddState(string_esc_hex);
  AddState(string_esc_oct2);
  AddState(string_esc_oct1);
  AddState(string_esc_universal_8);
  AddState(string_esc_universal_7);
  AddState(string_esc_universal_6);
  AddState(string_esc_universal_5);
  AddState(string_esc_universal_4);
  AddState(string_esc_universal_3);
  AddState(string_esc_universal_2);
  AddState(string_esc_universal_1);

  // NOTE: Whenever you see `_custom` that is inserting raw cpp code into the generated lexer
  // TODO: named labels so this need not be invalidated by sm edits
  printf(" -- MUST ENSURE `goto state_label_37: // comment_block` -- \n");

  AddState(comment_block);
  AddState(comment_block_try_open);
  AddState(comment_block_try_close);
  AddState(comment_line);
  AddState(comment_line_backslashing);

  Operator_Set *main_ops_without_dot_or_slash = smo_copy_op_set(main_ops);
  smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, ".");
  smo_remove_ops_with_prefix(main_ops_without_dot_or_slash, "/");

  Operator_Set *main_ops_with_dot = smo_copy_op_set(main_ops);
  smo_remove_ops_without_prefix(main_ops_with_dot, ".");
  smo_ops_string_skip(main_ops_with_dot, 1);

  ////

  sm_select_state(root);

  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("EOF");
    sm_case_eof(emit);
  }

  sm_case("$", parametric);
  sm_case("#", directive);
  sm_case("abcdefghijklmnopqrstuvwxyz"
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "_",
          identifier);
  sm_case(utf8, identifier);

  sm_case(" \r\n\t\f\v", whitespace);
  sm_case("\\", backslash);
  sm_case(".", operator_or_fnumber_dot);
  sm_case("/", operator_or_comment_slash);
  {
    Character_Set *char_set = smo_new_char_set();
    smo_char_set_union_ops_firsts(char_set, main_ops_without_dot_or_slash);
    smo_char_set_remove(char_set, "./");
    char *char_set_array = smo_char_set_get_array(char_set);
    State *operator_state = smo_op_set_lexer_root(main_ops_without_dot_or_slash, root, "LexError");
    sm_case_peek(char_set_array, operator_state);
  }

  sm_case("123456789", number);
  sm_case("0", znumber);

  sm_case("'", character);
  sm_case("\"", string);
  sm_case("`", raw_string);

  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_fallback(emit);
  }

  ////

  sm_select_state(identifier);
  sm_case("abcdefghijklmnopqrstuvwxyz"
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "_"
          "0123456789",
          identifier);
  sm_case(utf8, identifier);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_keys(main_keys);
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(parametric);
  sm_case("abcdefghijklmnopqrstuvwxyz"
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "_"
          "0123456789",
          parametric);
  sm_case(utf8, parametric);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("Parametric");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(directive);
  sm_case("abcdefghijklmnopqrstuvwxyz"
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "_+"
          "0123456789",
          directive);
  sm_case(utf8, directive);
  sm_case("!", comment_line);  // `#!` is treated as a comment 'cuz bash
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("Directive");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(whitespace);
  sm_case(" \t\n\r\f\v", whitespace);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("Whitespace");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(backslash);
  sm_case("\r", backslash);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("Backslash");
    sm_case("\n", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("Backslash");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(operator_or_comment_slash);
  sm_case("*", comment_block); sm_on_transition_custom(str8_lit("state.counter += 1;"));
  sm_case("/", comment_line);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("DivEq");
    sm_case("=", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("Div");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(operator_or_fnumber_dot);
  sm_case("0123456789", fnumber_decimal);
  {
    Character_Set *char_set = smo_new_char_set();
    smo_char_set_union_ops_firsts(char_set, main_ops_with_dot);
    char *char_set_array = smo_char_set_get_array(char_set);
    State *operator_state = smo_op_set_lexer_root(main_ops_with_dot, root, "LexError");
    sm_case_peek(char_set_array, operator_state);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("Dot");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number);
  sm_case("0123456789_", number);
  sm_case(".", fnumber_decimal_or_range);
  sm_case("Ee", fnumber_exponent);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralIntegerDec");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(znumber);
  sm_case(".",  fnumber_decimal_or_range);
  sm_case("Ee", fnumber_exponent);
  sm_case("b",  number_bin_first);
  sm_case("o",  number_oct_first);
  sm_case("d",  number_dec_first);
  sm_case("xh", number_hex_first);  // hex-floats can get a lil wacky and wild
  sm_case("z",  number_doz_first);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralIntegerDec");
    sm_fallback_peek(emit);
  }

  ////

  // At `0.` and will distinguish `0.15` from `0..<`
  // TODO: `10..<` needs to {Emit(Int, "10"), Transition(op_state)}
  sm_select_state(fnumber_decimal_or_range);
  sm_case("0123456789", fnumber_decimal);
  {
    Character_Set *char_set = smo_new_char_set();
    smo_char_set_union_ops_firsts(char_set, main_ops_with_dot);
    char *char_set_array = smo_char_set_get_array(char_set);
    State *operator_state = smo_op_set_lexer_root(main_ops_with_dot, root, "LexError");
    sm_case_peek(char_set_array, operator_state);
    sm_on_transition_custom(str8_lit(R"EMIT(
                                       //#error "custom emit integer"
                                       {
                                         Token token = {};
                                         token.pos = (i64)(state.emit_ptr - state.base);
                                         token.size = (i64)(state.ptr-1 - state.emit_ptr);
                                         token.sub_kind = TokenOdinKind_LiteralIntegerDec;
                                         token.kind = TokenBaseKind_LiteralInteger;
                                         token_list_push(arena, list, &token);
                                         state.emit_ptr = state.ptr-1;
                                         if (++emit_counter == max){ goto end; }
                                       }
                                       )EMIT"));
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralFloat");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(fnumber_decimal);
  sm_case("0123456789_", fnumber_decimal);
  sm_case("Ee", fnumber_exponent);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralFloat");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(fnumber_exponent);
  sm_case("+-", fnumber_exponent_sign);
  sm_case("0123456789", fnumber_exponent_digits);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralFloat");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(fnumber_exponent_sign);
  sm_case("0123456789", fnumber_exponent_digits);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralFloat");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(fnumber_exponent_digits);
  sm_case("0123456789", fnumber_exponent_digits);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralFloat");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_bin_first);
  sm_case("01", number_bin_first);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_oct_first);
  sm_case("01234567", number_oct);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_dec_first);
  sm_case("0123456789", number);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_doz_first);
  sm_case("0123456789abAB", number_doz);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_hex_first);
  sm_case("0123456789abcdefABCDEF", number_hex);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_bin);
  sm_case("01_", number_bin);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralIntegerBin");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_oct);
  sm_case("01234567_", number_oct);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralIntegerOct");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_doz);
  sm_case("0123456789abAB_", number_doz);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralIntegerDoz");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(number_hex);
  sm_case("0123456789abcdefABCDEF_", number_hex);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralQuaternion");
    sm_case("ijk", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralIntegerHex");
    sm_fallback_peek(emit);
  }

  ////

  sm_select_state(character);
  sm_set_flag(is_char, true);
  sm_fallback_peek(string);

  ////

  sm_select_state(raw_string);
  sm_set_flag(is_raw, true);
  sm_fallback_peek(string);

  ////

  sm_select_state(string);
  sm_case("\\", string_esc);
  sm_case_flagged(is_raw,  true, "\"\n", string);
  sm_case_flagged(is_char, true, "\"", string);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralString");
    sm_case("\"", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralCharacter");
    sm_case_flagged(is_char, true, "\'", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LiteralStringRaw");
    sm_case_flagged(is_raw, true, "`", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_case_peek_flagged(is_raw, false, "\n", emit);
    //sm_case_peek("\n", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_case_eof_peek(emit);
  }
  //sm_case_flagged(is_char, true, "\"", string);
  //sm_case_flagged(is_char, false, "\'", string);
  sm_fallback(string);

  ////

  sm_select_state(string_esc);
  sm_case("\n'\"?\\abfnrtv", string);
  sm_case("01234567", string_esc_oct2);
  sm_case("x", string_esc_hex);
  sm_case("u", string_esc_universal_4);
  sm_case("U", string_esc_universal_8);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_case_peek("\n", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LexError");
    sm_case_eof_peek(emit);
  }
  sm_fallback(string);

  ////

  sm_select_state(string_esc_oct2);
  sm_case("01234567", string_esc_oct1);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_oct1);
  sm_case("01234567", string);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_hex);
  sm_case("0123456789abcdefABCDEF", string_esc_hex);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_8);
  sm_case("0123456789abcdefABCDEF", string_esc_universal_7);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_7);
  sm_case("0123456789abcdefABCDEF", string_esc_universal_6);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_6);
  sm_case("0123456789abcdefABCDEF", string_esc_universal_5);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_5);
  sm_case("0123456789abcdefABCDEF", string_esc_universal_4);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_4);
  sm_case("0123456789abcdefABCDEF", string_esc_universal_3);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_3);
  sm_case("0123456789abcdefABCDEF", string_esc_universal_2);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_2);
  sm_case("0123456789abcdefABCDEF", string_esc_universal_1);
  sm_fallback_peek(string);

  ////

  sm_select_state(string_esc_universal_1);
  sm_case("0123456789abcdefABCDEF", string);
  sm_fallback_peek(string);

  ////

  sm_select_state(comment_block_try_open);
  sm_case("*", comment_block); sm_on_transition_custom(str8_lit("state.counter += 1;"));
  sm_fallback(comment_block);

  ////

  sm_select_state(comment_block);
  sm_case("/", comment_block_try_open);
  sm_case("*", comment_block_try_close);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("MultiComment");
    sm_case_eof_peek(emit);
  }
  sm_fallback(comment_block);

  ////

  sm_select_state(comment_block_try_close);
  sm_custom(str8_lit(R"EMIT(
                                                                                                                                                                                                                                                                                                                                                                                                                       if (state.ptr != state.opl_ptr && *state.ptr == '/' && --state.counter != 0){
                                                                                                                                                                                                                                                                                                                                                                                                                       goto state_label_37; // comment_block
                                                                                                                                                                                                                                                                                                                                                                                                                       }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                )EMIT"));
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("MultiComment");
    sm_case("/", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("MultiComment");
    sm_case_eof_peek(emit);
  }
  sm_case("*", comment_block_try_close);
  sm_fallback(comment_block);

  ////

  sm_select_state(comment_line);
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LineComment");
    sm_case_peek("\n", emit);
  }
  {
    Emit_Rule *emit = sm_emit_rule();
    sm_emit_handler_direct("LineComment");
    sm_case_eof_peek(emit);
  }
  sm_case("\\", comment_line_backslashing);
  sm_fallback(comment_line);

  sm_select_state(comment_line_backslashing);
  sm_case("\r", comment_line_backslashing);
  sm_fallback(comment_line);
}