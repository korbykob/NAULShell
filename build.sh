#!/bin/bash
set -e

mkdir -p bin/commands

gcc $PROGRAM_COMPILER_FLAGS -Iinclude src/commands/help.c -o bin/commands/help.o
gcc $PROGRAM_COMPILER_FLAGS -Iinclude src/commands/exit.c -o bin/commands/exit.o
gcc $PROGRAM_COMPILER_FLAGS -Iinclude src/commands/ping.c -o bin/commands/ping.o
gcc $PROGRAM_COMPILER_FLAGS -Iinclude src/commands/clear.c -o bin/commands/clear.o
gcc $PROGRAM_COMPILER_FLAGS -Iinclude src/commands/kys.c -o bin/commands/kys.o
gcc $PROGRAM_COMPILER_FLAGS -Iinclude src/shell.c -o bin/shell.o

ld -r bin/commands/help.o bin/commands/exit.o bin/commands/ping.o bin/commands/clear.o bin/commands/kys.o bin/shell.o -o bin/final.o

nm bin/final.o > bin/shell.sym

ld $PROGRAM_LINKER_FLAGS bin/final.o -o bin/shell.bin
