@echo off
echo ==== Creating build directories ====
if not exist obj mkdir obj
if not exist obj\src mkdir obj\src

echo ==== Compiling source files ====
gcc -Wall -std=c99 -Iinclude -c src\load.c -o obj\src\load.o
gcc -Wall -std=c99 -Iinclude -c src\start.c -o obj\src\start.o
gcc -Wall -std=c99 -Iinclude -c src\display.c -o obj\src\display.o
gcc -Wall -std=c99 -Iinclude -c src\check.c -o obj\src\check.o
gcc -Wall -std=c99 -Iinclude -c src\game.c -o obj\src\game.o
gcc -Wall -std=c99 -Iinclude -c src\menu.c -o obj\src\menu.o

echo ==== Compiling test main ====
gcc -Wall -std=c99 -Iinclude -c testing\testmain.c -o obj\testmain.o

echo ==== Linking ====
gcc obj\testmain.o obj\src\*.o -o obj\testmain.exe

if %errorlevel% neq 0 (
    echo ==== Build failed ====
    exit /b %errorlevel%
)

echo ==== Build successful! Running test ====
.\obj\testmain.exe

