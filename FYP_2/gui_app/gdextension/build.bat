@echo off
mkdir bin bin\int ..\project\gdextension_bin
set build_type=%1
set WARNINGS=/W3 /wd4312 /wd4005 /wd4172 /wd4127 /wd4530 /wd4459 /wd5105 /wd4100 /wd4996 /wd4244 
set FLAGS=/utf-8 /MP /LD %WARNINGS%
set RELEASE_FLAGS=/O2
set DEBUG_FLAGS=/Z7 /Od
set LIB_PATH=/LIBPATH:"..\..\..\..\Godot\godot-cpp\bin\" 
set LIBS=
set LIBS_DEBUG=libgodot-cpp.windows.template_debug.x86_64.lib
set LIBS_RELEASE=
set LIB_NAME=gdextension.dll
set INCLUDES=/I src\ /I ..\..\..\..\Godot\godot-cpp\gen\include /I ..\..\..\..\Godot\godot-cpp\include /I ..\..\..\..\Godot\godot-cpp\gdextension
set DEFINES=/DUNICODE /DTYPED_METHOD_BIND
set THIRD_PARTY_SRC=
set SRC=src\*.cpp %THIRD_PARTY_SRC%
set CPP_STANDARD=/std:c++17
if not defined DevEnvDir (
    call vcvarsall.bat x64
)

if "%build_type%"=="Debug" (
    cl.exe /Fe:..\project\gdextension_bin\%LIB_NAME% %SRC% /Fo:bin\int\ %CPP_STANDARD% %DEFINES% %FLAGS% %DEBUG_FLAGS% %INCLUDES% /link %LINKER_FLAGS% %LIB_PATH% %LIBS% %LIBS_DEBUG%
)
if "%build_type%"=="Release" (
    cl.exe /Fe:..\project\gdextension_bin\%LIB_NAME% %SRC% /Fo:bin\int\ %CPP_STANDARD% %DEFINES% %FLAGS% %RELEASE_FLAGS% %INCLUDES% /link %LINKER_FLAGS% %LIB_PATH% %LIBS% %LIBS_RELEASE%
)
if "%build_type%"=="Clean" (
    cd bin\int\
    del *.obj
    cd ..\..\..\project\gdextension_bin\
    del *.exp
    del *.ilk
    del *.lib
    del *.dll
    del *.pdb
    cd ..\..\gdextension\
)
