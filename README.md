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
- [05 - code index syntax highlighting](#c05)
- [06 - home scrolls view left](#c06)
- [07 - scroll margins](#c99)   -- TODO update numbers
- [07 - hot reload themes](#c07)
- [08 - interpolate theme](#c08)
- [09 - hot reload config.4coder](#c09)
- [10 - hot reload project.4coder](#c10)
- [11 - comp errors for theme reloads](#c11)
- [12 - hot reload bindings.4coder](#c12)
- [13 - reloading helpers](#c13)
- [14 - file explorer command](#c14)
- [15 - modal auto-complete {} on enter](#c15)
- [16 - bump column edit spaces](#c16)
- [17 - block functions and scope highlights](#c17)
- [18 - custom lexer generator](#c18)
- [19 - custom cpp token kinds](#c19)
- [20 - enums are parsed and indexed](#c20)
- [21 - move selected line ranges up/down](#c21)
- [22 - example kill-rectangle](#c22)
- [23 - draw comment divider lines](#c23)
- [24 - divider movements](#c24)
- [25 - draw hovered token underlines](#c25)
- [26 - paint @annotations in comments](#c26)
- [27 - scope end annotations](#c27)
- [28 - compiler error annotations](#c28)
- [29 - function peek tooltip](#c29)
- [30 - ctrl-movements](#c30)

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

### 05 - code index syntax highlighting <a name="c05"/>
Now we can get a better sense for the themes colors, but there was a conspicuous block of code `#if 0`'d out\
Enabling it demonstrates `CodeIndexNote_Function` syntax-highlighting from 4coder's code index\
Looing at `Code_Index_Note_Kind` we can see we also have `CodeIndexNote_Type` and `CodeIndexNote_Macro` as well

Seems like a perfectly reasonable thing to make customizable by users\
We'll declare them using `CUSTOM_ID(colors, ...)` which allows 4coder's metadata generator to see them\
Now we can use those in our theme the same as all the other colors

</br>

### 06 - home scrolls view left <a name="c06"/>
Now on to some quality of life features\
4coder by default only scrolls to keep the cursor in view\
This is fine vertically, but when I hit the `<home>` key I want to scroll all the way back

Same idea for the metadata generator when using `CUSTOM_COMMAND_SIG` and `CUSTOM_DOC`\
We can add our `qol_home` command to our `bindings.4coder`\
In case the user is missing this file, we can provide `qol_setup_default_mapping` at init

</br>

### 07 - scroll margins <a name="c99"/>
While the default behavior of scrolling once the cursor goes out of view is fine,\
it's common to allow the user to define some margin to start scrolling sooner\
So we'll add `scroll_margin_x` and `scroll_margin_y` in 'char-count' and 'line-count' resp.

</br>

### 07 - hot reload themes <a name="c07"/>
Okay, so we have these text files we parse at runtime (`config.4coder`, `theme-<theme_name>.4coder`, `bindings.4coder` etc.)\
But we haven't made it all that much easier to reload them at runtime\
So let's add a hook on file save, and if it's one of our themes, update our table

</br>

### 08 - interpolate theme <a name="c08"/>
Taking this one step further, we'll apply the same idea for [interpolate cursors](#c03) only with more data\
It'd be convenient to have a place to initialize the `cur_` and `nxt_` color table data, so we'll add `qol_startup`\
Now we also have the added caveat that anyone can modify the table out from under us,\
so we'll detect and intercept that on tick as well\
Lastly, we can simplify our theme reloading now that we have a simpler way to re-target a parsed theme

</br>

### 09 - hot reload config.4coder <a name="c09"/>
Now that we can [hot reload](#c07) our files, let's start applying it across the board\
This time with `config.4coder` files. This time our call to `load_config_and_apply` uses C's `FILE*` API\
This raises an issue as `qol_file_save` is called before the save is flushed\
So instead of directly calling `qol_reload_config`, we'll use `view_enqueue_command_function`

Unlike themes, it's much easier to hit a syntax error in the config files so let's look to resolve that\
First, we include `.4coder` in the list of file extensions we parse and syntax highlight as C-like\
Then we can re-use the way 4coder highlights compiler errors by adjusting the config error format to match\
Now by outputting those errors to the `*compilation*` buffer, they'll show us exactly where the parser choked

This also changes the default behavior to use the full path and avoid double-slashes e.g. `C:/4coder//config.4coder`

</br>

### 10 - hot reload project.4coder <a name="c10"/>
Continuing the trend, let's repeat for `project.4coder` files\
Since this is becoming a pattern, we can hoist `comp_error` as a function to re-use here\
We now find ourselves with the issue that by default, `load_project` does project parsing *and* directory loading\
By splitting these, we can keep simply reparse on file-save

</br>

### 11 - comp errors for theme reloads <a name="c11"/>
While `project.4coder` and `config.4coder` both got to make use of `comp_error` our theme parsing doesn't\
So we'll quickly update our call to send a `comp_error` and be on our way

</br>

### 12 - hot reload bindings.4coder <a name="c12"/>
You're not gonna *believe* what happens next...

</br>

### 13 - reloading helpers <a name="c13"/>
If, *hypothetically*, someone had to frequently `git rebase`, 4coder would find a lot of externally modified files\
Let's expedite the process a bit. We won't give keybinds here, since they're much *heftier* than the average command

</br>

### 14 - file explorer command <a name="c14"/>
I just wanted a faster way to open explorer in the current directory from 4coder... moving along

</br>

### 15 - modal auto-complete {} on enter <a name="c15"/>
Standard text editor stuff, but there's a slight catch if we're not careful\
Default behavior of enter will insert a `\n` when unhandled,\
but if in a jump buffer, it gets handled when taking the jump for the  current line

So first we try to get a buffer using `Access_ReadWriteVisible` and if it fails, it might be `Access_ReadVisible`\
This let's us forward the behavior back to `goto_jump_at_cursor`\
Otherwise, we'll do the standard close-brace insert when necessary

</br>

### 16 - bump column edit spaces <a name="c16"/>
Common thing I automate when using APIs that frequently fill out structs is to align the `=` chars\
This lets me place the cursor on the right-most char, place a column\
Then while holding shift, repeat `↑ ← <Space>` as necessary

Also serves the double purpose of allowing me to place a vertical visual guide

</br>

### 17 - block functions and scope highlights <a name="c17"/>
Interestingly, the implementation for scope highlights came from writing Visual Block Mode in [4coder_vim](https://github.com/B-Y-P/4coder_vim)\
If you were to `text_layout_character_on_screen` the `{` and `}`, it would only work when both are on screen\
But you can get around this using `view_relative_xy_of_pos` and `view_pos_at_relative_xy`\
Graphics intuition of "do this in model space, rather than screen space"

Since I already had the code lying around, I included the methods for iterating the line ranges of a block selection\
Maybe there will be a *future commit* which will have a use for them... ;)

</br>

### 18 - custom lexer generator <a name="c18"/>
Oh boy, time to bring in the [4coder lexer](https://www.youtube.com/watch?v=Jw9kJKuh-RU)\
For now, we'll just move some keywords around like `NULL` and `nullptr` and get it building\
For this to take effect, you need to run `build_lexer.bat` before running `build.bat`

If I don't end up going into more detail later, I'll revise this description\
For now, the tl;dr is "It's a DFA which is explicit on token emit, and has helpers for keywords and op-sets"

</br>

### 19 - custom cpp token kinds <a name="c19"/>
Now that we can change how tokens get emmitted, we can also add the kinds of tokens we emit\
So we can syntax highlight control flow, primitive types, and structural tokens differently

</br>

### 20 - enums are parsed and indexed <a name="c20"/>
Alright, enough lexing for now. Instead, we can start parsing\
Where lexing processed a stream of characters to produce tokens,\
our parser processes a stream of tokens, and indexes tokens of interest\

For our case, enum values are particularly helpful to index, since they often represent different options\
So if a function is being passed an enum, jump to definition to switch to a different enum value is invaluable

</br>

### 21 - move selected line ranges up/down <a name="c21"/>
This ones another quality of life feature which isn't a game changer, but nice to have

</br>

### 22 - example kill-rectangle <a name="c22"/>
The thing about [`qol_block_delete`](#c17) is that it's unclear exactly what's going to happen when you call it\
So let's provide a visual indication, and prompt the user to decide Yes or No

This moreso serves as a minimal but non-trivial example of what you can do with 4coder's View context\
We can see that we can override the View's render function, but internally we can still call whatever render hook was internally\
This let's us draw overtop of our rendered Views without adding code specifically to *our* main render_caller\
This means that someone could add their own hooks, and call our function and the behavior would be consistent

Finally, if take a closer look at the control flow implications of `qol_kill_rectangle`\
We'll notice that it's doing a spin-loop on user input, but when we ran it, the other views still rendered and updated just fine\
This is because `get_next_input` acts as a coroutine, allowing us the illusion of writing synchronous code without fully blocking

</br>

### 23 - draw comment divider lines <a name="c23"/>
Just a nice and simple change to help visualy 'slice' the code into sections without having to spam `///`'s

</br>

### 24 - divider movements <a name="c24"/>
Okay, but now that I can *see* the section I want to jump to\
I'd like to... y'know, actually *jump* to it now

</br>

### 25 - draw hovered token underlines <a name="c25"/>
Helps provide a more passive visual for "where else is this being used?"\
Without having to forcibly substring search and fill your view with highlights

</br>

### 26 - paint @annotations in comments <a name="c26"/>
We have code to iterate over comment tokens, so it's easy enough add a scan for '@'

</br>

### 27 - scope end annotations <a name="c27"/>
I mentioned that [scopes off screen](#c17) posed a challenge to implementing features,\
but they're also problematic to come across as a user

If you don't know *what* scope you're currently at the end of, you'll have to double check\
And to double check, you have to go all the way up, just to go right back down\
Let's just have the editor *tell* you

</br>

### 28 - compiler error annotations <a name="c28"/>
Let's take 4coder's jump to error and use it to render *where* and *what* those errors are\
so we can minimize the amount of neck-craning it takes when moving between code and terminal

There's some interesting behavior with how 4coder stores per-buffer pos and line numbers of errors\
By making a bit of an intrusive change which relies on reclaiming some otherwise unused padding,\
we can avoid a lot of redundant work when drawing each individual error message

</br>

### 29 - function peek tooltip <a name="c29"/>
Same idea as before where instead you're currently typing function parameters\
You'd rather not context switch by jumping to definition, double checking the type, and jumping back\
So let's just show you the definition, as you type

</br>

### 30 - ctrl-movements <a name="c30"/>
Default behavior for ctrl-backspace and similar ctrl-movements is *slightly* different from other text editors


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


