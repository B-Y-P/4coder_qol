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
u64 odin_main_keys_hash_array[319] = {
  0x0000000000000000,0x0000000000000000,0xa5276d4f814ee5c7,0x0000000000000000,
  0x0000000000000000,0x097404c0eff5432b,0x29d3adff7b2c316b,0xe079d93ffe5fea6b,
  0xa5276d4f814e57bf,0x29d3adff7bc6e10b,0x0000000000000000,0x5158a060677fcaf7,
  0x38f7154c8eb0291d,0x0000000000000000,0x0000000000000000,0xe6f687da7899d2ed,
  0x29d3adff7b35d875,0x097404c0c6b51fcf,0xe6f687d7a2f4e4bf,0xa5276d4f814e4797,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0xa5276d4f814e0d0b,0x097404c0ccd49bab,0x38f7154c8eb0256d,0x0000000000000000,
  0x0000000000000000,0xa3efa314600b255b,0x0000000000000000,0xa3efa30df90d941d,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x51591546f1bca239,0xa5276d4f814e0e5b,0x6d1399a01f772f2d,0x29d3adff7bd42747,
  0x0000000000000000,0x6d3a315a3f3301eb,0x097404c0cd74ea9b,0x0000000000000000,
  0x94ccdc77a5c2712b,0xe6f686958346ab1b,0xfc0d9b5a8badd31f,0xe6f68076bd2abbd7,
  0x7cde8f5e2d65b165,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x6d3f63d42546b63b,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x19c3a853d4162abd,0x0b7d2602cabbf07f,
  0x5159175003125b7f,0x6d17be2e2ff8968b,0x0000000000000000,0x0000000000000000,
  0x94ccdc7647d428bf,0xa3efa3164280e6fb,0x29d3adff7b2d01c7,0xa5276d4f814e454f,
  0x29d3adff7b325641,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x5159ff0a5b9095b5,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x097404c0c6a9ae85,0x0000000000000000,0xa5276d4f814d932f,0x6d136892ea3e037f,
  0x0000000000000000,0xa3efa30d996c6d6b,0x0000000000000000,0x0000000000000000,
  0xbc42476212340b39,0xa5276d4f814e0e93,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0xa3efa30c871a0f2d,0x0000000000000000,0x29d3adff7b395009,0xa5276d4f814ef7a1,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x29d3adff7b231663,
  0x0000000000000000,0x0000000000000000,0x63e261c30eaba8d1,0xe6f687d184f1685b,
  0x0000000000000000,0xeb5740cdcb1194ef,0xa5276d4f814f0e1b,0x6d16cbae2f16c305,
  0x097404c0cc9db41b,0x29d3adff7b0558cb,0x0000000000000000,0x6d1546752d4f2f7f,
  0xa3efa30d7fcf7cc9,0x29d3adff7b395019,0x5cd982e953760387,0x097404c0f02a97d7,
  0x0000000000000000,0x38f7154c8eb02497,0xa5276d4f814ef7b9,0xa3efa30d7fcc3b2d,
  0xa5276d4f814d90db,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0xe6f6869584db75dd,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x097404c0ccd4a61b,0x6d3f63d42546b7cf,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0xb057cb5b27b95c9b,0xa5276d4f814ef191,0x0000000000000000,
  0x0000000000000000,0xa3efa30d8279126d,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x29d3adff7b291489,
  0xa3efa3130e988059,0x0000000000000000,0x0000000000000000,0x097404c0f516a84b,
  0x1b727097b544ea39,0x51589e3dded3cbd7,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x29d3adff7bd4611b,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x097404c0ebe8341b,0x0000000000000000,0xc745f296e1f7d937,
  0x097404c0ef82d1b5,0x2feb2aadce470e8f,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x097404c0cd74edab,0x0000000000000000,0x0000000000000000,0xa3efa30d996c615b,
  0xe6f686415cc3f507,0xa5276d4f814f01f3,0x0000000000000000,0x38f7154c8eb024dd,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x2d635f642e2d8c81,
  0x1e47c9754bdb12ed,0x2feb2aadce45dd57,0x097404c0cc9db96b,0x0000000000000000,
  0x0000000000000000,0xa5276d4f814ee05b,0x0000000000000000,0x6d3f764c1d6cd0c9,
  0x94ccdc763fa1956b,0x0000000000000000,0x00a28a4d3cc6f91d,0x0000000000000000,
  0x097404c0ebed97ab,0x0000000000000000,0xe6f687d968815659,0x6b61396e7132ef87,
  0x097404c0eb997dab,0x38f7154c8eb0276f,0x0000000000000000,0xa5276d4f814d8ff7,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0xa5276d4f814f0fcb,
  0x0000000000000000,0x29d3adff7b048ba1,0xa5276d4f814d8609,0x0000000000000000,
  0xa5276d4f814d9281,0x0000000000000000,0x097404c0f4fac971,0xcdfbe3ecd09c2b2f,
  0xa5276d4f814d9007,0x5273f87742b4465b,0x0000000000000000,0x0000000000000000,
  0xe6f6806292e88fd7,0x30a9094eeac0d31f,0x29d3adff7b2c311b,0x0000000000000000,
  0x29d3adff7bcf53f3,0x097404c0f516a9db,0xa3efa30c9565c909,0xa3efa30bf3b4069b,
  0x0000000000000000,0x0000000000000000,0x29d3adff7bd4616b,0x0000000000000000,
  0x29d3adff7b3a7a6f,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0xa5276d4f814e6671,0x19a326d3a912f0fb,0x0000000000000000,
  0x0000000000000000,0x29d3adff7bc597d5,0x097404c0ebe8396b,0x0000000000000000,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x09740a63b3c7848b,0xe6f6804198486625,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x097404c0ebeda81b,0x0000000000000000,0x38f7154c8eb022af,
  0xff5f9cc47a5b362b,0x29d3adff7bf99a67,0x097404c0eff5725b,0x0000000000000000,
  0x0000000000000000,0x097404c0e80a760b,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0xbc4247621275dc69,0x9c666eabafeb648b,0xa5276d4f814ef5db,
  0xe6f6807ef052ac75,0x097404c0c415ab3b,0x0000000000000000,0xf200c84bef199c6b,
  0x5cd98286c20fe8c7,0x097404c0eb99029b,0xa3efa314600b216b,0xe6f681fe59e41b89,
  0x0000000000000000,0x29d3adff7b2e4ba3,0x29d3adff7bd2ac39,0x0000000000000000,
  0x29d3adff7bee548b,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0xe6f68645b13ecba5,0xa5276d4f814e44fb,0x097404c0f51058ab,0x5c67459a725d7a9f,
  0x0000000000000000,0x0000000000000000,0x0000000000000000,0x0000000000000000,
  0x0000000000000000,0x097404c0f510c51b,0xb15699ca697de54b,
};
u8 odin_main_keys_key_array_2[] = {0x6c,0x65,0x6e,};
u8 odin_main_keys_key_array_5[] = {0x66,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_6[] = {0x69,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_7[] = {0x4f,0x44,0x49,0x4e,0x5f,0x4f,0x53,};
u8 odin_main_keys_key_array_8[] = {0x66,0x6f,0x72,};
u8 odin_main_keys_key_array_9[] = {0x72,0x75,0x6e,0x65,};
u8 odin_main_keys_key_array_11[] = {0x72,0x61,0x77,0x5f,0x64,0x61,0x74,0x61,};
u8 odin_main_keys_key_array_12[] = {0x75,0x38,};
u8 odin_main_keys_key_array_15[] = {0x63,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_16[] = {0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_17[] = {0x75,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_18[] = {0x64,0x79,0x6e,0x61,0x6d,0x69,0x63,};
u8 odin_main_keys_key_array_19[] = {0x66,0x31,0x36,};
u8 odin_main_keys_key_array_24[] = {0x69,0x33,0x32,};
u8 odin_main_keys_key_array_25[] = {0x75,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_26[] = {0x64,0x6f,};
u8 odin_main_keys_key_array_29[] = {0x69,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_31[] = {0x6d,0x61,0x74,0x72,0x69,0x78,};
u8 odin_main_keys_key_array_40[] = {0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_41[] = {0x69,0x36,0x34,};
u8 odin_main_keys_key_array_42[] = {0x6f,0x72,0x5f,0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_43[] = {0x75,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_45[] = {0x62,0x69,0x74,0x5f,0x66,0x69,0x65,0x6c,0x64,};
u8 odin_main_keys_key_array_46[] = {0x75,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_48[] = {0x4f,0x44,0x49,0x4e,0x5f,0x4e,0x4f,0x5f,0x43,0x52,0x54,};
u8 odin_main_keys_key_array_49[] = {0x63,0x6f,0x6e,0x74,0x65,0x78,0x74,};
u8 odin_main_keys_key_array_50[] = {0x4f,0x44,0x49,0x4e,0x5f,0x44,0x45,0x46,0x41,0x55,0x4c,0x54,0x5f,0x54,0x4f,0x5f,0x50,0x41,0x4e,0x49,0x43,0x5f,0x41,0x4c,0x4c,0x4f,0x43,0x41,0x54,0x4f,0x52,};
u8 odin_main_keys_key_array_51[] = {0x74,0x79,0x70,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_52[] = {0x5f,};
u8 odin_main_keys_key_array_60[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x36,0x34,};
u8 odin_main_keys_key_array_66[] = {0x4f,0x44,0x49,0x4e,0x5f,0x50,0x4c,0x41,0x54,0x46,0x4f,0x52,0x4d,0x5f,0x53,0x55,0x42,0x54,0x41,0x52,0x47,0x45,0x54,};
u8 odin_main_keys_key_array_67[] = {0x6f,0x66,0x66,0x73,0x65,0x74,0x5f,0x6f,0x66,0x5f,0x73,0x65,0x6c,0x65,0x63,0x74,0x6f,0x72,};
u8 odin_main_keys_key_array_68[] = {0x61,0x6c,0x69,0x67,0x6e,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_69[] = {0x74,0x72,0x61,0x6e,0x73,0x6d,0x75,0x74,0x65,};
u8 odin_main_keys_key_array_72[] = {0x4f,0x44,0x49,0x4e,0x5f,0x56,0x45,0x4e,0x44,0x4f,0x52,};
u8 odin_main_keys_key_array_73[] = {0x69,0x6d,0x70,0x6f,0x72,0x74,};
u8 odin_main_keys_key_array_74[] = {0x69,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_75[] = {0x66,0x33,0x32,};
u8 odin_main_keys_key_array_76[] = {0x65,0x6e,0x75,0x6d,};
u8 odin_main_keys_key_array_83[] = {0x64,0x69,0x73,0x74,0x69,0x6e,0x63,0x74,};
u8 odin_main_keys_key_array_88[] = {0x75,0x73,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_90[] = {0x62,0x33,0x32,};
u8 odin_main_keys_key_array_91[] = {0x6f,0x66,0x66,0x73,0x65,0x74,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_93[] = {0x75,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_96[] = {0x4f,0x44,0x49,0x4e,0x5f,0x41,0x52,0x43,0x48,};
u8 odin_main_keys_key_array_97[] = {0x69,0x31,0x36,};
u8 odin_main_keys_key_array_104[] = {0x72,0x65,0x74,0x75,0x72,0x6e,};
u8 odin_main_keys_key_array_106[] = {0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_107[] = {0x6d,0x61,0x78,};
u8 odin_main_keys_key_array_111[] = {0x69,0x6d,0x61,0x67,};
u8 odin_main_keys_key_array_114[] = {0x4f,0x44,0x49,0x4e,0x5f,0x43,0x4f,0x4d,0x50,0x49,0x4c,0x45,0x5f,0x54,0x49,0x4d,0x45,0x53,0x54,0x41,0x4d,0x50,};
u8 odin_main_keys_key_array_115[] = {0x73,0x77,0x69,0x7a,0x7a,0x6c,0x65,};
u8 odin_main_keys_key_array_117[] = {0x65,0x78,0x70,0x61,0x6e,0x64,0x5f,0x76,0x61,0x6c,0x75,0x65,0x73,};
u8 odin_main_keys_key_array_118[] = {0x75,0x36,0x34,};
u8 odin_main_keys_key_array_119[] = {0x73,0x6f,0x61,0x5f,0x75,0x6e,0x7a,0x69,0x70,};
u8 odin_main_keys_key_array_120[] = {0x75,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_121[] = {0x62,0x79,0x74,0x65,};
u8 odin_main_keys_key_array_123[] = {0x74,0x79,0x70,0x65,0x69,0x64,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_124[] = {0x73,0x74,0x72,0x75,0x63,0x74,};
u8 odin_main_keys_key_array_125[] = {0x63,0x61,0x73,0x65,};
u8 odin_main_keys_key_array_126[] = {0x4f,0x44,0x49,0x4e,0x5f,0x56,0x45,0x52,0x53,0x49,0x4f,0x4e,};
u8 odin_main_keys_key_array_127[] = {0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_129[] = {0x69,0x66,};
u8 odin_main_keys_key_array_130[] = {0x6d,0x61,0x70,};
u8 odin_main_keys_key_array_131[] = {0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_132[] = {0x62,0x36,0x34,};
u8 odin_main_keys_key_array_140[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,};
u8 odin_main_keys_key_array_144[] = {0x75,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_145[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x33,0x32,};
u8 odin_main_keys_key_array_149[] = {0x75,0x6e,0x72,0x65,0x61,0x63,0x68,0x61,0x62,0x6c,0x65,};
u8 odin_main_keys_key_array_150[] = {0x6e,0x69,0x6c,};
u8 odin_main_keys_key_array_153[] = {0x74,0x79,0x70,0x65,0x69,0x64,};
u8 odin_main_keys_key_array_163[] = {0x63,0x6f,0x6e,0x6a,};
u8 odin_main_keys_key_array_164[] = {0x73,0x77,0x69,0x74,0x63,0x68,};
u8 odin_main_keys_key_array_167[] = {0x66,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_168[] = {0x6f,0x72,0x5f,0x63,0x6f,0x6e,0x74,0x69,0x6e,0x75,0x65,};
u8 odin_main_keys_key_array_169[] = {0x6f,0x72,0x5f,0x62,0x72,0x65,0x61,0x6b,};
u8 odin_main_keys_key_array_174[] = {0x75,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_181[] = {0x69,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_183[] = {0x63,0x6f,0x6d,0x70,0x6c,0x65,0x78,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_184[] = {0x66,0x61,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_185[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x32,0x35,0x36,};
u8 odin_main_keys_key_array_192[] = {0x75,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_195[] = {0x75,0x31,0x32,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_196[] = {0x66,0x6f,0x72,0x65,0x69,0x67,0x6e,};
u8 odin_main_keys_key_array_197[] = {0x75,0x31,0x36,};
u8 odin_main_keys_key_array_199[] = {0x69,0x38,};
u8 odin_main_keys_key_array_203[] = {0x4f,0x44,0x49,0x4e,0x5f,0x57,0x49,0x4e,0x44,0x4f,0x57,0x53,0x5f,0x53,0x55,0x42,0x53,0x59,0x53,0x54,0x45,0x4d,};
u8 odin_main_keys_key_array_204[] = {0x6f,0x66,0x66,0x73,0x65,0x74,0x5f,0x6f,0x66,0x5f,0x62,0x79,0x5f,0x73,0x74,0x72,0x69,0x6e,0x67,};
u8 odin_main_keys_key_array_205[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x31,0x32,0x38,};
u8 odin_main_keys_key_array_206[] = {0x75,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_209[] = {0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_211[] = {0x61,0x75,0x74,0x6f,0x5f,0x63,0x61,0x73,0x74,};
u8 odin_main_keys_key_array_212[] = {0x4f,0x44,0x49,0x4e,0x5f,0x45,0x4e,0x44,0x49,0x41,0x4e,};
u8 odin_main_keys_key_array_214[] = {0x66,0x61,0x6c,0x6c,0x74,0x68,0x72,0x6f,0x75,0x67,0x68,};
u8 odin_main_keys_key_array_216[] = {0x69,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_218[] = {0x70,0x61,0x63,0x6b,0x61,0x67,0x65,};
u8 odin_main_keys_key_array_219[] = {0x74,0x79,0x70,0x65,0x5f,0x69,0x6e,0x66,0x6f,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_220[] = {0x69,0x33,0x32,0x62,0x65,};
u8 odin_main_keys_key_array_221[] = {0x69,0x6e,};
u8 odin_main_keys_key_array_223[] = {0x62,0x31,0x36,};
u8 odin_main_keys_key_array_231[] = {0x75,0x33,0x32,};
u8 odin_main_keys_key_array_233[] = {0x62,0x6f,0x6f,0x6c,};
u8 odin_main_keys_key_array_234[] = {0x61,0x62,0x73,};
u8 odin_main_keys_key_array_236[] = {0x61,0x73,0x6d,};
u8 odin_main_keys_key_array_238[] = {0x63,0x6c,0x61,0x6d,0x70,};
u8 odin_main_keys_key_array_239[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,};
u8 odin_main_keys_key_array_240[] = {0x61,0x6e,0x79,};
u8 odin_main_keys_key_array_241[] = {0x71,0x75,0x61,0x74,0x65,0x72,0x6e,0x69,0x6f,0x6e,0x36,0x34,};
u8 odin_main_keys_key_array_244[] = {0x73,0x69,0x7a,0x65,0x5f,0x6f,0x66,};
u8 odin_main_keys_key_array_245[] = {0x4f,0x44,0x49,0x4e,0x5f,0x44,0x45,0x46,0x41,0x55,0x4c,0x54,0x5f,0x54,0x4f,0x5f,0x4e,0x49,0x4c,0x5f,0x41,0x4c,0x4c,0x4f,0x43,0x41,0x54,0x4f,0x52,};
u8 odin_main_keys_key_array_246[] = {0x69,0x38,0x6c,0x65,};
u8 odin_main_keys_key_array_248[] = {0x6b,0x6d,0x61,0x67,};
u8 odin_main_keys_key_array_249[] = {0x66,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_250[] = {0x72,0x61,0x77,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_251[] = {0x6e,0x6f,0x74,0x5f,0x69,0x6e,};
u8 odin_main_keys_key_array_254[] = {0x75,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_256[] = {0x70,0x72,0x6f,0x63,};
u8 odin_main_keys_key_array_261[] = {0x63,0x61,0x70,};
u8 odin_main_keys_key_array_262[] = {0x4f,0x44,0x49,0x4e,0x5f,0x44,0x49,0x53,0x41,0x42,0x4c,0x45,0x5f,0x41,0x53,0x53,0x45,0x52,0x54,};
u8 odin_main_keys_key_array_265[] = {0x72,0x65,0x61,0x6c,};
u8 odin_main_keys_key_array_266[] = {0x69,0x31,0x36,0x62,0x65,};
u8 odin_main_keys_key_array_272[] = {0x4d,0x61,0x79,0x62,0x65,};
u8 odin_main_keys_key_array_273[] = {0x6f,0x72,0x5f,0x65,0x6c,0x73,0x65,};
u8 odin_main_keys_key_array_277[] = {0x69,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_279[] = {0x62,0x38,};
u8 odin_main_keys_key_array_280[] = {0x4f,0x44,0x49,0x4e,0x5f,0x4e,0x4f,0x5f,0x45,0x4e,0x54,0x52,0x59,0x5f,0x50,0x4f,0x49,0x4e,0x54,};
u8 odin_main_keys_key_array_281[] = {0x77,0x68,0x65,0x6e,};
u8 odin_main_keys_key_array_282[] = {0x66,0x31,0x36,0x6c,0x65,};
u8 odin_main_keys_key_array_285[] = {0x64,0x65,0x66,0x65,0x72,};
u8 odin_main_keys_key_array_289[] = {0x4f,0x44,0x49,0x4e,0x5f,0x52,0x4f,0x4f,0x54,};
u8 odin_main_keys_key_array_290[] = {0x6f,0x66,0x66,0x73,0x65,0x74,0x5f,0x6f,0x66,0x5f,0x6d,0x65,0x6d,0x62,0x65,0x72,};
u8 odin_main_keys_key_array_291[] = {0x6d,0x69,0x6e,};
u8 odin_main_keys_key_array_292[] = {0x73,0x6f,0x61,0x5f,0x7a,0x69,0x70,};
u8 odin_main_keys_key_array_293[] = {0x77,0x68,0x65,0x72,0x65,};
u8 odin_main_keys_key_array_295[] = {0x4f,0x44,0x49,0x4e,0x5f,0x45,0x52,0x52,0x4f,0x52,0x5f,0x50,0x4f,0x53,0x5f,0x53,0x54,0x59,0x4c,0x45,};
u8 odin_main_keys_key_array_296[] = {0x4f,0x44,0x49,0x4e,0x5f,0x4e,0x4f,0x5f,0x52,0x54,0x54,0x49,};
u8 odin_main_keys_key_array_297[] = {0x69,0x33,0x32,0x6c,0x65,};
u8 odin_main_keys_key_array_298[] = {0x69,0x31,0x32,0x38,0x62,0x65,};
u8 odin_main_keys_key_array_299[] = {0x75,0x69,0x6e,0x74,0x70,0x74,0x72,};
u8 odin_main_keys_key_array_301[] = {0x6a,0x6d,0x61,0x67,};
u8 odin_main_keys_key_array_302[] = {0x74,0x72,0x75,0x65,};
u8 odin_main_keys_key_array_304[] = {0x75,0x69,0x6e,0x74,};
u8 odin_main_keys_key_array_308[] = {0x62,0x69,0x74,0x5f,0x73,0x65,0x74,};
u8 odin_main_keys_key_array_309[] = {0x66,0x36,0x34,};
u8 odin_main_keys_key_array_310[] = {0x66,0x36,0x34,0x62,0x65,};
u8 odin_main_keys_key_array_311[] = {0x4f,0x44,0x49,0x4e,0x5f,0x44,0x45,0x42,0x55,0x47,};
u8 odin_main_keys_key_array_317[] = {0x66,0x36,0x34,0x6c,0x65,};
u8 odin_main_keys_key_array_318[] = {0x4f,0x44,0x49,0x4e,0x5f,0x42,0x55,0x49,0x4c,0x44,0x5f,0x4d,0x4f,0x44,0x45,};
String_Const_u8 odin_main_keys_key_array[319] = {
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_2, 3},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_5, 5},
  {odin_main_keys_key_array_6, 4},
  {odin_main_keys_key_array_7, 7},
  {odin_main_keys_key_array_8, 3},
  {odin_main_keys_key_array_9, 4},
  {0, 0},
  {odin_main_keys_key_array_11, 8},
  {odin_main_keys_key_array_12, 2},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_15, 7},
  {odin_main_keys_key_array_16, 4},
  {odin_main_keys_key_array_17, 5},
  {odin_main_keys_key_array_18, 7},
  {odin_main_keys_key_array_19, 3},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_24, 3},
  {odin_main_keys_key_array_25, 5},
  {odin_main_keys_key_array_26, 2},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_29, 6},
  {0, 0},
  {odin_main_keys_key_array_31, 6},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_40, 8},
  {odin_main_keys_key_array_41, 3},
  {odin_main_keys_key_array_42, 9},
  {odin_main_keys_key_array_43, 4},
  {0, 0},
  {odin_main_keys_key_array_45, 9},
  {odin_main_keys_key_array_46, 5},
  {0, 0},
  {odin_main_keys_key_array_48, 11},
  {odin_main_keys_key_array_49, 7},
  {odin_main_keys_key_array_50, 31},
  {odin_main_keys_key_array_51, 7},
  {odin_main_keys_key_array_52, 1},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_60, 9},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_66, 23},
  {odin_main_keys_key_array_67, 18},
  {odin_main_keys_key_array_68, 8},
  {odin_main_keys_key_array_69, 9},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_72, 11},
  {odin_main_keys_key_array_73, 6},
  {odin_main_keys_key_array_74, 4},
  {odin_main_keys_key_array_75, 3},
  {odin_main_keys_key_array_76, 4},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_83, 8},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_88, 5},
  {0, 0},
  {odin_main_keys_key_array_90, 3},
  {odin_main_keys_key_array_91, 9},
  {0, 0},
  {odin_main_keys_key_array_93, 6},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_96, 9},
  {odin_main_keys_key_array_97, 3},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_104, 6},
  {0, 0},
  {odin_main_keys_key_array_106, 4},
  {odin_main_keys_key_array_107, 3},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_111, 4},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_114, 22},
  {odin_main_keys_key_array_115, 7},
  {0, 0},
  {odin_main_keys_key_array_117, 13},
  {odin_main_keys_key_array_118, 3},
  {odin_main_keys_key_array_119, 9},
  {odin_main_keys_key_array_120, 5},
  {odin_main_keys_key_array_121, 4},
  {0, 0},
  {odin_main_keys_key_array_123, 9},
  {odin_main_keys_key_array_124, 6},
  {odin_main_keys_key_array_125, 4},
  {odin_main_keys_key_array_126, 12},
  {odin_main_keys_key_array_127, 5},
  {0, 0},
  {odin_main_keys_key_array_129, 2},
  {odin_main_keys_key_array_130, 3},
  {odin_main_keys_key_array_131, 6},
  {odin_main_keys_key_array_132, 3},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_140, 7},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_144, 5},
  {odin_main_keys_key_array_145, 9},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_149, 11},
  {odin_main_keys_key_array_150, 3},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_153, 6},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_163, 4},
  {odin_main_keys_key_array_164, 6},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_167, 5},
  {odin_main_keys_key_array_168, 11},
  {odin_main_keys_key_array_169, 8},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_174, 4},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_181, 5},
  {0, 0},
  {odin_main_keys_key_array_183, 10},
  {odin_main_keys_key_array_184, 5},
  {odin_main_keys_key_array_185, 13},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_192, 5},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_195, 6},
  {odin_main_keys_key_array_196, 7},
  {odin_main_keys_key_array_197, 3},
  {0, 0},
  {odin_main_keys_key_array_199, 2},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_203, 22},
  {odin_main_keys_key_array_204, 19},
  {odin_main_keys_key_array_205, 13},
  {odin_main_keys_key_array_206, 5},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_209, 3},
  {0, 0},
  {odin_main_keys_key_array_211, 9},
  {odin_main_keys_key_array_212, 11},
  {0, 0},
  {odin_main_keys_key_array_214, 11},
  {0, 0},
  {odin_main_keys_key_array_216, 5},
  {0, 0},
  {odin_main_keys_key_array_218, 7},
  {odin_main_keys_key_array_219, 12},
  {odin_main_keys_key_array_220, 5},
  {odin_main_keys_key_array_221, 2},
  {0, 0},
  {odin_main_keys_key_array_223, 3},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_231, 3},
  {0, 0},
  {odin_main_keys_key_array_233, 4},
  {odin_main_keys_key_array_234, 3},
  {0, 0},
  {odin_main_keys_key_array_236, 3},
  {0, 0},
  {odin_main_keys_key_array_238, 5},
  {odin_main_keys_key_array_239, 10},
  {odin_main_keys_key_array_240, 3},
  {odin_main_keys_key_array_241, 12},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_244, 7},
  {odin_main_keys_key_array_245, 29},
  {odin_main_keys_key_array_246, 4},
  {0, 0},
  {odin_main_keys_key_array_248, 4},
  {odin_main_keys_key_array_249, 5},
  {odin_main_keys_key_array_250, 6},
  {odin_main_keys_key_array_251, 6},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_254, 4},
  {0, 0},
  {odin_main_keys_key_array_256, 4},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_261, 3},
  {odin_main_keys_key_array_262, 19},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_265, 4},
  {odin_main_keys_key_array_266, 5},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_272, 5},
  {odin_main_keys_key_array_273, 7},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_277, 5},
  {0, 0},
  {odin_main_keys_key_array_279, 2},
  {odin_main_keys_key_array_280, 19},
  {odin_main_keys_key_array_281, 4},
  {odin_main_keys_key_array_282, 5},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_285, 5},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_289, 9},
  {odin_main_keys_key_array_290, 16},
  {odin_main_keys_key_array_291, 3},
  {odin_main_keys_key_array_292, 7},
  {odin_main_keys_key_array_293, 5},
  {0, 0},
  {odin_main_keys_key_array_295, 20},
  {odin_main_keys_key_array_296, 12},
  {odin_main_keys_key_array_297, 5},
  {odin_main_keys_key_array_298, 6},
  {odin_main_keys_key_array_299, 7},
  {0, 0},
  {odin_main_keys_key_array_301, 4},
  {odin_main_keys_key_array_302, 4},
  {0, 0},
  {odin_main_keys_key_array_304, 4},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_308, 7},
  {odin_main_keys_key_array_309, 3},
  {odin_main_keys_key_array_310, 5},
  {odin_main_keys_key_array_311, 10},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {odin_main_keys_key_array_317, 5},
  {odin_main_keys_key_array_318, 15},
};
Lexeme_Table_Value odin_main_keys_value_array[319] = {
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Len},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_F16BE},
  {16, TokenOdinKind_I8BE},
  {5, TokenOdinKind_Odin_OS},
  {17, TokenOdinKind_For},
  {16, TokenOdinKind_Rune},
  {0, 0},
  {4, TokenOdinKind_RawData},
  {16, TokenOdinKind_U8},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_CString},
  {17, TokenOdinKind_Else},
  {18, TokenOdinKind_Union},
  {4, TokenOdinKind_Dynamic},
  {16, TokenOdinKind_F16},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_I32},
  {16, TokenOdinKind_U64BE},
  {17, TokenOdinKind_Do},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_I128LE},
  {0, 0},
  {16, TokenOdinKind_Matrix},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {17, TokenOdinKind_Continue},
  {16, TokenOdinKind_I64},
  {17, TokenOdinKind_OrReturn},
  {16, TokenOdinKind_U128},
  {0, 0},
  {18, TokenOdinKind_BitField},
  {16, TokenOdinKind_U32LE},
  {0, 0},
  {5, TokenOdinKind_Odin_No_CRT},
  {4, TokenOdinKind_Context},
  {5, TokenOdinKind_Odin_Default_To_Panic_Allocator},
  {4, TokenOdinKind_TypeOf},
  {7, TokenOdinKind_Ignore},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_Complex64},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {5, TokenOdinKind_Odin_Platform_Subtarget},
  {4, TokenOdinKind_OffsetOfSelector},
  {4, TokenOdinKind_AlignOf},
  {4, TokenOdinKind_Transmute},
  {0, 0},
  {0, 0},
  {5, TokenOdinKind_Odin_Vendor},
  {4, TokenOdinKind_Import},
  {16, TokenOdinKind_I128},
  {16, TokenOdinKind_F32},
  {18, TokenOdinKind_Enum},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Distinct},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Using},
  {0, 0},
  {16, TokenOdinKind_B32},
  {4, TokenOdinKind_OffsetOf},
  {0, 0},
  {16, TokenOdinKind_U128BE},
  {0, 0},
  {0, 0},
  {5, TokenOdinKind_Odin_Arch},
  {16, TokenOdinKind_I16},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {17, TokenOdinKind_Return},
  {0, 0},
  {4, TokenOdinKind_Cast},
  {4, TokenOdinKind_Max},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Imag},
  {0, 0},
  {0, 0},
  {5, TokenOdinKind_Odin_Compile_Timestamp},
  {4, TokenOdinKind_Swizzle},
  {0, 0},
  {4, TokenOdinKind_ExpandValues},
  {16, TokenOdinKind_U64},
  {4, TokenOdinKind_SoaUnzip},
  {16, TokenOdinKind_U16LE},
  {16, TokenOdinKind_Byte},
  {0, 0},
  {4, TokenOdinKind_TypeidOf},
  {18, TokenOdinKind_Struct},
  {17, TokenOdinKind_Case},
  {5, TokenOdinKind_Odin_Version},
  {17, TokenOdinKind_Break},
  {0, 0},
  {17, TokenOdinKind_If},
  {16, TokenOdinKind_Map},
  {16, TokenOdinKind_String},
  {16, TokenOdinKind_B64},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Complex},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_U64LE},
  {16, TokenOdinKind_Complex32},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Unreachable},
  {8, TokenOdinKind_LiteralNull},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_TypeID},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Conj},
  {17, TokenOdinKind_Switch},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_F32BE},
  {17, TokenOdinKind_OrContinue},
  {17, TokenOdinKind_OrBreak},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_U8LE},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_I16LE},
  {0, 0},
  {16, TokenOdinKind_Complex128},
  {8, TokenOdinKind_LiteralFalse},
  {16, TokenOdinKind_Quaternion256},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_U32BE},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_U128LE},
  {4, TokenOdinKind_Foreign},
  {16, TokenOdinKind_U16},
  {0, 0},
  {16, TokenOdinKind_I8},
  {0, 0},
  {0, 0},
  {0, 0},
  {5, TokenOdinKind_Odin_Windows_Subsystem},
  {4, TokenOdinKind_OffsetOfByString},
  {16, TokenOdinKind_Quaternion128},
  {16, TokenOdinKind_U16BE},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_Int},
  {0, 0},
  {4, TokenOdinKind_AutoCast},
  {5, TokenOdinKind_Odin_Endian},
  {0, 0},
  {17, TokenOdinKind_Fallthrough},
  {0, 0},
  {16, TokenOdinKind_I64BE},
  {0, 0},
  {4, TokenOdinKind_Package},
  {4, TokenOdinKind_TypeInfoOf},
  {16, TokenOdinKind_I32BE},
  {7, TokenOdinKind_In},
  {0, 0},
  {16, TokenOdinKind_B16},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_U32},
  {0, 0},
  {16, TokenOdinKind_Bool},
  {4, TokenOdinKind_Abs},
  {0, 0},
  {4, TokenOdinKind_Asm},
  {0, 0},
  {4, TokenOdinKind_Clamp},
  {4, TokenOdinKind_Quaternion},
  {16, TokenOdinKind_Any},
  {16, TokenOdinKind_Quaternion64},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_SizeOf},
  {5, TokenOdinKind_Odin_Default_To_Nil_Allocator},
  {16, TokenOdinKind_I8LE},
  {0, 0},
  {4, TokenOdinKind_Kmag},
  {16, TokenOdinKind_F32LE},
  {16, TokenOdinKind_RawPtr},
  {7, TokenOdinKind_NotIn},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_U8BE},
  {0, 0},
  {4, TokenOdinKind_Proc},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Cap},
  {5, TokenOdinKind_Odin_Disable_Assert},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Real},
  {16, TokenOdinKind_I16BE},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {4, TokenOdinKind_Maybe},
  {17, TokenOdinKind_OrElse},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_I64LE},
  {0, 0},
  {16, TokenOdinKind_B8},
  {5, TokenOdinKind_Odin_No_Entry_Point},
  {17, TokenOdinKind_When},
  {16, TokenOdinKind_F16LE},
  {0, 0},
  {0, 0},
  {17, TokenOdinKind_Defer},
  {0, 0},
  {0, 0},
  {0, 0},
  {5, TokenOdinKind_Odin_Root},
  {4, TokenOdinKind_OffsetOfMember},
  {4, TokenOdinKind_Min},
  {4, TokenOdinKind_SoaZip},
  {17, TokenOdinKind_Where},
  {0, 0},
  {5, TokenOdinKind_Odin_Error_Pos_Style},
  {5, TokenOdinKind_Odin_No_RTTI},
  {16, TokenOdinKind_I32LE},
  {16, TokenOdinKind_I128BE},
  {16, TokenOdinKind_UIntPtr},
  {0, 0},
  {4, TokenOdinKind_Jmag},
  {8, TokenOdinKind_LiteralTrue},
  {0, 0},
  {16, TokenOdinKind_UInt},
  {0, 0},
  {0, 0},
  {0, 0},
  {18, TokenOdinKind_BitSet},
  {16, TokenOdinKind_F64},
  {16, TokenOdinKind_F64BE},
  {5, TokenOdinKind_Odin_Debug},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {0, 0},
  {16, TokenOdinKind_F64LE},
  {5, TokenOdinKind_Odin_Build_Mode},
};
i32 odin_main_keys_slot_count = 319;
u64 odin_main_keys_seed = 0x7cde8f5e2d65b106;
struct Lex_State_Odin{
  u32 flags_ZF0;
  u8 *base;
  u8 *delim_first;
  u8 *delim_one_past_last;
  u8 *emit_ptr;
  u8 *ptr;
  u8 *opl_ptr;
  i64 counter;
};

