@echo off
pushd build
gcc -ggdb ../source/main.c -o Game.exe -Wall -Wextra -O0  -std=c99 -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
popd