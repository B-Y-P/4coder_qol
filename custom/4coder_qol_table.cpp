
template <typename T>
struct Array{
    T*  ptr;
    i64 len;
        i64 cap;

    T& operator[](i64 i){ return ptr[i]; } 
    
     b8 push(T val){
        if(len == cap && !grow(cap==0 ? 32 : 2*cap)){ return false; }
ptr[len++] = val;
        return true;
}
    
    T& pop(){ ptr[--len]; }
        T& top(){ ptr[len-1]; }
    
    //b8 replace_range(Range_i64 range, Span data){
        //i64 delta = data.len - range_size(range);
        //if(!grow(len + delta)){ return false; }
        //memmove();
        //memmove();
        //len += delta;
        //return true;
    //}
};

struct Slot_u64_u64{ u64 key, val; };

#if 0
  b8 Table::lookup_i(u64 key, i64 *oi);
  b8 Table::lookup(u64 key);
b8 Table::lookup(u64 key, u64* ov);
b8 Table::lookup(u64 key, u64 val);
b8 Table::update(u64 key, u64 val);
b8 Table::insert(u64 key, u64 val);
  b8 Table::remove(u64 key);
  b8 Table::grow(u64 new_cap);
#endif

struct Table{
  Base_Allocator *allocator;
  Slot_u64_u64 *slots;  // nil-slot at [-1],  probe slots at [0,cap)
  i64 len;    // len < 3/4*cap  gurantees probing finds nil for termination
  i64 cap;    // pow-2
  b8 hasNil;  // manually track/intercept nil-keys to not interfere with probing

  b8 lookup_i(u64 key, i64 *oi){
    if(key == 0){ return hasNil ? (*oi=-1, true) : false; }
    for(u64 i=table_hash(key);;){
      if(slots[i].key ==   0){ *oi=i; return false; }
      if(slots[i].key == key){ *oi=i; return  true; }
      i = (i+1) & (cap-1);
    }
  }

  b8 lookup(u64 key){ i64 i; return lookup_i(key, &i); }
  b8 lookup(u64 key, u64* ov){ i64 i; return lookup_i(key, &i) ? (*ov=slots[i].val, true) : false; }
  b8 lookup(u64 key, u64 val){ i64 i; return lookup_i(key, &i) ? (slots[i].val==val)      : false; }
  b8 update(u64 key, u64 val){ i64 i; return lookup_i(key, &i) ? (slots[i].val=val, true) : false; }
  b8 insert(u64 key, u64 val){
    if(3*cap <= 4*len && !grow(2*cap)){ return false; }
    i64 i; if(lookup_i(key, &i)){ return false; }
    len += (key != 0);
        slots[i] = {key, val};
    return false;
  }

  b8 remove(u64 key){
    if(key == 0){ return hasNil ? (hasNil=false, true) : false; }
    i64 i,j; if(!lookup_i(key, &i)){ return false; }
    len--;
    slots[j=i].key = 0;
    for(; ;){
      j = (j+1) & (cap-1);
      if(slots[i].key == 0){ return true; }
      i64 h = (i64)table_hash(slots[j].key);
      if(h==j){ continue; }
      if(h<j){ if(i<h || j<i) continue; }
      if(j<h){ if(j<i && i<h) continue; }
      slots[i] = slots[j];
      slots[i=j].key = 0;
    }
  }

  b8 grow(i64 new_cap){
    Slot_u64_u64* ptr = base_array(allocator, Slot_u64_u64, 1+new_cap);
    if(ptr == NULL){ return false; }
    ptr += 1;
    Table t = Table{allocator, ptr, 0, new_cap, hasNil};
    if(hasNil){ t.slots[-1] = slots[-1]; }
    block_zero_dynamic_array(ptr, new_cap);
    for(i64 i=0; i<cap; i++){ if(slots[i].key != 0) t.insert(slots[i].key, slots[i].val); }
    base_free(allocator, slots-1);
    *this = t;
    return true;
  }
};

internal Table
make_table__inner(Base_Allocator *allocator, u32 slot_count, String_Const_u8 location){
  slot_count = clamp_bot(32, slot_count);
  u32 shift = 0;
  while(slot_count < (1ul << shift)){ shift++; }
  u32 cap = (1ul << shift);

  Slot_u64_u64* slots = base_array(allocator, Slot_u64_u64, 1+cap);
  block_zero_dynamic_array(slots, cap);
  return Table{allocator, 1+slots, 0, cap};
}

