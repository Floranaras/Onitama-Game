@echo off
echo Compiling source files...
mkdir obj 2>nul
mkdir obj\src 2>nul

gcc -Wall -std=c99 -Iinclude -c main.c -o obj/main.o
gcc -Wall -std=c99 -Iinclude -c src/load.c -o obj/src/load.o
gcc -Wall -std=c99 -Iinclude -c src/display.c -o obj/src/display.o
gcc -Wall -std=c99 -Iinclude -c src/check.c -o obj/src/check.o
gcc -Wall -std=c99 -Iinclude -c src/game.c -o obj/src/game.o
gcc -Wall -std=c99 -Iinclude -c src/start.c -o obj/src/start.o
gcc -Wall -std=c99 -Iinclude -c src/menu.c -o obj/src/menu.o

echo Linking...
gcc obj/main.o obj/src/*.o -o onitama.exe

echo Done! Run the game with: onitama

