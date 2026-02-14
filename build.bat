@echo off
setlocal enabledelayedexpansion

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

set ROOTDIR=%~dp0
set SRCDIR=%ROOTDIR%src
set OUTDIR=%ROOTDIR%bin
set OBJDIR=%OUTDIR%\obj

if not exist "%OUTDIR%" mkdir "%OUTDIR%"
if not exist "%OBJDIR%" mkdir "%OBJDIR%"

set CFLAGS=/nologo /W3 /Zi /O2 /MD
set INCLUDES=/I"%ROOTDIR%lib\raylib\include"
set LIBDIR=/LIBPATH:"%ROOTDIR%lib\raylib\lib"
set LIBS=raylib.lib kernel32.lib user32.lib gdi32.lib winmm.lib shell32.lib opengl32.lib advapi32.lib

set SOURCES= ^
    main.c ^
    g_game.c ^
    r_render.c ^
    p_play.c ^
    u_utils.c

echo Compiling...
for %%f in (%SOURCES%) do (
    echo   %%f
    clang-cl %CFLAGS% %INCLUDES% ^
        /c "%SRCDIR%\%%f" ^
        /Fo"%OBJDIR%\%%~nf.obj"
)

echo Linking...
clang-cl %CFLAGS% ^
    "%OBJDIR%\*.obj" ^
    /Fe:"%OUTDIR%\out.exe" ^
    /link %LIBDIR% %LIBS%

echo Done.
endlocal
