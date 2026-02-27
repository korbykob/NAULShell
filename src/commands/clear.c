#include <commands/clear.h>
#include <tty.h>

void shellClear()
{
    put(TTY_CLEAR);
}