internal void
lex_full_input_odin_init(Lex_State_Odin *state_ptr, String_Const_u8 input){
  state_ptr->flags_ZF0 = 0;
  state_ptr->base = input.str;
  state_ptr->delim_first = input.str;
  state_ptr->delim_one_past_last = input.str;
  state_ptr->emit_ptr = input.str;
  state_ptr->ptr = input.str;
  state_ptr->opl_ptr = input.str + input.size;
  state_ptr->counter = 0;
}

internal b32
lex_full_input_odin_breaks(Arena *arena, Token_List *list, Lex_State_Odin *state_ptr, u64 max){
  b32 result = false;
  u64 emit_counter = 0;
  Lex_State_Odin state;
  block_copy_struct(&state, state_ptr);
  {
    state_label_1: // root
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_EOF;
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
      case 0x1a:case 0x1b:case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x7f:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
      case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:case 0x20:
      {
        state.ptr += 1;
        goto state_label_5; // whitespace
      }break;
      case 0x21:
      {
        state.ptr += 1;
        goto state_label_49; // op stage
      }break;
      case 0x22:
      {
        state.ptr += 1;
        goto state_label_24; // string
      }break;
      case 0x23:
      {
        state.ptr += 1;
        goto state_label_4; // directive
      }break;
      case 0x24:
      {
        state.ptr += 1;
        goto state_label_3; // parametric
      }break;
      case 0x25:
      {
        state.ptr += 1;
        goto state_label_44; // op stage
      }break;
      case 0x26:
      {
        state.ptr += 1;
        goto state_label_43; // op stage
      }break;
      case 0x27:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x1;
        goto state_label_24; // string
      }break;
      case 0x28:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_ParenOp;
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
          do{
            token.sub_kind = TokenOdinKind_ParenCl;
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
        goto state_label_52; // op stage
      }break;
      case 0x2b:
      {
        state.ptr += 1;
        goto state_label_51; // op stage
      }break;
      case 0x2c:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Comma;
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
        goto state_label_42; // op stage
      }break;
      case 0x2e:
      {
        state.ptr += 1;
        goto state_label_7; // operator_or_fnumber_dot
      }break;
      case 0x2f:
      {
        state.ptr += 1;
        goto state_label_8; // operator_or_comment_slash
      }break;
      case 0x30:
      {
        state.ptr += 1;
        goto state_label_10; // znumber
      }break;
      case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:case 0x37:
      case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_9; // number
      }break;
      case 0x3a:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Colon;
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
      case 0x3b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Semicolon;
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
        state.ptr += 1;
        goto state_label_46; // op stage
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        goto state_label_48; // op stage
      }break;
      case 0x3e:
      {
        state.ptr += 1;
        goto state_label_47; // op stage
      }break;
      case 0x3f:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Question;
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
      case 0x40:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_At;
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
      default:
      {
        state.ptr += 1;
        goto state_label_2; // identifier
      }break;
      case 0x5b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_BrackOp;
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
        goto state_label_6; // backslash
      }break;
      case 0x5d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_BrackCl;
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
          do{
            token.sub_kind = TokenOdinKind_Ptr;
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
      case 0x60:
      {
        state.ptr += 1;
        state.flags_ZF0 |= 0x2;
        goto state_label_24; // string
      }break;
      case 0x7b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_BraceOp;
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
        goto state_label_50; // op stage
      }break;
      case 0x7d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_BraceCl;
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
        goto state_label_55; // op stage
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
          do{
            Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_main_keys_hash_array, odin_main_keys_key_array, odin_main_keys_value_array, odin_main_keys_slot_count, odin_main_keys_seed, state.emit_ptr, token.size);
            if (lookup.found_match){
              token.kind = lookup.base_kind;
              token.sub_kind = lookup.sub_kind;
              break;
            }
            token.sub_kind = TokenOdinKind_Identifier;
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
      case 0x23:case 0x24:case 0x25:case 0x26:case 0x27:case 0x28:case 0x29:
      case 0x2a:case 0x2b:case 0x2c:case 0x2d:case 0x2e:case 0x2f:case 0x3a:
      case 0x3b:case 0x3c:case 0x3d:case 0x3e:case 0x3f:case 0x40:case 0x5b:
      case 0x5c:case 0x5d:case 0x5e:case 0x60:case 0x7b:case 0x7c:case 0x7d:
      case 0x7e:case 0x7f:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            Lexeme_Table_Lookup lookup = lexeme_table_lookup(odin_main_keys_hash_array, odin_main_keys_key_array, odin_main_keys_value_array, odin_main_keys_slot_count, odin_main_keys_seed, state.emit_ptr, token.size);
            if (lookup.found_match){
              token.kind = lookup.base_kind;
              token.sub_kind = lookup.sub_kind;
              break;
            }
            token.sub_kind = TokenOdinKind_Identifier;
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
    state_label_3: // parametric
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Parametric;
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
      case 0x23:case 0x24:case 0x25:case 0x26:case 0x27:case 0x28:case 0x29:
      case 0x2a:case 0x2b:case 0x2c:case 0x2d:case 0x2e:case 0x2f:case 0x3a:
      case 0x3b:case 0x3c:case 0x3d:case 0x3e:case 0x3f:case 0x40:case 0x5b:
      case 0x5c:case 0x5d:case 0x5e:case 0x60:case 0x7b:case 0x7c:case 0x7d:
      case 0x7e:case 0x7f:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Parametric;
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
        goto state_label_3; // parametric
      }break;
    }
  }
  {
    state_label_4: // directive
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Directive;
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
      case 0x1c:case 0x1d:case 0x1e:case 0x1f:case 0x20:case 0x22:case 0x23:
      case 0x24:case 0x25:case 0x26:case 0x27:case 0x28:case 0x29:case 0x2a:
      case 0x2c:case 0x2d:case 0x2e:case 0x2f:case 0x3a:case 0x3b:case 0x3c:
      case 0x3d:case 0x3e:case 0x3f:case 0x40:case 0x5b:case 0x5c:case 0x5d:
      case 0x5e:case 0x60:case 0x7b:case 0x7c:case 0x7d:case 0x7e:case 0x7f:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Directive;
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
      case 0x21:
      {
        state.ptr += 1;
        goto state_label_40; // comment_line
      }break;
      default:
      {
        state.ptr += 1;
        goto state_label_4; // directive
      }break;
    }
  }
  {
    state_label_5: // whitespace
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Whitespace;
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
          do{
            token.sub_kind = TokenOdinKind_Whitespace;
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
      case 0x09:case 0x0a:case 0x0b:case 0x0c:case 0x0d:case 0x20:
      {
        state.ptr += 1;
        goto state_label_5; // whitespace
      }break;
    }
  }
  {
    state_label_6: // backslash
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Backslash;
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
          do{
            token.sub_kind = TokenOdinKind_Backslash;
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
          do{
            token.sub_kind = TokenOdinKind_Backslash;
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
        goto state_label_6; // backslash
      }break;
    }
  }
  {
    state_label_7: // operator_or_fnumber_dot
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Dot;
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
          do{
            token.sub_kind = TokenOdinKind_Dot;
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
        goto state_label_60; // op stage
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_12; // fnumber_decimal
      }break;
    }
  }
  {
    state_label_8: // operator_or_comment_slash
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Div;
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
          do{
            token.sub_kind = TokenOdinKind_Div;
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
        state.counter += 1;
        goto state_label_37; // comment_block
      }break;
      case 0x2f:
      {
        state.ptr += 1;
        goto state_label_40; // comment_line
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_DivEq;
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
    state_label_9: // number
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerDec;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerDec;
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
        goto state_label_11; // fnumber_decimal_or_range
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x5f:
      {
        state.ptr += 1;
        goto state_label_9; // number
      }break;
      case 0x45:case 0x65:
      {
        state.ptr += 1;
        goto state_label_13; // fnumber_exponent
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_10: // znumber
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerDec;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerDec;
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
        goto state_label_11; // fnumber_decimal_or_range
      }break;
      case 0x45:case 0x65:
      {
        state.ptr += 1;
        goto state_label_13; // fnumber_exponent
      }break;
      case 0x62:
      {
        state.ptr += 1;
        goto state_label_16; // number_bin_first
      }break;
      case 0x64:
      {
        state.ptr += 1;
        goto state_label_18; // number_dec_first
      }break;
      case 0x68:case 0x78:
      {
        state.ptr += 1;
        goto state_label_20; // number_hex_first
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
      case 0x6f:
      {
        state.ptr += 1;
        goto state_label_17; // number_oct_first
      }break;
      case 0x7a:
      {
        state.ptr += 1;
        goto state_label_19; // number_doz_first
      }break;
    }
  }
  {
    state_label_11: // fnumber_decimal_or_range
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
      case 0x2e:
      {

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

        state.ptr += 1;
        goto state_label_61; // op stage
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_12; // fnumber_decimal
      }break;
    }
  }
  {
    state_label_12: // fnumber_decimal
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
      case 0x37:case 0x38:case 0x39:case 0x5f:
      {
        state.ptr += 1;
        goto state_label_12; // fnumber_decimal
      }break;
      case 0x45:case 0x65:
      {
        state.ptr += 1;
        goto state_label_13; // fnumber_exponent
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_13: // fnumber_exponent
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
        goto state_label_14; // fnumber_exponent_sign
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_15; // fnumber_exponent_digits
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_14: // fnumber_exponent_sign
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
        goto state_label_15; // fnumber_exponent_digits
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_15: // fnumber_exponent_digits
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralFloat;
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
        goto state_label_15; // fnumber_exponent_digits
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_16: // number_bin_first
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
      case 0x30:case 0x31:
      {
        state.ptr += 1;
        goto state_label_16; // number_bin_first
      }break;
    }
  }
  {
    state_label_17: // number_oct_first
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
      case 0x37:
      {
        state.ptr += 1;
        goto state_label_21; // number_oct
      }break;
    }
  }
  {
    state_label_18: // number_dec_first
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
      case 0x37:case 0x38:case 0x39:
      {
        state.ptr += 1;
        goto state_label_9; // number
      }break;
    }
  }
  {
    state_label_19: // number_doz_first
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x61:case 0x62:
      {
        state.ptr += 1;
        goto state_label_22; // number_doz
      }break;
    }
  }
  {
    state_label_20: // number_hex_first
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
        goto state_label_23; // number_hex
      }break;
    }
  }
  {
    state_label_21: // number_oct
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerOct;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerOct;
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
      case 0x37:case 0x5f:
      {
        state.ptr += 1;
        goto state_label_21; // number_oct
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_22: // number_doz
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerDoz;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerDoz;
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
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x5f:case 0x61:
      case 0x62:
      {
        state.ptr += 1;
        goto state_label_22; // number_doz
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_23: // number_hex
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerHex;
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
          do{
            token.sub_kind = TokenOdinKind_LiteralIntegerHex;
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
      case 0x45:case 0x46:case 0x5f:case 0x61:case 0x62:case 0x63:case 0x64:
      case 0x65:case 0x66:
      {
        state.ptr += 1;
        goto state_label_23; // number_hex
      }break;
      case 0x69:case 0x6a:case 0x6b:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LiteralQuaternion;
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
    state_label_24: // string
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
        goto state_label_24; // string
      }break;
      case 0x0a:
      {
        if ((!HasFlag(state.flags_ZF0, 0x2))){
          {
            Token token = {};
            token.pos = (i64)(state.emit_ptr - state.base);
            token.size = (i64)(state.ptr - state.emit_ptr);
            do{
              token.sub_kind = TokenOdinKind_LexError;
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
        }
        state.ptr += 1;
        goto state_label_24; // string
      }break;
      case 0x22:
      {
        if ((!HasFlag(state.flags_ZF0, 0x2) && !HasFlag(state.flags_ZF0, 0x1))){
          state.ptr += 1;
          {
            Token token = {};
            token.pos = (i64)(state.emit_ptr - state.base);
            token.size = (i64)(state.ptr - state.emit_ptr);
            do{
              token.sub_kind = TokenOdinKind_LiteralString;
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
        if ((HasFlag(state.flags_ZF0, 0x2))){
          state.ptr += 1;
          goto state_label_24; // string
        }
        state.ptr += 1;
        goto state_label_24; // string
      }break;
      case 0x27:
      {
        if ((HasFlag(state.flags_ZF0, 0x1))){
          state.ptr += 1;
          {
            Token token = {};
            token.pos = (i64)(state.emit_ptr - state.base);
            token.size = (i64)(state.ptr - state.emit_ptr);
            do{
              token.sub_kind = TokenOdinKind_LiteralCharacter;
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
        goto state_label_24; // string
      }break;
      case 0x5c:
      {
        state.ptr += 1;
        goto state_label_25; // string_esc
      }break;
      case 0x60:
      {
        if ((HasFlag(state.flags_ZF0, 0x2))){
          state.ptr += 1;
          {
            Token token = {};
            token.pos = (i64)(state.emit_ptr - state.base);
            token.size = (i64)(state.ptr - state.emit_ptr);
            do{
              token.sub_kind = TokenOdinKind_LiteralStringRaw;
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
        goto state_label_24; // string
      }break;
    }
  }
  {
    state_label_25: // string_esc
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LexError;
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
          do{
            token.sub_kind = TokenOdinKind_EOF;
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
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        goto state_label_27; // string_esc_oct2
      }break;
      case 0x55:
      {
        state.ptr += 1;
        goto state_label_29; // string_esc_universal_8
      }break;
      case 0x75:
      {
        state.ptr += 1;
        goto state_label_33; // string_esc_universal_4
      }break;
      case 0x78:
      {
        state.ptr += 1;
        goto state_label_26; // string_esc_hex
      }break;
    }
  }
  {
    state_label_26: // string_esc_hex
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_26; // string_esc_hex
      }break;
    }
  }
  {
    state_label_27: // string_esc_oct2
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        goto state_label_28; // string_esc_oct1
      }break;
    }
  }
  {
    state_label_28: // string_esc_oct1
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:
      {
        state.ptr += 1;
        goto state_label_24; // string
      }break;
    }
  }
  {
    state_label_29: // string_esc_universal_8
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_30; // string_esc_universal_7
      }break;
    }
  }
  {
    state_label_30: // string_esc_universal_7
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_31; // string_esc_universal_6
      }break;
    }
  }
  {
    state_label_31: // string_esc_universal_6
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_32; // string_esc_universal_5
      }break;
    }
  }
  {
    state_label_32: // string_esc_universal_5
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_33; // string_esc_universal_4
      }break;
    }
  }
  {
    state_label_33: // string_esc_universal_4
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_34; // string_esc_universal_3
      }break;
    }
  }
  {
    state_label_34: // string_esc_universal_3
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_35; // string_esc_universal_2
      }break;
    }
  }
  {
    state_label_35: // string_esc_universal_2
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_36; // string_esc_universal_1
      }break;
    }
  }
  {
    state_label_36: // string_esc_universal_1
    if (state.ptr == state.opl_ptr){
      if ((true)){
        goto state_label_24; // string
      }
    }
    switch (*state.ptr){
      default:
      {
        goto state_label_24; // string
      }break;
      case 0x30:case 0x31:case 0x32:case 0x33:case 0x34:case 0x35:case 0x36:
      case 0x37:case 0x38:case 0x39:case 0x41:case 0x42:case 0x43:case 0x44:
      case 0x45:case 0x46:case 0x61:case 0x62:case 0x63:case 0x64:case 0x65:
      case 0x66:
      {
        state.ptr += 1;
        goto state_label_24; // string
      }break;
    }
  }
  {
    state_label_37: // comment_block
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_MultiComment;
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
          do{
            token.sub_kind = TokenOdinKind_EOF;
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
        goto state_label_37; // comment_block
      }break;
      case 0x2a:
      {
        state.ptr += 1;

        if (state.ptr != state.opl_ptr && *state.ptr == '/' && --state.counter != 0){
          goto state_label_37; // comment_block
        }

        goto state_label_39; // comment_block_try_close
      }break;
      case 0x2f:
      {
        state.ptr += 1;
        goto state_label_38; // comment_block_try_open
      }break;
    }
  }
  {
    state_label_38: // comment_block_try_open
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
        goto state_label_37; // comment_block
      }break;
      case 0x2a:
      {
        state.ptr += 1;
        state.counter += 1;
        goto state_label_37; // comment_block
      }break;
    }
  }
  {
    state_label_39: // comment_block_try_close
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_MultiComment;
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
          do{
            token.sub_kind = TokenOdinKind_EOF;
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
        goto state_label_37; // comment_block
      }break;
      case 0x2a:
      {
        state.ptr += 1;

        if (state.ptr != state.opl_ptr && *state.ptr == '/' && --state.counter != 0){
          goto state_label_37; // comment_block
        }

        goto state_label_39; // comment_block_try_close
      }break;
      case 0x2f:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_MultiComment;
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
    state_label_40: // comment_line
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LineComment;
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
        goto state_label_40; // comment_line
      }break;
      case 0x0a:
      {
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LineComment;
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
        goto state_label_41; // comment_line_backslashing
      }break;
    }
  }
  {
    state_label_41: // comment_line_backslashing
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
        goto state_label_40; // comment_line
      }break;
      case 0x0d:
      {
        state.ptr += 1;
        goto state_label_41; // comment_line_backslashing
      }break;
    }
  }
  {
    state_label_42: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Minus;
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
          do{
            token.sub_kind = TokenOdinKind_Minus;
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
        goto state_label_45; // op stage
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_MinusEq;
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
          do{
            token.sub_kind = TokenOdinKind_Arrow;
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
    state_label_43: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_And;
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
          do{
            token.sub_kind = TokenOdinKind_And;
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
        goto state_label_58; // op stage
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_AndEq;
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
      case 0x7e:
      {
        state.ptr += 1;
        goto state_label_54; // op stage
      }break;
    }
  }
  {
    state_label_44: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Mod;
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
          do{
            token.sub_kind = TokenOdinKind_Mod;
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
      case 0x25:
      {
        state.ptr += 1;
        goto state_label_53; // op stage
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_ModEq;
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
    state_label_45: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Dec;
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
          do{
            token.sub_kind = TokenOdinKind_Dec;
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
          do{
            token.sub_kind = TokenOdinKind_Undef;
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
    state_label_46: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Less;
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
          do{
            token.sub_kind = TokenOdinKind_Less;
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
        goto state_label_56; // op stage
      }break;
      case 0x3d:
      {
        state.ptr += 1;
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_LessEq;
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
    state_label_47: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Grtr;
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
          do{
            token.sub_kind = TokenOdinKind_Grtr;
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
          do{
            token.sub_kind = TokenOdinKind_GrtrEq;
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
        goto state_label_57; // op stage
      }break;
    }
  }
  {
    state_label_48: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Eq;
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
          do{
            token.sub_kind = TokenOdinKind_Eq;
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
          do{
            token.sub_kind = TokenOdinKind_EqEq;
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
    state_label_49: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Not;
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
          do{
            token.sub_kind = TokenOdinKind_Not;
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
          do{
            token.sub_kind = TokenOdinKind_NotEq;
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
    state_label_50: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Or;
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
          do{
            token.sub_kind = TokenOdinKind_Or;
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
          do{
            token.sub_kind = TokenOdinKind_OrEq;
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
        goto state_label_59; // op stage
      }break;
    }
  }
  {
    state_label_51: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Plus;
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
          do{
            token.sub_kind = TokenOdinKind_Plus;
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
          do{
            token.sub_kind = TokenOdinKind_Inc;
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
          do{
            token.sub_kind = TokenOdinKind_PlusEq;
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
    state_label_52: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Star;
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
          do{
            token.sub_kind = TokenOdinKind_Star;
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
          do{
            token.sub_kind = TokenOdinKind_StarEq;
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
    state_label_53: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_ModMod;
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
          do{
            token.sub_kind = TokenOdinKind_ModMod;
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
          do{
            token.sub_kind = TokenOdinKind_ModModEq;
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
          do{
            token.sub_kind = TokenOdinKind_AndNot;
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
          do{
            token.sub_kind = TokenOdinKind_AndNot;
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
          do{
            token.sub_kind = TokenOdinKind_AndNotEq;
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
          do{
            token.sub_kind = TokenOdinKind_Xor;
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
          do{
            token.sub_kind = TokenOdinKind_Xor;
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
          do{
            token.sub_kind = TokenOdinKind_XorEq;
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
    state_label_56: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_Shl;
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
          do{
            token.sub_kind = TokenOdinKind_Shl;
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
          do{
            token.sub_kind = TokenOdinKind_LessLessEq;
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
          do{
            token.sub_kind = TokenOdinKind_Shr;
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
          do{
            token.sub_kind = TokenOdinKind_Shr;
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
          do{
            token.sub_kind = TokenOdinKind_GrtrGrtrEq;
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
    state_label_58: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_AndAnd;
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
          do{
            token.sub_kind = TokenOdinKind_AndAnd;
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
          do{
            token.sub_kind = TokenOdinKind_AndAndEq;
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
    state_label_59: // op stage
    if (state.ptr == state.opl_ptr){
      if ((true)){
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_OrOr;
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
          do{
            token.sub_kind = TokenOdinKind_OrOr;
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
          do{
            token.sub_kind = TokenOdinKind_OrOrEq;
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
          do{
            token.sub_kind = TokenOdinKind_Variadic;
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
          do{
            token.sub_kind = TokenOdinKind_Variadic;
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
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_RangeHalf;
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
          do{
            token.sub_kind = TokenOdinKind_RangeFull;
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
          do{
            token.sub_kind = TokenOdinKind_Variadic;
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
          do{
            token.sub_kind = TokenOdinKind_Variadic;
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
        {
          Token token = {};
          token.pos = (i64)(state.emit_ptr - state.base);
          token.size = (i64)(state.ptr - state.emit_ptr);
          do{
            token.sub_kind = TokenOdinKind_RangeHalf;
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
          do{
            token.sub_kind = TokenOdinKind_RangeFull;
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
lex_full_input_odin(Arena *arena, String_Const_u8 input){
  Lex_State_Odin state = {};
  lex_full_input_odin_init(&state, input);
  Token_List list = {};
  lex_full_input_odin_breaks(arena, &list, &state, max_u64);
  return(list);
}
