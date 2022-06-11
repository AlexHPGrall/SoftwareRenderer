@echo off
pushd ..\build
set CompilerFlags= -O2 -Oi -Z7 -MT -FC -GR- -EHa
set LinkerFlags= -OPT:REF -INCREMENTAL:NO user32.lib Gdi32.lib 
cl %CompilerFlags% ../code/Win32_Renderer.cpp /link %LinkerFlags%

popd
