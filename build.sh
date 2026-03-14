#!/bin/bash
set -e

mkdir -p bin/commands

COMPILER_FLAGS="$PROGRAM_COMPILER_FLAGS -Iinclude -g -fno-omit-frame-pointer -mavx2 -O2 -fvect-cost-model=dynamic -Wall -Wextra -Werror"

gcc $COMPILER_FLAGS src/commands/help.c -o bin/commands/help.o
gcc $COMPILER_FLAGS src/commands/exit.c -o bin/commands/exit.o
gcc $COMPILER_FLAGS src/commands/ping.c -o bin/commands/ping.o
gcc $COMPILER_FLAGS src/commands/clear.c -o bin/commands/clear.o
gcc $COMPILER_FLAGS src/commands/kys.c -o bin/commands/kys.o
gcc $COMPILER_FLAGS src/shell.c -o bin/shell.o

ld -r bin/commands/help.o bin/commands/exit.o bin/commands/ping.o bin/commands/clear.o bin/commands/kys.o bin/shell.o -o bin/final.o

nm bin/final.o > bin/shell.sym

ld $PROGRAM_LINKER_FLAGS bin/final.o -o bin/shell.nxe
