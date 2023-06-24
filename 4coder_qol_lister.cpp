
function void
qol_lister_render(Application_Links *app, Frame_Info frame_info, View_ID view){
  Scratch_Block scratch(app);

  Lister *lister = view_get_lister(app, view);
  if (lister == 0){ return; }
  Rect_f32 region = draw_background_and_margin(app, view);
  Rect_f32 prev_clip = draw_set_clip(app, region);
  b32 is_active_view = (view == get_active_view(app, Access_Always));

  Face_ID face_id = get_face_id(app, 0);
  Face_Metrics metrics = get_face_metrics(app, face_id);
  f32 line_height = metrics.line_height;
  f32 block_height = lister_get_block_height(line_height);
  f32 text_field_height = lister_get_text_field_height(line_height) + 2.f;

  // NOTE(allen): file bar
  // TODO(allen): What's going on with 'showing_file_bar'? I found it like this.
  b64 showing_file_bar = false;
  b32 hide_file_bar_in_ui = def_get_config_b32(vars_save_string_lit("hide_file_bar_in_ui"));
  if (view_get_setting(app, view, ViewSetting_ShowFileBar, &showing_file_bar) &&
      showing_file_bar && !hide_file_bar_in_ui){
    Rect_f32_Pair pair = layout_file_bar_on_bot(region, line_height);
    Buffer_ID buffer = view_get_buffer(app, view, Access_Always);
    draw_file_bar(app, view, buffer, face_id, pair.max);
    region = pair.min;
  }

  Mouse_State mouse = get_mouse_state(app);
  Vec2_f32 m_p = V2f32(mouse.p);
  Vec2_f32 cursor_pos = {};

  lister->visible_count = (i32)((rect_height(region)/block_height)) - 3;
  lister->visible_count = clamp_bot(1, lister->visible_count);

  Rect_f32 text_field_rect = {};
  Rect_f32 list_rect = {};
  {
    Rect_f32_Pair pair = rect_split_top_bottom_neg(region, text_field_height);
    text_field_rect = pair.max;
    list_rect = pair.min;
  }

  {
    Vec2_f32 p = V2f32(text_field_rect.x0 + 3.f, text_field_rect.y0);
    Fancy_Line text_field = {};
    push_fancy_string(scratch, &text_field, fcolor_id(defcolor_pop1), lister->query.string);
    push_fancy_stringf(scratch, &text_field, " ");
    p = draw_fancy_line(app, face_id, fcolor_zero(), &text_field, p);

    // TODO(allen): This is a bit of a hack. Maybe an upgrade to fancy to focus
    // more on being good at this and less on overriding everything 10 ways to sunday
    // would be good.
    block_zero_struct(&text_field);
    push_fancy_string(scratch, &text_field, fcolor_id(defcolor_text_default),
                      lister->text_field.string);
    f32 width = get_fancy_line_width(app, face_id, &text_field);
    f32 cap_width = text_field_rect.x1 - p.x - 6.f;
    if (cap_width < width){
      Rect_f32 prect = draw_set_clip(app, Rf32(p.x, text_field_rect.y0, p.x + cap_width, text_field_rect.y1));
      p.x += cap_width - width;
      cursor_pos = draw_fancy_line(app, face_id, fcolor_zero(), &text_field, p);
      draw_set_clip(app, prect);
    }
    else{
      cursor_pos = draw_fancy_line(app, face_id, fcolor_zero(), &text_field, p);
    }
    if (is_active_view){
      qol_nxt_cursor_pos = cursor_pos;
    }
  }


  Range_f32 x = rect_range_x(list_rect);
  draw_set_clip(app, list_rect);

  // NOTE(allen): auto scroll to the item if the flag is set.
  f32 scroll_y = lister->scroll.position.y;

  if (lister->set_vertical_focus_to_item){
    lister->set_vertical_focus_to_item = false;
    Range_f32 item_y = If32_size(lister->item_index*block_height, block_height);
    f32 view_h = rect_height(list_rect);
    Range_f32 view_y = If32_size(scroll_y, view_h);
    if (view_y.min > item_y.min || item_y.max > view_y.max){
      f32 item_center = (item_y.min + item_y.max)*0.5f;
      f32 view_center = (view_y.min + view_y.max)*0.5f;
      f32 margin = view_h*.3f;
      margin = clamp_top(margin, block_height*3.f);
      if (item_center < view_center){
        lister->scroll.target.y = item_y.min - margin;
      }
      else{
        f32 target_bot = item_y.max + margin;
        lister->scroll.target.y = target_bot - view_h;
      }
    }
  }

  // NOTE(allen): clamp scroll target and position; smooth scroll rule
  i32 count = lister->filtered.count;
  Range_f32 scroll_range = If32(0.f, clamp_bot(0.f, count*block_height - block_height));
  lister->scroll.target.y = clamp_range(scroll_range, lister->scroll.target.y);
  lister->scroll.target.x = 0.f;

  Vec2_f32_Delta_Result delta = delta_apply(app, view, frame_info.animation_dt, lister->scroll);
  lister->scroll.position = delta.p;
  if (delta.still_animating){
    animate_in_n_milliseconds(app, 0);
  }

  lister->scroll.position.y = clamp_range(scroll_range, lister->scroll.position.y);
  lister->scroll.position.x = 0.f;

  scroll_y = lister->scroll.position.y;
  f32 y_pos = list_rect.y0 - scroll_y;

  i32 first_index = (i32)(scroll_y/block_height);
  y_pos += first_index*block_height;

  for (i32 i = first_index; i < count; i += 1){
    Lister_Node *node = lister->filtered.node_ptrs[i];

    if (y_pos >= region.y1){ break; }
    Range_f32 y = If32(y_pos, y_pos + block_height);
    y_pos = y.max;

    Rect_f32 item_rect = Rf32(x, y);
    Rect_f32 item_inner = rect_inner(item_rect, 3.f);

    b32 hovered = rect_contains_point(item_rect, m_p);
    UI_Highlight_Level highlight = UIHighlight_None;
    if (node == lister->highlighted_node){
      highlight = UIHighlight_Active;
    }
    else if (node->user_data == lister->hot_user_data){
      if (hovered){
        highlight = UIHighlight_Active;
      }
      else{
        highlight = UIHighlight_Hover;
      }
    }
    else if (hovered){
      highlight = UIHighlight_Hover;
    }

    u64 lister_roundness_100 = def_get_config_u64(app, vars_save_string_lit("lister_roundness"));
    f32 roundness = block_height*lister_roundness_100*0.01f;
    draw_rectangle_fcolor(app, item_rect, roundness, get_item_margin_color(highlight));
    draw_rectangle_fcolor(app, item_inner, roundness, get_item_margin_color(highlight, 1));

    Fancy_Line line = {};
    push_fancy_string(scratch, &line, fcolor_id(defcolor_text_default), node->string);
    push_fancy_stringf(scratch, &line, " ");
    push_fancy_string(scratch, &line, fcolor_id(defcolor_pop2), node->status);

    Vec2_f32 p = item_inner.p0 + V2f32(3.f, (block_height - line_height)*0.5f);
    draw_fancy_line(app, face_id, fcolor_zero(), &line, p);
  }


  {
    draw_set_clip(app, region);
    f32 line_diff = abs_f32(qol_cur_cursor_pos.y - cursor_pos.y)/line_height;
    f32 interp_t = unlerp(2.f, line_diff, 8.f);
    f32 cursor_wid = lerp(2.f, cubic_reinterpolate(clamp(0.f, interp_t, 1.f)), metrics.normal_advance);
    Rect_f32 cursor_rect = Rf32_xy_wh(qol_cur_cursor_pos, V2f32(cursor_wid, line_height));
    Rect_f32 dividor_rect = rect_split_top_bottom_neg(list_rect, 2.f).max;
    draw_rectangle_fcolor(app, cursor_rect, 0.f, fcolor_id(defcolor_cursor, 0));
    draw_rectangle_fcolor(app, dividor_rect, 0.f, get_item_margin_color(UIHighlight_Active));
  }

  draw_set_clip(app, prev_clip);
}

