#include <commands/kys.h>
#include <tty.h>

void shellKys()
{
    write("Killing myself!\n");
    __asm__ volatile ("ud2");
}
