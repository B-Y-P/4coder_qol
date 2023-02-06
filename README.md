# 4coder_qol [![badge](https://github.com/B-Y-P/4coder_qol/actions/workflows/main.yml/badge.svg)](https://github.com/B-Y-P/4coder_qol/releases/)
Quality of Life custom layer for [4coder](https://mr-4th.itch.io/4coder)

`cd \path\to\4ed.exe`\
`git clone https://github.com/B-Y-P/4coder_qol.git`\
`cd 4coder_qol`\
`build release`

### Still WIP

---

### Table of Contents
- [PRE - Some cleaning up before properly starting](#pre)
- [00 - add custom render hook                    ](#c00)

---

### 00 - add custom render hook <a name="c00"/>
Starting simple by merely replacing the render hook with a copy-pasted version of our own

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
