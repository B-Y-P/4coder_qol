@echo off
set /A comp_fail = 0
call custom\bin\build_one_time.bat .\4coder_qol_cpp_lexer_gen.cpp ..\ %1 && ..\one_time.exe  || set /A comp_fail=1
call custom\bin\build_one_time.bat .\4coder_qol_odin_lexer_gen.cpp ..\ %1  && ..\one_time.exe  || set /A comp_fail=2

if %comp_fail% EQU 0 (echo Lexers Generated)
if %comp_fail% EQU 1 (echo cpp lexer failed to gen)
if %comp_fail% EQU 2 (echo odin lexer failed to gen)

del ..\4coder_qol_cpp_lexer_gen.obj
del ..\one_time.*
