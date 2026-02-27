#include <commands/help.h>
#include <tty.h>

void shellHelp()
{
    write(
TTY_GREEN "help       " TTY_DEFAULT ": Shows this info screen\n"
TTY_GREEN "exit       " TTY_DEFAULT ": Exit the shell\n"
TTY_GREEN "ping       " TTY_DEFAULT ": Reply with \"Pong!\"\n"
TTY_GREEN "clear      " TTY_DEFAULT ": Clear the terminal\n"
TTY_GREEN "kys        " TTY_DEFAULT ": Panic the system\n"
TTY_GREEN "(folder)/* " TTY_DEFAULT ": List files in the folder\n"
TTY_GREEN "(folder)/  " TTY_DEFAULT ": Enter the folder\n"
TTY_GREEN "..         " TTY_DEFAULT ": Go back a folder\n"
TTY_GREEN "(file)     " TTY_DEFAULT ": Execute or read the file\n");
}
