@echo off
call "N:\Visual Studio\VC\Auxiliary\Build\vcvarsall.bat" x86
call ..\..\Debug\AVD-2022.exe -in:in.txt -out:..\out.asm 
ml /c /coff /asm.lst ..\AVD-AsmLib\AVD-AsmLib\out.asm
link /OPT:NOREF /DEBUG ..\AVD-AsmLib\Debug\StaticLib.lib out.obj  /SUBSYSTEM:CONSOLE libucrt.lib
call out.exe
pause