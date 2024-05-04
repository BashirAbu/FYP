@echo off
python moc.py
python uic.py
set build_type=%1
mkdir bin\int

if "%build_type%"=="Debug" (
    set FLAGS=/EHsc /utf-8 /Z7 /Od /MDd /MP /W3 /wd4312 /wd4005 /wd4172 /wd4127 /wd4530 /wd4459 /wd5105 /wd4100 /wd4996 /std:c++17 /Zc:__cplusplus /permissive- 
    set LIBS=user32.lib gdi32.lib opengl32.lib advapi32.lib Qt6Cored.lib Qt6Guid.lib Qt6Widgetsd.lib shell32.lib
)

if "%build_type%"=="Release" (
    set FLAGS=/EHsc /utf-8 /O2 /MD /MP /W3 /wd4312 /wd4005 /wd4172 /wd4127 /wd4530 /wd4459 /wd5105 /wd4100 /wd4996 /std:c++17 /Zc:__cplusplus /permissive-
    set LIBS=user32.lib gdi32.lib opengl32.lib advapi32.lib Qt6Core.lib Qt6Gui.lib Qt6Widgets.lib
)

if "%build_type%"=="Mem_Test" (
    set FLAGS=/EHsc /utf-8 /Od /Z7 /MDd /MP /W3 /wd4312 /wd4005 /wd4172 /wd4127 /wd4530 /wd4459 /wd5105 /wd4100 /wd4996 /std:c++17 /Zc:__cplusplus /permissive-
    set LIBS=user32.lib gdi32.lib opengl32.lib advapi32.lib Qt6Core.lib Qt6Gui.lib Qt6Widgets.lib
)
set EXE_NAME=servo_controller.exe
set LIBSDIR=/LIBPATH:third_party\qt\lib /LIBPATH:third_party\sdl\lib\x64\ /SUBSYSTEM:CONSOLE
set INCLUDES=/I src /I src/auto_gen /I third_party\qt\include /I third_party\qt\include\QtWidgets
set DEFINES=
set SRC=src\*.cpp src\auto_gen\*.cpp

call vcvarsall x64

rc /fo bin\servo_controller.res servo_controller.rc 

cl.exe /Fe:bin\%EXE_NAME% %SRC% bin\servo_controller.res /Fo:bin\int\ %FLAGS% %INCLUDES% /link %LIBSDIR% %LIBS%

if "%build_type%"=="Mem_Test" (
    pushd bin
    heob64 %EXE_NAME%
    popd
)