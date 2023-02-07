#if !defined(FCODER_LEX_GEN_HAND_WRITTEN)
#define FCODER_LEX_GEN_HAND_WRITTEN

internal u64
lexeme_hash(u64 seed, u8 *ptr, u64 size){
  u64 result = 0;
  for (u64 i = 0; i < size; i += 1, ptr += 1){
    result ^= ((*ptr) ^ result*59) + seed;
  }
  return(result);
}

internal Lexeme_Table_Lookup
lexeme_table_lookup(u64 *hash_array, String_Const_u8 *key_array,
                    Lexeme_Table_Value *value_array, i32 slot_count, u64 seed,
                    u8 *ptr, u64 size){
  Lexeme_Table_Lookup result = {};
  u64 hash = lexeme_hash(seed, ptr, size);
  u64 comparison_hash = hash | 1;
  i32 first_index = (hash % slot_count);
  i32 index = first_index;
  for (;;){
    if (hash_array[index] == comparison_hash){
      if (string_match(SCu8(ptr, size), key_array[index])){
        result.found_match = true;
        result.base_kind = value_array[index].base_kind;
        result.sub_kind = value_array[index].sub_kind;
        break;
      }
    }
    else if (hash_array[index] == 0){
      break;
    }
    index += 1;
    if (index == slot_count){
      index = 0;
    }
    if (index == first_index){
      break;
    }
  }
  return(result);
}

