# 4coder_qol
Quality of Life custom layer for [4coder](https://mr-4th.itch.io/4coder)

`cd \path\to\4ed.exe`\
`git clone https://github.com/B-Y-P/4coder_qol.git`\
`cd 4coder_qol`\
`build release`

---

### Table of Contents
- [PRE - Some cleaning up before properly starting](#pre)
- [00 - add custom render hook](#c00)
- [01 - bottom filebars](#c01)
- [02 - config determines filebar position](#c02)
- [03 - interpolate cursor](#c03)
- [04 - hex colors](#c04)

---

</br>

### 00 - add custom render hook <a name="c00"/>
Starting simple by merely replacing the render hook with a copy-pasted version of our own

</br>

### 01 - bottom filebars <a name="c01"/>
Now that we can customize our rendering\
Changing `layout_file_bar_on_top` -> `layout_file_bar_on_bot` is straight-forward enough,\
but if you left it there, you'd get some very different results

The takeaway here would be that 4coder uses a "y-is-down" convention\
Meaning y-values increase the further down the screen you go\
So when splitting a rectangle into a top and bottom pair,\
the `pair.min` will be the top, and `pair.max` will be the bottom

The next thing to do is modify the `buffer_region` hook accordingly\
This keeps the rest of the code up-to-date on what region of the view is dedicated to text\
Now existing code which calls `view_get_buffer_region` is kept correct after our customizations

</br>

### 02 - config determines filebar position <a name="c02"/>
Okay sure, we can change where the filebar gets positioned, but to do so requires closing and recompiling the editor\
Not exactly the best user experience, so let's at least do away with the requirement of recompiling the code

The convenient thing about the config.4coder file is that you can declare your own keywords\
It also helps that this is just a text file which we can load (and reload) whenever we like

</br>

### 03 - interpolate cursor <a name="c03"/>
Now let's get a little fancier. Sure the scrolling is smooth, but the cursor teleports with no temporal coherency\
By tracking a `qol_cur_cursor_pos` and  `qol_nxt_cursor_pos` (sorry, not sorry for the naming convention :P)\
we can make use of [lerp smoothing](https://www.youtube.com/watch?v=LSNQuFEDOyQ)

Now it's `qol_nxt_cursor_pos` which logically 'teleports', while `qol_cur_cursor_pos` smoothly interpolates towards it\
If that's all we did, our cursor won't always finish interpolating\
This is because 4coder by default doesn't update every frame\
When the app is idle, it shouldn't drain your battery. It only updates when necessary

We can inform 4coder we still need updates by calling `animate_in_n_milliseconds` as necessary\
We'll do this whenever the cursor is still more than half a pixel away from it's target\
Now we can always finish our animation, but still idle as needed

</br>

### 04 - hex colors <a name="c04"/>
You'll most likely want to change the theme colors, but opening them in 4coder isn't going to help you much\
Here's  where we'll start getting a bit more involved. The goal is to draw a colored rect around hex-literals\
We can avoid processing the entire file every frame by limiting ourselves to `text_layout_get_visible_range`\
Once we've found a hex-literal, we can call `string_to_integer` with base=16 to get an `ARGB_Color` value

At this point, we could draw our rectangle and be done, but we often get white text overtop light colors\
To prevent this, we can determine whether the `ARGB_Color` is on 'lighter' or 'darker'\
This lets us pick either black or white to contrast accordingly\
*Note: 4coder does have `rgba_to_hsla` but I must've felt like twiddling bits when I made this commit :)*

One thing you might notice is calling `paint_text_color` before drawing the rectangles doesn't change the result\
The color of the text is associated with the text layout drawn later on in `draw_text_layout_default`

</br>

---

</br>

### PRE <a name="pre"/>

### [stb_sprintf](https://github.com/nothings/stb/blob/master/stb_sprintf.h) gives us a couple benefits:
- performance speedup
- cross-platform `%lld` for `int64_t`
- add `%S` for 4coder `String_Const_u8`

### fix config file add float rvalues
- typo in config file `s/use_comment_keywords/use_comment_keyword`
- floats allow users to better modify UI at runtime (no need to close and re-compile)

### decouple lister fill from lister run
- this will come in handy waaaay later down the line


