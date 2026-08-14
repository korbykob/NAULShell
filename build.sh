#!/bin/bash
set -e

mkdir -p bin/commands

COMPILER_FLAGS="$PROGRAM_COMPILER_FLAGS -Iinclude -g -fno-omit-frame-pointer -O2 -fvect-cost-model=dynamic -Wall -Wextra -Werror"

x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/help.c -o bin/commands/help.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/exit.c -o bin/commands/exit.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/ping.c -o bin/commands/ping.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/clear.c -o bin/commands/clear.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/kys.c -o bin/commands/kys.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/usage.c -o bin/commands/usage.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/reboot.c -o bin/commands/reboot.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/commands/shutdown.c -o bin/commands/shutdown.o
x86_64-linux-gnu-gcc $COMPILER_FLAGS src/shell.c -o bin/shell.o

x86_64-linux-gnu-ld -r bin/commands/help.o bin/commands/exit.o bin/commands/ping.o bin/commands/clear.o bin/commands/kys.o bin/commands/usage.o bin/commands/reboot.o bin/commands/shutdown.o bin/shell.o -o bin/final.o

x86_64-linux-gnu-nm bin/final.o > bin/shell.sym

x86_64-linux-gnu-ld $PROGRAM_LINKER_FLAGS bin/final.o -o bin/shell.nxe