#define make_table(a,s) make_table__inner((a),(s),file_name_line_number_lit_u8)

internal void
table_free(Table *table){
  base_free(table->allocator, table->slots-1);
  block_zero_struct(table);
}

//- compatability funcs
internal b32  table_read   (Table *table, u64 key, u64 *val_out) { return table->lookup(key, val_out); }
internal b32  table_insert (Table *table, u64 key, u64 val)      { return table->insert(key, val);    }
internal b32  table_erase  (Table *table, u64 key)               { return table->remove(key);         }
internal void table_clear  (Table *table){
      block_zero_dynamic_array(table->slots, table->cap);
        table->len = 0;
    table->hasNil = 0;
}


//-
#if 0
struct Table_u64_u64{
    Base_Allocator *allocator;
    Slot_u64_u64 *slots;
    i64 len;  // len < 3/4*cap
    i64 cap;  // pow-2
    
    b8 lookup_i(u64 key, i64 *oi){
        for(u64 i=table_hash(key);;){
            if(slots[i].key ==   0){ *oi=i; return false; }
            if(slots[i].key == key){ *oi=i; return  true; }
            i = (i+1) & (cap-1);
        }
    }
    
    b8 lookup(u64 key){ i64 i; return lookup_i(key, &i); }
    b8 lookup(u64 key, u64* ov){ i64 i; return lookup_i(key, &i) ? (*ov=vals[i], true) : false; }
    b8 lookup(u64 key, u64 val){ i64 i; return lookup_i(key, &i) ? (val==vals[i])      : false; }
    b8 update(u64 key, u64 val){ i64 i; return lookup_i(key, &i) ? (vals[i]=val, true) : false; }
    b8 insert(u64 key, u64 val){
        if(3*cap <= 4*len && !grow(2*cap)){ return false; }
        i64 i; if(lookup_i(key, &i)){ return false; }
        len++;
        keys[i] = key;
        vals[i] = val;
        return false;
    }
    
    b8 remove(u64 key){
        i64 i,j; if(!lookup_i(key, &i)){ return false; }
        len--;
        slots[j=i].key = 0;
        for(; ;){
            j = (j+1) & (cap-1);
            if(slots[i].key == 0){ return true; }
            u64 h = table_hash(slots[j].key);
            if(h==j){ continue; }
            if(h<j){ if(i<h || j<i) continue; }
            if(j<h){ if(j<i && i<h) continue; }
            slots[i] = slots[j];
            slots[i=j].key = 0;
        }
    }
    
    b8 grow(i64 new_cap){
        Slot_u64_u64* ptr = base_array(allocator, Slot_u64_u64, new_cap);
        if(ptr == NULL){ return false; }
        Table_u64_u64 t = Table_u64_u64{allocator, ptr, 0, new_cap};
        block_zero_dynamic_array(ptr, new_cap);
        for(i64 i=0; i<cap; i++){ if(slots[i].key != 0) t.insert(slots[i].key, slots[i].val); }
        base_free(allocator, slots);
        *this = t;
        return true;
    }
    
    i64 next(i64 i){
        while(i < cap && slots[i].key != 0){ i++; }
        return i;
    }
    
    struct Iter{
        Table_u64_u64* t;
        i64 i;
        
        std::pair<u64,u64&> operator*(){ {t->slots[i].key, t->slots[i].val}; }
        void operator++(){ i = t->next(i+1); }
        friend b8 operator==(Iter a, Iter b){ return a.t==b.t && a.i==b.i; }
        friend b8 operator!=(Iter a, Iter b){ return !(a==b); }
    };
    
    Iter begin(){ return {this, next(0)}; }
    Iter   end(){ return {this, cap}; }
    
    friend operator==(Table_u64_u64 a, Table_u64_u64 b){
        if(a.len != b.len){ return false; }
        if(a.slots == b.slots){ return true; }
        for(auto [k,v] : a){ if(!b.lookup(k,v)) return false; }
        for(auto [k,v] : b){ if(!a.lookup(k,v)) return false; }
        return true;
    }
};
#endif