function Lister_Result
qol_run_lister(Application_Links *app, Lister *lister){

  lister->filter_restore_point = begin_temp(lister->arena);
  lister_update_filtered_list(app, lister);

  View_ID view = get_this_ctx_view(app, Access_Always);
  View_Context ctx = view_current_context(app, view);
  ctx.render_caller = qol_lister_render;
  ctx.hides_buffer = true;
  View_Context_Block ctx_block(app, view, &ctx);
  lister->handlers.navigate(app, view, lister, 0);

  for (;;){
    User_Input in = get_next_input(app, EventPropertyGroup_Any, EventProperty_Escape);
    if (in.abort){
      block_zero_struct(&lister->out);
      lister->out.canceled = true;
      break;
    }

    Lister_Activation_Code result = ListerActivation_Continue;
    b32 handled = true;
    switch (in.event.kind){
      case InputEventKind_TextInsert:{
        if (lister->handlers.write_character != 0){
          result = lister->handlers.write_character(app);
          lister->handlers.navigate(app, view, lister, 0);
        }
      }break;

      case InputEventKind_KeyStroke:{
        switch (in.event.key.code){
          case KeyCode_Return:
          case KeyCode_Tab:{
            void *user_data = 0;
            if (0 <= lister->raw_item_index &&
                lister->raw_item_index < lister->options.count){
              user_data = lister_get_user_data(lister, lister->raw_item_index);
            }
            lister_activate(app, lister, user_data, false);
            result = ListerActivation_Finished;
          }break;

          case KeyCode_Backspace:{
            if (lister->handlers.backspace != 0){
              lister->handlers.backspace(app);
              lister->handlers.navigate(app, view, lister, 0);
            }
            else if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;

          case KeyCode_Up:{
            if (lister->handlers.navigate != 0){
              lister->handlers.navigate(app, view, lister, -1);
            }
            else if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;

          case KeyCode_Down:{
            if (lister->handlers.navigate != 0){
              lister->handlers.navigate(app, view, lister, 1);
            }
            else if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;

          case KeyCode_PageUp:{
            if (lister->handlers.navigate != 0){
              lister->handlers.navigate(app, view, lister, -lister->visible_count);
            }
            else if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;

          case KeyCode_PageDown:{
            if (lister->handlers.navigate != 0){
              lister->handlers.navigate(app, view, lister, lister->visible_count);
            }
            else if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;

          default:{
            if (lister->handlers.key_stroke != 0){
              result = lister->handlers.key_stroke(app);
            }
            else{
              handled = false;
            }
          }break;
        }
      }break;

      case InputEventKind_MouseButton:{
        switch (in.event.mouse.code){
          case MouseCode_Left:{
            Vec2_f32 p = V2f32(in.event.mouse.p);
            void *clicked = lister_user_data_at_p(app, view, lister, p);
            lister->hot_user_data = clicked;
          }break;

          default:{ handled = false; }break;
        }
      }break;

      case InputEventKind_MouseButtonRelease:{
        switch (in.event.mouse.code){
          case MouseCode_Left:{
            if (lister->hot_user_data != 0){
              Vec2_f32 p = V2f32(in.event.mouse.p);
              void *clicked = lister_user_data_at_p(app, view, lister, p);
              if (lister->hot_user_data == clicked){
                lister_activate(app, lister, clicked, true);
                result = ListerActivation_Finished;
              }
            }
            lister->hot_user_data = 0;
          }break;

          default:{ handled = false; }break;
        }
      }break;

      case InputEventKind_MouseWheel:{
        Mouse_State mouse = get_mouse_state(app);
        lister->scroll.target.y += mouse.wheel;
        lister_update_filtered_list(app, lister);
      }break;

      case InputEventKind_MouseMove:{
        lister_update_filtered_list(app, lister);
      }break;

      case InputEventKind_Core:{
        switch (in.event.core.code){
          case CoreCode_Animate:{
            lister_update_filtered_list(app, lister);
          }break;

          default:{ handled = false; }break;
        }
      }break;

      default:{ handled = false; }break;
    }

    if (result == ListerActivation_Finished){
      break;
    }

    if (!handled){
      Mapping *mapping = lister->mapping;
      Command_Map *map = lister->map;

      Fallback_Dispatch_Result disp_result =
        fallback_command_dispatch(app, mapping, map, &in);
      if (disp_result.code == FallbackDispatch_DelayedUICall){
        call_after_ctx_shutdown(app, view, disp_result.func);
        break;
      }
      if (disp_result.code == FallbackDispatch_Unhandled){
        leave_current_input_unhandled(app);
      }
      else{
        lister_call_refresh_handler(app, lister);
      }
    }
  }

  return lister->out;
}