#endif
u64 cpp_main_keys_hash_array[131] = {
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0xda536ed778061f95,0x23591dfab22eb255,0xfee87b6d7e90ef9f,0x0000000000000000,
  0x6dfc91df590fffd1,0xb23ab86a678f5171,0x5533b286e080aa27,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0xfeefe2b7e56e89d1,0xda5375509107a9d1,
  0x23591dcce90040ff,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x206df7aac060cd1f,0x23591dfab0aa128f,0x0000000000000000,0x6a23423bfc3ba257,
  0x0000000000000000,0xae2a229dea362e25,0xda536ed72c80dc97,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0xda53756c698057e5,0x5533b2860ae30d1f,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0xda5375509c9d5b0d,0xfeefe6a8855ee3f1,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x41a0fa6f2a4660bd,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0xda53756c69b3d4cf,0xda53756cde5b8b2d,
  0x0000000000000000,0x0000000000000000,0x6dfc9ce5cf97f211,0x23591dcce8053973,
  0x5533b2860a1687ab,0x0000000000000000,0x5533b2860a1c46df,0x5533b2860a88df89,
  0xda536ed771b4a633,0x5533b2860a0dea2f,0xb23ab86a67ff4b9d,0x0000000000000000,
  0x5533b2860a1ae7db,0x23591dcceb9f7cd7,0x23591dcd18f76449,0x0000000000000000,
  0xb23ab86a678e880d,0xfeefed913099c73b,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x5533b2860a13a6df,
  0xfeefef04a4ab9b3d,0x0000000000000000,0x23591dfab0b0f72d,0x0000000000000000,
  0x0000000000000000,0xda536ed77064ab91,0x6a2623fe6135d251,0x6dfc14ba3bdaea97,
  0x6dfc124337aa2009,0x0000000000000000,0x6a23a1b18d58efb1,0xda536ed77097012f,
  0x0000000000000000,0xda536ed7ea695f3f,0x23591dfaaeb10d11,0x6a25559503681261,
  0x5533b286e099831f,0xfee87b292af6021d,0x0000000000000000,0x0000000000000000,
  0xfeefef04a4ab94a9,0x5533b286e09761a9,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0xda536ed72d6ca197,
  0x239531f2920f385f,0x0000000000000000,0x23838c022b404e1b,0x41a0fa6f2a466387,
  0x0d03f1aca838a10f,0xa7d90fe5d0983f4f,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x6dfc97ca5cffcc7f,0xc380413c0a5cc90f,
  0x0000000000000000,0x0000000000000000,0xb23ab86a678f4077,0x23591dccebd01989,
  0xda537561563de2d9,0x0000000000000000,0xda5375613aad1fed,0x6a234dcec2b25207,
  0x23591dcce8caaf57,0x0000000000000000,0x5533b2860a1c40ff,0x215242e4a2bdc90f,
  0x5533b2860a1163d1,0xe7e9f03cbb1dc90f,0xb23ab86a678ec73d,
};
u8 cpp_main_keys_key_array_4[] = {0x73,0x69,0x7a,0x65,0x6f,0x66,};
u8 cpp_main_keys_key_array_5[] = {0x73,0x68,0x6f,0x72,0x74,};
u8 cpp_main_keys_key_array_6[] = {0x76,0x69,0x72,0x74,0x75,0x61,0x6c,};
u8 cpp_main_keys_key_array_8[] = {0x74,0x65,0x6d,0x70,0x6c,0x61,0x74,0x65,};
u8 cpp_main_keys_key_array_9[] = {0x66,0x6f,0x72,};
u8 cpp_main_keys_key_array_10[] = {0x76,0x6f,0x69,0x64,};
u8 cpp_main_keys_key_array_18[] = {0x70,0x72,0x69,0x76,0x61,0x74,0x65,};
u8 cpp_main_keys_key_array_19[] = {0x64,0x65,0x6c,0x65,0x74,0x65,};
u8 cpp_main_keys_key_array_20[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 cpp_main_keys_key_array_24[] = {0x70,0x72,0x6f,0x74,0x65,0x63,0x74,0x65,0x64,};
u8 cpp_main_keys_key_array_25[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 cpp_main_keys_key_array_27[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 cpp_main_keys_key_array_29[] = {0x73,0x74,0x61,0x74,0x69,0x63,0x5f,0x61,0x73,0x73,0x65,0x72,0x74,};
u8 cpp_main_keys_key_array_30[] = {0x73,0x69,0x67,0x6e,0x65,0x64,};
u8 cpp_main_keys_key_array_34[] = {0x65,0x78,0x70,0x6f,0x72,0x74,};
u8 cpp_main_keys_key_array_35[] = {0x62,0x6f,0x6f,0x6c,};
u8 cpp_main_keys_key_array_40[] = {0x64,0x6f,0x75,0x62,0x6c,0x65,};
u8 cpp_main_keys_key_array_41[] = {0x64,0x65,0x66,0x61,0x75,0x6c,0x74,};
u8 cpp_main_keys_key_array_46[] = {0x69,0x66,};
u8 cpp_main_keys_key_array_50[] = {0x65,0x78,0x74,0x65,0x72,0x6e,};
u8 cpp_main_keys_key_array_51[] = {0x66,0x72,0x69,0x65,0x6e,0x64,};
u8 cpp_main_keys_key_array_54[] = {0x76,0x6f,0x6c,0x61,0x74,0x69,0x6c,0x65,};
u8 cpp_main_keys_key_array_55[] = {0x63,0x61,0x74,0x63,0x68,};
u8 cpp_main_keys_key_array_56[] = {0x67,0x6f,0x74,0x6f,};
u8 cpp_main_keys_key_array_58[] = {0x65,0x6e,0x75,0x6d,};
u8 cpp_main_keys_key_array_59[] = {0x4e,0x55,0x4c,0x4c,};
u8 cpp_main_keys_key_array_60[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 cpp_main_keys_key_array_61[] = {0x6c,0x6f,0x6e,0x67,};
u8 cpp_main_keys_key_array_62[] = {0x74,0x72,0x79,};
u8 cpp_main_keys_key_array_64[] = {0x61,0x75,0x74,0x6f,};
u8 cpp_main_keys_key_array_65[] = {0x63,0x6f,0x6e,0x73,0x74,};
u8 cpp_main_keys_key_array_66[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 cpp_main_keys_key_array_68[] = {0x6e,0x65,0x77,};
u8 cpp_main_keys_key_array_69[] = {0x6e,0x75,0x6c,0x6c,0x70,0x74,0x72,};
u8 cpp_main_keys_key_array_75[] = {0x63,0x61,0x73,0x65,};
u8 cpp_main_keys_key_array_76[] = {0x61,0x6c,0x69,0x67,0x6e,0x6f,0x66,};
u8 cpp_main_keys_key_array_78[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 cpp_main_keys_key_array_81[] = {0x73,0x74,0x61,0x74,0x69,0x63,};
u8 cpp_main_keys_key_array_82[] = {0x6f,0x70,0x65,0x72,0x61,0x74,0x6f,0x72,};
u8 cpp_main_keys_key_array_83[] = {0x75,0x6e,0x73,0x69,0x67,0x6e,0x65,0x64,};
u8 cpp_main_keys_key_array_84[] = {0x72,0x65,0x67,0x69,0x73,0x74,0x65,0x72,};
u8 cpp_main_keys_key_array_86[] = {0x6e,0x6f,0x65,0x78,0x63,0x65,0x70,0x74,};
u8 cpp_main_keys_key_array_87[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 cpp_main_keys_key_array_89[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 cpp_main_keys_key_array_90[] = {0x77,0x68,0x69,0x6c,0x65,};
u8 cpp_main_keys_key_array_91[] = {0x64,0x65,0x63,0x6c,0x74,0x79,0x70,0x65,};
u8 cpp_main_keys_key_array_92[] = {0x74,0x72,0x75,0x65,};
u8 cpp_main_keys_key_array_93[] = {0x74,0x79,0x70,0x65,0x64,0x65,0x66,};
u8 cpp_main_keys_key_array_96[] = {0x61,0x6c,0x69,0x67,0x6e,0x61,0x73,};
u8 cpp_main_keys_key_array_97[] = {0x74,0x68,0x69,0x73,};
u8 cpp_main_keys_key_array_103[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 cpp_main_keys_key_array_104[] = {0x6e,0x61,0x6d,0x65,0x73,0x70,0x61,0x63,0x65,};
u8 cpp_main_keys_key_array_106[] = {0x63,0x6f,0x6e,0x73,0x74,0x65,0x78,0x70,0x72,};
u8 cpp_main_keys_key_array_107[] = {0x64,0x6f,};
u8 cpp_main_keys_key_array_108[] = {0x72,0x65,0x69,0x6e,0x74,0x65,0x72,0x70,0x72,0x65,0x74,0x5f,0x63,0x61,0x73,0x74,};
u8 cpp_main_keys_key_array_109[] = {0x74,0x68,0x72,0x65,0x61,0x64,0x5f,0x6c,0x6f,0x63,0x61,0x6c,};
u8 cpp_main_keys_key_array_114[] = {0x74,0x79,0x70,0x65,0x6e,0x61,0x6d,0x65,};
u8 cpp_main_keys_key_array_115[] = {0x73,0x74,0x61,0x74,0x69,0x63,0x5f,0x63,0x61,0x73,0x74,};
u8 cpp_main_keys_key_array_118[] = {0x61,0x73,0x6d,};
u8 cpp_main_keys_key_array_119[] = {0x63,0x6c,0x61,0x73,0x73,};
u8 cpp_main_keys_key_array_120[] = {0x70,0x75,0x62,0x6c,0x69,0x63,};
u8 cpp_main_keys_key_array_122[] = {0x69,0x6e,0x6c,0x69,0x6e,0x65,};
u8 cpp_main_keys_key_array_123[] = {0x65,0x78,0x70,0x6c,0x69,0x63,0x69,0x74,};
u8 cpp_main_keys_key_array_124[] = {0x66,0x6c,0x6f,0x61,0x74,};
u8 cpp_main_keys_key_array_126[] = {0x65,0x6c,0x73,0x65,};
u8 cpp_main_keys_key_array_127[] = {0x63,0x6f,0x6e,0x73,0x74,0x5f,0x63,0x61,0x73,0x74,};
u8 cpp_main_keys_key_array_128[] = {0x63,0x68,0x61,0x72,};
u8 cpp_main_keys_key_array_129[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,0x5f,0x63,0x61,0x73,0x74,};
u8 cpp_main_keys_key_array_130[] = {0x69,0x6e,0x74,};
String_Const_u8 cpp_main_keys_key_array[131] = {
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_4, 6},
  {cpp_main_keys_key_array_5, 5},
  {cpp_main_keys_key_array_6, 7},
  {0, 0},
  {cpp_main_keys_key_array_8, 8},
  {cpp_main_keys_key_array_9, 3},
  {cpp_main_keys_key_array_10, 4},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_18, 7},
  {cpp_main_keys_key_array_19, 6},
  {cpp_main_keys_key_array_20, 5},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_24, 9},
  {cpp_main_keys_key_array_25, 5},
  {0, 0},
  {cpp_main_keys_key_array_27, 8},
  {0, 0},
  {cpp_main_keys_key_array_29, 13},
  {cpp_main_keys_key_array_30, 6},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_34, 6},
  {cpp_main_keys_key_array_35, 4},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_40, 6},
  {cpp_main_keys_key_array_41, 7},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_46, 2},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_50, 6},
  {cpp_main_keys_key_array_51, 6},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_54, 8},
  {cpp_main_keys_key_array_55, 5},
  {cpp_main_keys_key_array_56, 4},
  {0, 0},
  {cpp_main_keys_key_array_58, 4},
  {cpp_main_keys_key_array_59, 4},
  {cpp_main_keys_key_array_60, 6},
  {cpp_main_keys_key_array_61, 4},
  {cpp_main_keys_key_array_62, 3},
  {0, 0},
  {cpp_main_keys_key_array_64, 4},
  {cpp_main_keys_key_array_65, 5},
  {cpp_main_keys_key_array_66, 5},
  {0, 0},
  {cpp_main_keys_key_array_68, 3},
  {cpp_main_keys_key_array_69, 7},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_75, 4},
  {cpp_main_keys_key_array_76, 7},
  {0, 0},
  {cpp_main_keys_key_array_78, 5},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_81, 6},
  {cpp_main_keys_key_array_82, 8},
  {cpp_main_keys_key_array_83, 8},
  {cpp_main_keys_key_array_84, 8},
  {0, 0},
  {cpp_main_keys_key_array_86, 8},
  {cpp_main_keys_key_array_87, 6},
  {0, 0},
  {cpp_main_keys_key_array_89, 6},
  {cpp_main_keys_key_array_90, 5},
  {cpp_main_keys_key_array_91, 8},
  {cpp_main_keys_key_array_92, 4},
  {cpp_main_keys_key_array_93, 7},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_96, 7},
  {cpp_main_keys_key_array_97, 4},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_103, 6},
  {cpp_main_keys_key_array_104, 9},
  {0, 0},
  {cpp_main_keys_key_array_106, 9},
  {cpp_main_keys_key_array_107, 2},
  {cpp_main_keys_key_array_108, 16},
  {cpp_main_keys_key_array_109, 12},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_114, 8},
  {cpp_main_keys_key_array_115, 11},
  {0, 0},
  {0, 0},
  {cpp_main_keys_key_array_118, 3},
  {cpp_main_keys_key_array_119, 5},
  {cpp_main_keys_key_array_120, 6},
  {0, 0},
  {cpp_main_keys_key_array_122, 6},
  {cpp_main_keys_key_array_123, 8},
  {cpp_main_keys_key_array_124, 5},
  {0, 0},
  {cpp_main_keys_key_array_126, 4},
  {cpp_main_keys_key_array_127, 10},
  {cpp_main_keys_key_array_128, 4},
  {cpp_main_keys_key_array_129, 12},
  {cpp_main_keys_key_array_130, 3},
};
Lexeme_Table_Value cpp_main_keys_value_array[131] = {
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_SizeOf},
  {4, TokenCppKind_Short},
  {4, TokenCppKind_Virtual},
  {0, 0},
  {4, TokenCppKind_Template},
  {4, TokenCppKind_For},
  {4, TokenCppKind_Void},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Private},
  {4, TokenCppKind_Delete},
  {8, TokenCppKind_LiteralFalse},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Protected},
  {4, TokenCppKind_Using},
  {0, 0},
  {4, TokenCppKind_Continue},
  {0, 0},
  {4, TokenCppKind_StaticAssert},
  {4, TokenCppKind_Signed},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Export},
  {4, TokenCppKind_Bool},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Double},
  {4, TokenCppKind_Default},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_If},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Extern},
  {4, TokenCppKind_Friend},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Volatile},
  {4, TokenCppKind_Catch},
  {4, TokenCppKind_Goto},
  {0, 0},
  {4, TokenCppKind_Enum},
  {8, TokenCppKind_LiteralNull},
  {4, TokenCppKind_Switch},
  {4, TokenCppKind_Long},
  {4, TokenCppKind_Try},
  {0, 0},
  {4, TokenCppKind_Auto},
  {4, TokenCppKind_Const},
  {4, TokenCppKind_Break},
  {0, 0},
  {4, TokenCppKind_New},
  {8, TokenCppKind_NullPtr},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Case},
  {4, TokenCppKind_AlignOf},
  {0, 0},
  {4, TokenCppKind_Union},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Static},
  {4, TokenCppKind_Operator},
  {4, TokenCppKind_Unsigned},
  {4, TokenCppKind_Register},
  {0, 0},
  {4, TokenCppKind_NoExcept},
  {4, TokenCppKind_Struct},
  {0, 0},
  {4, TokenCppKind_Return},
  {4, TokenCppKind_While},
  {4, TokenCppKind_DeclType},
  {8, TokenCppKind_LiteralTrue},
  {4, TokenCppKind_Typedef},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_AlignAs},
  {4, TokenCppKind_This},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_TypeID},
  {4, TokenCppKind_Namespace},
  {0, 0},
  {4, TokenCppKind_ConstExpr},
  {4, TokenCppKind_Do},
  {4, TokenCppKind_ReinterpretCast},
  {4, TokenCppKind_ThreadLocal},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Typename},
  {4, TokenCppKind_StaticCast},
  {0, 0},
  {0, 0},
  {4, TokenCppKind_Asm},
  {4, TokenCppKind_Class},
  {4, TokenCppKind_Public},
  {0, 0},
  {4, TokenCppKind_Inline},
  {4, TokenCppKind_Explicit},
  {4, TokenCppKind_Float},
  {0, 0},
  {4, TokenCppKind_Else},
  {4, TokenCppKind_ConstCast},
  {4, TokenCppKind_Char},
  {4, TokenCppKind_DynamicCast},
  {4, TokenCppKind_Int},
};
i32 cpp_main_keys_slot_count = 131;
u64 cpp_main_keys_seed = 0xd3808a668f905e80;
u64 cpp_pp_directives_hash_array[23] = {
  0x0e715e28c8cca757,0x17219f9a010575c3,0x0e7120648dad63fb,0x0000000000000000,
  0xc7e12d41c1c4f0c3,0x17219f9a074ad2c3,0x0057939312bdc5e9,0x0000000000000000,
  0x4f274e39810861bf,0x0000000000000000,0x4f274e38018d7a43,0x0000000000000000,
  0x17219f94008853c3,0x4f274e3bfe8394cf,0x0000000000000000,0x0057939312ab84ff,
  0x0000000000000000,0x0057939312bdd273,0x17219f940e4e76a9,0x4f274f2141c39c15,
  0x0000000000000000,0x17219f9a05ec2aa3,0x0000000000000000,
};
u8 cpp_pp_directives_key_array_0[] = {0x69,0x6e,0x63,0x6c,0x75,0x64,0x65,};
u8 cpp_pp_directives_key_array_1[] = {0x69,0x66,0x64,0x65,0x66,};
u8 cpp_pp_directives_key_array_2[] = {0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,};
u8 cpp_pp_directives_key_array_4[] = {0x69,0x66,};
u8 cpp_pp_directives_key_array_5[] = {0x65,0x6e,0x64,0x69,0x66,};
u8 cpp_pp_directives_key_array_6[] = {0x65,0x6c,0x73,0x65,};
u8 cpp_pp_directives_key_array_8[] = {0x64,0x65,0x66,0x69,0x6e,0x65,};
u8 cpp_pp_directives_key_array_10[] = {0x69,0x66,0x6e,0x64,0x65,0x66,};
u8 cpp_pp_directives_key_array_12[] = {0x75,0x6e,0x64,0x65,0x66,};
u8 cpp_pp_directives_key_array_13[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 cpp_pp_directives_key_array_15[] = {0x6c,0x69,0x6e,0x65,};
u8 cpp_pp_directives_key_array_17[] = {0x65,0x6c,0x69,0x66,};
u8 cpp_pp_directives_key_array_18[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 cpp_pp_directives_key_array_19[] = {0x70,0x72,0x61,0x67,0x6d,0x61,};
u8 cpp_pp_directives_key_array_21[] = {0x65,0x72,0x72,0x6f,0x72,};
String_Const_u8 cpp_pp_directives_key_array[23] = {
  {cpp_pp_directives_key_array_0, 7},
  {cpp_pp_directives_key_array_1, 5},
  {cpp_pp_directives_key_array_2, 7},
  {0, 0},
  {cpp_pp_directives_key_array_4, 2},
  {cpp_pp_directives_key_array_5, 5},
  {cpp_pp_directives_key_array_6, 4},
  {0, 0},
  {cpp_pp_directives_key_array_8, 6},
  {0, 0},
  {cpp_pp_directives_key_array_10, 6},
  {0, 0},
  {cpp_pp_directives_key_array_12, 5},
  {cpp_pp_directives_key_array_13, 6},
  {0, 0},
  {cpp_pp_directives_key_array_15, 4},
  {0, 0},
  {cpp_pp_directives_key_array_17, 4},
  {cpp_pp_directives_key_array_18, 5},
  {cpp_pp_directives_key_array_19, 6},
  {0, 0},
  {cpp_pp_directives_key_array_21, 5},
  {0, 0},
};
Lexeme_Table_Value cpp_pp_directives_value_array[23] = {
  {5, TokenCppKind_PPInclude},
  {5, TokenCppKind_PPIfDef},
  {5, TokenCppKind_PPVersion},
  {0, 0},
  {5, TokenCppKind_PPIf},
  {5, TokenCppKind_PPEndIf},
  {5, TokenCppKind_PPElse},
  {0, 0},
  {5, TokenCppKind_PPDefine},
  {0, 0},
  {5, TokenCppKind_PPIfNDef},
  {0, 0},
  {5, TokenCppKind_PPUndef},
  {5, TokenCppKind_PPImport},
  {0, 0},
  {5, TokenCppKind_PPLine},
  {0, 0},
  {5, TokenCppKind_PPElIf},
  {5, TokenCppKind_PPUsing},
  {5, TokenCppKind_PPPragma},
  {0, 0},
  {5, TokenCppKind_PPError},
  {0, 0},
};
i32 cpp_pp_directives_slot_count = 23;
u64 cpp_pp_directives_seed = 0x03470923c45c254a;
u64 cpp_pp_keys_hash_array[2] = {
  0x0000000000000000,0x4c47bc027474f20f,
};
u8 cpp_pp_keys_key_array_1[] = {0x64,0x65,0x66,0x69,0x6e,0x65,0x64,};
String_Const_u8 cpp_pp_keys_key_array[2] = {
  {0, 0},
  {cpp_pp_keys_key_array_1, 7},
};
Lexeme_Table_Value cpp_pp_keys_value_array[2] = {
  {0, 0},
  {4, TokenCppKind_PPDefined},
};
i32 cpp_pp_keys_slot_count = 2;
u64 cpp_pp_keys_seed = 0xb2fdb24a5b6dc8cb;
struct Lex_State_Cpp{
  u32 flags_ZF0;
  u32 flags_KF0;
  u16 flags_KB0;
  u8 *base;
  u8 *delim_first;
  u8 *delim_one_past_last;
  u8 *emit_ptr;
  u8 *ptr;
  u8 *opl_ptr;
};
internal void
lex_full_input_cpp_init(Lex_State_Cpp *state_ptr, String_Const_u8 input){
  state_ptr->flags_ZF0 = 0;
  state_ptr->flags_KF0 = 0;
  state_ptr->flags_KB0 = 0;
  state_ptr->base = input.str;
  state_ptr->delim_first = input.str;
  state_ptr->delim_one_past_last = input.str;
  state_ptr->emit_ptr = input.str;
  state_ptr->ptr = input.str;
  state_ptr->opl_ptr = input.str + input.size;
}
internal b32
lex_full_input_cpp_breaks(Arena *arena, Token_List *list, Lex_State_Cpp *state_ptr, u64 max){
  b32 result = false;
  u64 emit_counter = 0;
  Lex_State_Cpp state;
  block_copy_struct(&state, state_ptr);
  {
    state_label_1: // root
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_EOF;
            token.kind = 0;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        result = true;
        goto end;
      }
    }
    switch (*state.ptr){
      case 0x00:case 0x01:case 0x02:case 0x03:case 0x04:case 0x05:case 0x06:
      case 0x07:case 0x08:case 0x0e:case 0x0f:case 0x10:case 0x11:case 0x12:
      case 0x13:case 0x14:case 0x15:case 0x16:case 0x17:case 0x18:case 0x19:
      case 0x1a:case 0x1b:case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x40:
      case 0x60:case 0x7f:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x09:case 0x0b:case 0x0c:case 0x0d:case 0x20:
      {
        if ((HasFlag(state.flags_KF0, 0x2))){
          state.ptr += 1;
          goto state_label_4; // error_body
        }
        state.ptr += 1;
        goto state_label_3; // whitespace
      }break;
      case 0x0a:
      {
        state.ptr += 1;
        state.flags_KB0 &= ~(0x1);
        state.flags_KF0 &= ~(0x1);
        state.flags_KF0 &= ~(0x2);
        goto state_label_3; // whitespace
      }break;
      case 0x21:
      {
        state.ptr += 1;
        goto state_label_61; // op stage
      }break;
      case 0x22:
      {
        if ((HasFlag(state.flags_KF0, 0x1))){
          state.ptr += 1;
          goto state_label_26; // include_quotes
        }
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x23:
      {
        if ((!HasFlag(state.flags_KB0, 0x1))){
          state.ptr += 1;
          goto state_label_23; // pp_directive_whitespace
        }
        state.ptr += 1;
        goto state_label_68; // op stage
      }break;
      default:
      {
        state.ptr += 1;
        goto state_label_2; // identifier
      }break;
      case 0x25:
      {
        state.ptr += 1;
        goto state_label_65; // op stage
      }break;
      case 0x26:
      {
        state.ptr += 1;
        goto state_label_62; // op stage
      }break;
      case 0x27:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x40;
        goto state_label_32; // string
      }break;
      case 0x28:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_ParenOp;
            token.kind = 13;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x29:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_ParenCl;
            token.kind = 14;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2a:
      {
        state.ptr += 1;
        goto state_label_64; // op stage
      }break;
      case 0x2b:
      {
        state.ptr += 1;
        goto state_label_54; // op stage
      }break;
      case 0x2c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Comma;
            token.kind = 15;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2d:
      {
        state.ptr += 1;
        goto state_label_55; // op stage
      }break;
      case 0x2e:
      {
        state.ptr += 1;
        goto state_label_6; // operator_or_fnumber_dot
      }break;
      case 0x2f:
      {
        state.ptr += 1;
        goto state_label_7; // operator_or_comment_slash
      }break;
      case 0x30:
      {
        state.ptr += 1;
        goto state_label_9; // znumber
      }break;
      case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:case 0x37:
      case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_8; // number
      }break;
      case 0x3a:
      {
        state.ptr += 1;
        goto state_label_53; // op stage
      }break;
      case 0x3b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Semicolon;
            token.kind = 15;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3c:
      {
        if ((!HasFlag(state.flags_KF0, 0x1))){
          state.ptr += 1;
          goto state_label_57; // op stage
        }
        state.ptr += 1;
        goto state_label_25; // include_pointy
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        goto state_label_60; // op stage
      }break;
      case 0x3e:
      {
        state.ptr += 1;
        goto state_label_58; // op stage
      }break;
      case 0x3f:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Ternary;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x4;
        goto state_label_27; // pre_L
      }break;
      case 0x52:
      {
        state.ptr += 1;
        goto state_label_31; // pre_R
      }break;
      case 0x55:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x20;
        goto state_label_29; // pre_U
      }break;
      case 0x5b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_BrackOp;
            token.kind = 13;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x5c:
      {
        state.ptr += 1;
        goto state_label_5; // backslash
      }break;
      case 0x5d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_BrackCl;
            token.kind = 14;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x5e:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Xor;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x75:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x10;
        goto state_label_28; // pre_u
      }break;
      case 0x7b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_BraceOp;
            token.kind = 11;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x7c:
      {
        state.ptr += 1;
        goto state_label_63; // op stage
      }break;
      case 0x7d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_BraceCl;
            token.kind = 12;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x7e:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Tilde;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_2: // identifier
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_KB0, 0x1)){
              Lexeme_Table_Lookup lookup = lexeme_table_lookup(cpp_pp_keys_hash_array, cpp_pp_keys_key_array, cpp_pp_keys_value_array, cpp_pp_keys_slot_count, cpp_pp_keys_seed, state.emit_ptr, token.size);
              if (lookup.found_match){
                token.kind = lookup.base_kind;
                token.sub_kind = lookup.sub_kind;
                break;
              }
            }
            Lexeme_Table_Lookup lookup = lexeme_table_lookup(cpp_main_keys_hash_array, cpp_main_keys_key_array, cpp_main_keys_value_array, cpp_main_keys_slot_count, cpp_main_keys_seed, state.emit_ptr, token.size);
            if (lookup.found_match){
              token.kind = lookup.base_kind;
              token.sub_kind = lookup.sub_kind;
              break;
            }
            token.sub_kind = TokenCppKind_Identifier;
            token.kind = 6;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      case 0x00:case 0x01:case 0x02:case 0x03:case 0x04:case 0x05:case 0x06:
      case 0x07:case 0x08:case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:
      case 0x0e:case 0x0f:case 0x10:case 0x11:case 0x12:case 0x13:case 0x14:
      case 0x15:case 0x16:case 0x17:case 0x18:case 0x19:case 0x1a:case 0x1b:
      case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x20:case 0x21:case 0x22:
      case 0x23:case 0x25:case 0x26:case 0x27:case 0x28:case 0x29:case 0x2a:
      case 0x2b:case 0x2c:case 0x2d:case 0x2e:case 0x2f:case 0x3a:case 0x3b:
      case 0x3c:case 0x3d:case 0x3e:case 0x3f:case 0x40:case 0x5b:case 0x5c:
      case 0x5d:case 0x5e:case 0x60:case 0x7b:case 0x7c:case 0x7d:case 0x7e:
      case 0x7f:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_KB0, 0x1)){
              Lexeme_Table_Lookup lookup = lexeme_table_lookup(cpp_pp_keys_hash_array, cpp_pp_keys_key_array, cpp_pp_keys_value_array, cpp_pp_keys_slot_count, cpp_pp_keys_seed, state.emit_ptr, token.size);
              if (lookup.found_match){
                token.kind = lookup.base_kind;
                token.sub_kind = lookup.sub_kind;
                break;
              }
            }
            Lexeme_Table_Lookup lookup = lexeme_table_lookup(cpp_main_keys_hash_array, cpp_main_keys_key_array, cpp_main_keys_value_array, cpp_main_keys_slot_count, cpp_main_keys_seed, state.emit_ptr, token.size);
            if (lookup.found_match){
              token.kind = lookup.base_kind;
              token.sub_kind = lookup.sub_kind;
              break;
            }
            token.sub_kind = TokenCppKind_Identifier;
            token.kind = 6;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      default:
      {
        state.ptr += 1;
        goto state_label_2; // identifier
      }break;
    }
  }
  {
    state_label_3: // whitespace
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Whitespace;
            token.kind = 1;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Whitespace;
            token.kind = 1;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x09:case 0x0b:case 0x0c:case 0x0d:case 0x20:
      {
        state.ptr += 1;
        goto state_label_3; // whitespace
      }break;
      case 0x0a:
      {
        state.ptr += 1;
        state.flags_KB0 &= ~(0x1);
        state.flags_KF0 &= ~(0x1);
        state.flags_KF0 &= ~(0x2);
        goto state_label_3; // whitespace
      }break;
    }
  }
  {
    state_label_4: // error_body
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PPErrorMessage;
            token.kind = 10;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_4; // error_body
      }break;
      case 0x0a:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PPErrorMessage;
            token.kind = 10;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_5: // backslash
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Backslash;
            token.kind = 1;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Backslash;
            token.kind = 1;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x0a:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Backslash;
            token.kind = 1;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x0d:
      {
        state.ptr += 1;
        goto state_label_5; // backslash
      }break;
    }
  }
  {
    state_label_6: // operator_or_fnumber_dot
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Dot;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Dot;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2a:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_DotStar;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2e:
      {
        state.ptr += 1;
        goto state_label_69; // op stage
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_10; // fnumber_decimal
      }break;
    }
  }
  {
    state_label_7: // operator_or_comment_slash
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Div;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Div;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2a:
      {
        state.ptr += 1;
        goto state_label_49; // comment_block
      }break;
      case 0x2f:
      {
        state.ptr += 1;
        goto state_label_51; // comment_line
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_DivEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_8: // number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralInteger;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralInteger;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x27:case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:
      case 0x36:case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_8; // number
      }break;
      case 0x2e:
      {
        state.ptr += 1;
        goto state_label_10; // fnumber_decimal
      }break;
      case 0x45:case 0x65:
      {
        state.ptr += 1;
        goto state_label_11; // fnumber_exponent
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        goto state_label_18; // L_number
      }break;
      case 0x55:case 0x75:
      {
        state.ptr += 1;
        goto state_label_17; // U_number
      }break;
      case 0x6c:
      {
        state.ptr += 1;
        goto state_label_20; // l_number
      }break;
    }
  }
  {
    state_label_9: // znumber
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralInteger;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralInteger;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2e:
      {
        state.ptr += 1;
        goto state_label_10; // fnumber_decimal
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x2;
        goto state_label_16; // number_oct
      }break;
      case 0x45:case 0x65:
      {
        state.ptr += 1;
        goto state_label_11; // fnumber_exponent
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        goto state_label_18; // L_number
      }break;
      case 0x55:case 0x75:
      {
        state.ptr += 1;
        goto state_label_17; // U_number
      }break;
      case 0x58:case 0x78:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x1;
        goto state_label_14; // number_hex_first
      }break;
      case 0x6c:
      {
        state.ptr += 1;
        goto state_label_20; // l_number
      }break;
    }
  }
  {
    state_label_10: // fnumber_decimal
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x27:case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:
      case 0x36:case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_10; // fnumber_decimal
      }break;
      case 0x45:case 0x65:
      {
        state.ptr += 1;
        goto state_label_11; // fnumber_exponent
      }break;
      case 0x46:case 0x66:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat32;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:case 0x6c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_11: // fnumber_exponent
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2b:case 0x2d:
      {
        state.ptr += 1;
        goto state_label_12; // fnumber_exponent_sign
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_13; // fnumber_exponent_digits
      }break;
      case 0x46:case 0x66:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat32;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:case 0x6c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_12: // fnumber_exponent_sign
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_13; // fnumber_exponent_digits
      }break;
      case 0x46:case 0x66:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat32;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:case 0x6c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_13: // fnumber_exponent_digits
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_13; // fnumber_exponent_digits
      }break;
      case 0x46:case 0x66:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat32;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:case 0x6c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralFloat64;
            token.kind = 9;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_14: // number_hex_first
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_15; // number_hex
      }break;
    }
  }
  {
    state_label_15: // number_hex
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralIntegerHex;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralIntegerHex;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_15; // number_hex
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        goto state_label_18; // L_number
      }break;
      case 0x55:case 0x75:
      {
        state.ptr += 1;
        goto state_label_17; // U_number
      }break;
      case 0x6c:
      {
        state.ptr += 1;
        goto state_label_20; // l_number
      }break;
    }
  }
  {
    state_label_16: // number_oct
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralIntegerOct;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LiteralIntegerOct;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x2;
        goto state_label_16; // number_oct
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        goto state_label_18; // L_number
      }break;
      case 0x55:case 0x75:
      {
        state.ptr += 1;
        goto state_label_17; // U_number
      }break;
      case 0x6c:
      {
        state.ptr += 1;
        goto state_label_20; // l_number
      }break;
    }
  }
  {
    state_label_17: // U_number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexU;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctU;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerU;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexU;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctU;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerU;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        goto state_label_19; // UL_number
      }break;
      case 0x6c:
      {
        state.ptr += 1;
        goto state_label_21; // Ul_number
      }break;
    }
  }
  {
    state_label_18: // L_number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        goto state_label_22; // LL_number
      }break;
      case 0x55:case 0x75:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexUL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctUL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerUL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_19: // UL_number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexUL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctUL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerUL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexUL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctUL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerUL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x4c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexULL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctULL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerULL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_20: // l_number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x55:case 0x75:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexUL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctUL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerUL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x6c:
      {
        state.ptr += 1;
        goto state_label_22; // LL_number
      }break;
    }
  }
  {
    state_label_21: // Ul_number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexUL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctUL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerUL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexUL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctUL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerUL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x6c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexULL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctULL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerULL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_22: // LL_number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexLL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctLL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerLL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexLL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctLL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerLL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x55:case 0x75:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x1)){
              token.sub_kind = TokenCppKind_LiteralIntegerHexULL;
              token.kind = 8;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x2)){
              token.sub_kind = TokenCppKind_LiteralIntegerOctULL;
              token.kind = 8;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralIntegerULL;
            token.kind = 8;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_23: // pp_directive_whitespace
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x09:case 0x0b:case 0x0c:case 0x20:
      {
        state.ptr += 1;
        goto state_label_23; // pp_directive_whitespace
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:case 0x4b:
      case 0x4c:case 0x4d:case 0x4e:case 0x4f:case 0x50:case 0x51:case 0x52:
      case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:case 0x58:case 0x59:
      case 0x5a:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:case 0x67:case 0x68:case 0x69:case 0x6a:case 0x6b:case 0x6c:
      case 0x6d:case 0x6e:case 0x6f:case 0x70:case 0x71:case 0x72:case 0x73:
      case 0x74:case 0x75:case 0x76:case 0x77:case 0x78:case 0x79:case 0x7a:
      {
        state.delim_first = state.ptr;
        state.flags_KB0 |= 0x1;
        state.ptr += 1;
        goto state_label_24; // pp_directive
      }break;
    }
  }
  {
    state_label_24: // pp_directive
    if (state.ptr == state.opl_ptr){
      if ((true)){
        state.delim_one_past_last = state.ptr;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            Lexeme_Table_Lookup lookup = lexeme_table_lookup(cpp_pp_directives_hash_array, cpp_pp_directives_key_array, cpp_pp_directives_value_array, cpp_pp_directives_slot_count, cpp_pp_directives_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
            if (lookup.found_match){
              token.kind = lookup.base_kind;
              token.sub_kind = lookup.sub_kind;
              break;
            }
            token.sub_kind = TokenCppKind_PPUnknown;
            token.kind = 2;
          }while(0);
          switch (token.sub_kind){
            case TokenCppKind_PPInclude:
            {
              state.flags_KF0 |= 0x1;
            }break;
            case TokenCppKind_PPError:
            {
              state.flags_KF0 |= 0x2;
            }break;
          }
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        state.delim_one_past_last = state.ptr;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            Lexeme_Table_Lookup lookup = lexeme_table_lookup(cpp_pp_directives_hash_array, cpp_pp_directives_key_array, cpp_pp_directives_value_array, cpp_pp_directives_slot_count, cpp_pp_directives_seed, state.delim_first, (state.delim_one_past_last - state.delim_first));
            if (lookup.found_match){
              token.kind = lookup.base_kind;
              token.sub_kind = lookup.sub_kind;
              break;
            }
            token.sub_kind = TokenCppKind_PPUnknown;
            token.kind = 2;
          }while(0);
          switch (token.sub_kind){
            case TokenCppKind_PPInclude:
            {
              state.flags_KF0 |= 0x1;
            }break;
            case TokenCppKind_PPError:
            {
              state.flags_KF0 |= 0x2;
            }break;
          }
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:case 0x4b:
      case 0x4c:case 0x4d:case 0x4e:case 0x4f:case 0x50:case 0x51:case 0x52:
      case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:case 0x58:case 0x59:
      case 0x5a:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:case 0x67:case 0x68:case 0x69:case 0x6a:case 0x6b:case 0x6c:
      case 0x6d:case 0x6e:case 0x6f:case 0x70:case 0x71:case 0x72:case 0x73:
      case 0x74:case 0x75:case 0x76:case 0x77:case 0x78:case 0x79:case 0x7a:
      {
        state.ptr += 1;
        goto state_label_24; // pp_directive
      }break;
    }
  }
  {
    state_label_25: // include_pointy
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x20:case 0x21:case 0x22:case 0x23:case 0x24:case 0x25:case 0x26:
      case 0x27:case 0x28:case 0x29:case 0x2a:case 0x2b:case 0x2c:case 0x2d:
      case 0x2e:case 0x2f:case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:
      case 0x35:case 0x36:case 0x37:case 0x38:case 0x39:case 0x3a:case 0x3b:
      case 0x3d:case 0x3f:case 0x40:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:case 0x4b:
      case 0x4c:case 0x4d:case 0x4e:case 0x4f:case 0x50:case 0x51:case 0x52:
      case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:case 0x58:case 0x59:
      case 0x5a:case 0x5b:case 0x5c:case 0x5d:case 0x5e:case 0x5f:case 0x61:
      case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:case 0x68:
      case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:case 0x6f:
      case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:case 0x76:
      case 0x77:case 0x78:case 0x79:case 0x7a:case 0x7b:case 0x7c:case 0x7d:
      {
        state.ptr += 1;
        goto state_label_25; // include_pointy
      }break;
      case 0x3e:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PPIncludeFile;
            token.kind = 10;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_26: // include_quotes
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x20:case 0x21:case 0x23:case 0x24:case 0x25:case 0x26:case 0x27:
      case 0x28:case 0x29:case 0x2a:case 0x2b:case 0x2c:case 0x2d:case 0x2e:
      case 0x2f:case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:
      case 0x36:case 0x37:case 0x38:case 0x39:case 0x3a:case 0x3b:case 0x3c:
      case 0x3d:case 0x3e:case 0x3f:case 0x40:case 0x41:case 0x42:case 0x43:
      case 0x44:case 0x45:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:
      case 0x4b:case 0x4c:case 0x4d:case 0x4e:case 0x4f:case 0x50:case 0x51:
      case 0x52:case 0x53:case 0x54:case 0x55:case 0x56:case 0x57:case 0x58:
      case 0x59:case 0x5a:case 0x5b:case 0x5c:case 0x5d:case 0x5e:case 0x5f:
      case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:case 0x66:case 0x67:
      case 0x68:case 0x69:case 0x6a:case 0x6b:case 0x6c:case 0x6d:case 0x6e:
      case 0x6f:case 0x70:case 0x71:case 0x72:case 0x73:case 0x74:case 0x75:
      case 0x76:case 0x77:case 0x78:case 0x79:case 0x7a:case 0x7b:case 0x7c:
      case 0x7d:
      {
        state.ptr += 1;
        goto state_label_26; // include_quotes
      }break;
      case 0x22:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PPIncludeFile;
            token.kind = 10;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_27: // pre_L
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_2; // identifier
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_2; // identifier
      }break;
      case 0x22:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x52:
      {
        state.ptr += 1;
        goto state_label_31; // pre_R
      }break;
    }
  }
  {
    state_label_28: // pre_u
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_2; // identifier
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_2; // identifier
      }break;
      case 0x22:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x38:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x8;
        goto state_label_30; // pre_u8
      }break;
      case 0x52:
      {
        state.ptr += 1;
        goto state_label_31; // pre_R
      }break;
    }
  }
  {
    state_label_29: // pre_U
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_2; // identifier
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_2; // identifier
      }break;
      case 0x22:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x52:
      {
        state.ptr += 1;
        goto state_label_31; // pre_R
      }break;
    }
  }
  {
    state_label_30: // pre_u8
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_2; // identifier
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_2; // identifier
      }break;
      case 0x22:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x52:
      {
        state.ptr += 1;
        goto state_label_31; // pre_R
      }break;
    }
  }
  {
    state_label_31: // pre_R
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_2; // identifier
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_2; // identifier
      }break;
      case 0x22:
      {
        state.ptr += 1;
        state.delim_first = state.ptr;
        goto state_label_45; // raw_string_get_delim
      }break;
    }
  }
  {
    state_label_32: // string
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x0a:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x22:
      {
        if ((!HasFlag(state.flags_ZF0, 0x40))){
          state.ptr += 1;
          {
            Token token = {};
            token.pos = (i64)(state.emit_ptr - state.base);
            token.size = (i64)(state.ptr - state.emit_ptr);
            token.flags = state.flags_KB0;
            do{
              if (HasFlag(state.flags_ZF0, 0x4)){
                token.sub_kind = TokenCppKind_LiteralStringWide;
                token.kind = 10;
                break;
              }
              if (HasFlag(state.flags_ZF0, 0x8)){
                token.sub_kind = TokenCppKind_LiteralStringUTF8;
                token.kind = 10;
                break;
              }
              if (HasFlag(state.flags_ZF0, 0x10)){
                token.sub_kind = TokenCppKind_LiteralStringUTF16;
                token.kind = 10;
                break;
              }
              if (HasFlag(state.flags_ZF0, 0x20)){
                token.sub_kind = TokenCppKind_LiteralStringUTF32;
                token.kind = 10;
                break;
              }
              token.sub_kind = TokenCppKind_LiteralString;
              token.kind = 10;
            }while(0);
            token_list_push(arena, list, &token);
            emit_counter += 1;
            state.emit_ptr = state.ptr;
            if (emit_counter == max){
              goto end;
            }
          }
          state.flags_ZF0 = 0;
          goto state_label_1; // root
        }
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x27:
      {
        if ((HasFlag(state.flags_ZF0, 0x40))){
          state.ptr += 1;
          {
            Token token = {};
            token.pos = (i64)(state.emit_ptr - state.base);
            token.size = (i64)(state.ptr - state.emit_ptr);
            token.flags = state.flags_KB0;
            do{
              if (HasFlag(state.flags_ZF0, 0x4)){
                token.sub_kind = TokenCppKind_LiteralCharacterWide;
                token.kind = 10;
                break;
              }
              if (HasFlag(state.flags_ZF0, 0x8)){
                token.sub_kind = TokenCppKind_LiteralCharacterUTF8;
                token.kind = 10;
                break;
              }
              if (HasFlag(state.flags_ZF0, 0x10)){
                token.sub_kind = TokenCppKind_LiteralCharacterUTF16;
                token.kind = 10;
                break;
              }
              if (HasFlag(state.flags_ZF0, 0x20)){
                token.sub_kind = TokenCppKind_LiteralCharacterUTF32;
                token.kind = 10;
                break;
              }
              token.sub_kind = TokenCppKind_LiteralCharacter;
              token.kind = 10;
            }while(0);
            token_list_push(arena, list, &token);
            emit_counter += 1;
            state.emit_ptr = state.ptr;
            if (emit_counter == max){
              goto end;
            }
          }
          state.flags_ZF0 = 0;
          goto state_label_1; // root
        }
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x5c:
      {
        state.ptr += 1;
        goto state_label_33; // string_esc
      }break;
    }
  }
  {
    state_label_33: // string_esc
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_EOF;
            token.kind = 0;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        result = true;
        goto end;
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        goto state_label_34; // string_esc_oct2
      }break;
      case 0x55:
      {
        state.ptr += 1;
        goto state_label_37; // string_esc_universal_8
      }break;
      case 0x75:
      {
        state.ptr += 1;
        goto state_label_41; // string_esc_universal_4
      }break;
      case 0x78:
      {
        state.ptr += 1;
        goto state_label_36; // string_esc_hex
      }break;
    }
  }
  {
    state_label_34: // string_esc_oct2
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        goto state_label_35; // string_esc_oct1
      }break;
    }
  }
  {
    state_label_35: // string_esc_oct1
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
    }
  }
  {
    state_label_36: // string_esc_hex
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_36; // string_esc_hex
      }break;
    }
  }
  {
    state_label_37: // string_esc_universal_8
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_38; // string_esc_universal_7
      }break;
    }
  }
  {
    state_label_38: // string_esc_universal_7
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_39; // string_esc_universal_6
      }break;
    }
  }
  {
    state_label_39: // string_esc_universal_6
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_40; // string_esc_universal_5
      }break;
    }
  }
  {
    state_label_40: // string_esc_universal_5
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_41; // string_esc_universal_4
      }break;
    }
  }
  {
    state_label_41: // string_esc_universal_4
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_42; // string_esc_universal_3
      }break;
    }
  }
  {
    state_label_42: // string_esc_universal_3
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_43; // string_esc_universal_2
      }break;
    }
  }
  {
    state_label_43: // string_esc_universal_2
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_44; // string_esc_universal_1
      }break;
    }
  }
  {
    state_label_44: // string_esc_universal_1
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_32; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_32; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_32; // string
      }break;
    }
  }
  {
    state_label_45: // raw_string_get_delim
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_EOF;
            token.kind = 0;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        result = true;
        goto end;
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_45; // raw_string_get_delim
      }break;
      case 0x20:case 0x29:case 0x5c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x28:
      {
        state.delim_one_past_last = state.ptr;
        state.ptr += 1;
        goto state_label_46; // raw_string_find_close
      }break;
    }
  }
  {
    state_label_46: // raw_string_find_close
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_EOF;
            token.kind = 0;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        result = true;
        goto end;
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_46; // raw_string_find_close
      }break;
      case 0x29:
      {
        state.ptr += 1;
        goto state_label_47; // raw_string_try_delim
      }break;
    }
  }
  {
    state_label_47: // raw_string_try_delim
    u64 delim_length = state.delim_one_past_last - state.delim_first;
    u64 parse_length = 0;
    for (;;){
      if (parse_length == delim_length){
        goto state_label_48; // raw_string_try_quote
      }
      if (state.ptr == state.opl_ptr){
        goto state_label_48; // raw_string_try_quote
      }
      if (*state.ptr == state.delim_first[parse_length]){
        state.ptr += 1;
        parse_length += 1;
      }
      else{
        goto state_label_46; // raw_string_find_close
      }
    }
  }
  {
    state_label_48: // raw_string_try_quote
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_46; // raw_string_find_close
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_46; // raw_string_find_close
      }break;
      case 0x22:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            if (HasFlag(state.flags_ZF0, 0x4)){
              token.sub_kind = TokenCppKind_LiteralStringWideRaw;
              token.kind = 10;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x8)){
              token.sub_kind = TokenCppKind_LiteralStringUTF8Raw;
              token.kind = 10;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x10)){
              token.sub_kind = TokenCppKind_LiteralStringUTF16Raw;
              token.kind = 10;
              break;
            }
            if (HasFlag(state.flags_ZF0, 0x20)){
              token.sub_kind = TokenCppKind_LiteralStringUTF32Raw;
              token.kind = 10;
              break;
            }
            token.sub_kind = TokenCppKind_LiteralStringRaw;
            token.kind = 10;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_49: // comment_block
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_BlockComment;
            token.kind = 3;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_EOF;
            token.kind = 0;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        result = true;
        goto end;
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_49; // comment_block
      }break;
      case 0x0a:
      {
        state.ptr += 1;
        state.flags_KB0 &= ~(0x1);
        state.flags_KF0 &= ~(0x1);
        goto state_label_49; // comment_block
      }break;
      case 0x2a:
      {
        state.ptr += 1;
        goto state_label_50; // comment_block_try_close
      }break;
    }
  }
  {
    state_label_50: // comment_block_try_close
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_BlockComment;
            token.kind = 3;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_EOF;
            token.kind = 0;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        result = true;
        goto end;
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_49; // comment_block
      }break;
      case 0x2a:
      {
        state.ptr += 1;
        goto state_label_50; // comment_block_try_close
      }break;
      case 0x2f:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_BlockComment;
            token.kind = 3;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_51: // comment_line
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LineComment;
            token.kind = 3;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_51; // comment_line
      }break;
      case 0x0a:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LineComment;
            token.kind = 3;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x5c:
      {
        state.ptr += 1;
        goto state_label_52; // comment_line_backslashing
      }break;
    }
  }
  {
    state_label_52: // comment_line_backslashing
    if (state.ptr == state.opl_ptr){
      if ((true)){
        result = true;
        goto end;
      }
    }
    switch (*state.ptr){
      default:
      {
        state.ptr += 1;
        goto state_label_51; // comment_line
      }break;
      case 0x0d:
      {
        state.ptr += 1;
        goto state_label_52; // comment_line_backslashing
      }break;
    }
  }
  {
    state_label_53: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Colon;
            token.kind = 15;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Colon;
            token.kind = 15;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3a:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_ColonColon;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_54: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Plus;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Plus;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PlusPlus;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PlusEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_55: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Minus;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Minus;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_MinusMinus;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_MinusEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3e:
      {
        state.ptr += 1;
        goto state_label_56; // op stage
      }break;
    }
  }
  {
    state_label_56: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Arrow;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Arrow;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2a:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_ArrowStar;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_57: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Less;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Less;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3c:
      {
        state.ptr += 1;
        goto state_label_66; // op stage
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        goto state_label_59; // op stage
      }break;
    }
  }
  {
    state_label_58: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Grtr;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Grtr;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_GrtrEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3e:
      {
        state.ptr += 1;
        goto state_label_67; // op stage
      }break;
    }
  }
  {
    state_label_59: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LessEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LessEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3e:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Compare;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_60: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Eq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Eq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_EqEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_61: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Not;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Not;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_NotEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_62: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_And;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_And;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x26:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_AndAnd;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_63: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Or;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Or;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x7c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_OrOr;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_64: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Star;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Star;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_StarEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_65: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Mod;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_Mod;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_ModEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_66: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LeftLeft;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LeftLeft;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LeftLeftEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_67: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_RightRight;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_RightRight;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_RightRightEq;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_68: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PPStringify;
            token.kind = 15;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PPStringify;
            token.kind = 15;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x23:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_PPConcat;
            token.kind = 15;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  {
    state_label_69: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }
    }
    switch (*state.ptr){
      default:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_LexError;
            token.kind = 2;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
      case 0x2e:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          token.flags = state.flags_KB0;
          do{
            token.sub_kind = TokenCppKind_DotDotDot;
            token.kind = 7;
          }while(0);
          token_list_push(arena, list, &token);
          emit_counter += 1;
          state.emit_ptr = state.ptr;
          if (emit_counter == max){
            goto end;
          }
        }
        state.flags_ZF0 = 0;
        goto state_label_1; // root
      }break;
    }
  }
  end:;
  block_copy_struct(state_ptr, &state);
  return(result);
}
internal Token_List
lex_full_input_cpp(Arena *arena, String_Const_u8 input){
  Lex_State_Cpp state = {};
  lex_full_input_cpp_init(&state, input);
  Token_List list = {};
  lex_full_input_cpp_breaks(arena, &list, &state, max_u64);
  return(list);
}
