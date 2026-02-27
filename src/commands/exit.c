#include <commands/exit.h>
#include <shell.h>
#include <allocator.h>
#include <processes.h>

void shellExit()
{
    unallocate(directory);
    quit();
}
