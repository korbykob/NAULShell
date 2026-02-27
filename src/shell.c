#include <shell.h>
#include <definitions.h>
#include <allocator.h>
#include <tty.h>
#include <processes.h>
#include <scheduler.h>
#include <filesystem.h>
#include <str.h>

const struct
{
    const char* name;
    void (*function)();
} commands[] = 
{
    { "help", shellHelp },
    { "exit", shellExit },
    { "ping", shellPing },
    { "clear", shellClear },
    { "kys", shellKys },
    { 0, 0 }
};
char* directory = 0;

void entry()
{
    uint64_t directoryLength = 1;
    directory = allocate(directoryLength + 1);
    directory[0] = '/';
    directory[1] = '\0';
    char command[256];
    while (true)
    {
        write(TTY_BLUE);
        write(directory);
        write(TTY_DEFAULT);
        read(command, 255);
        uint64_t commandLength = stringLength(command);
        if (commandLength > 0)
        {
            uint64_t bufferLength = directoryLength + commandLength;
            char* buffer = allocate(bufferLength + 1);
            copyString(directory, buffer);
            copyString(command, buffer + directoryLength);
            void (*function)() = 0;
            uint64_t commandId = 0;
            while (commands[commandId].name)
            {
                if (compareStrings(command, commands[commandId].name) == 0)
                {
                    function = commands[commandId].function;
                    break;
                }
                commandId++;
            }
            if (!function)
            {
                if (buffer[bufferLength - 2] == '/' && buffer[bufferLength - 1] == '*')
                {
                    buffer[bufferLength - 2] = '\0';
                    if (checkFolder(buffer))
                    {
                        uint64_t count = 0;
                        const char** files = getFiles(buffer, &count);
                        for (uint64_t i = 0; i < count; i++)
                        {
                            bool folder = checkFolder(files[i]);
                            if (folder)
                            {
                                write(TTY_BLUE);
                            }
                            write(files[i] + bufferLength - 1);
                            if (folder)
                            {
                                write("/" TTY_DEFAULT);
                            }
                            put('\n');
                        }
                        unallocate(files);
                    }
                    else
                    {
                        write("Folder does not exist\n");
                    }
                }
                else if (buffer[bufferLength - 1] == '/' && buffer[bufferLength - 2] != '/')
                {
                    buffer[bufferLength - 1] = '\0';
                    if (checkFolder(buffer))
                    {
                        unallocate(directory);
                        directoryLength = bufferLength;
                        directory = allocate(directoryLength + 1);
                        copyString(buffer, directory);
                        directory[directoryLength - 1] = '/';
                        directory[directoryLength] = '\0';
                    }
                    else
                    {
                        write("Folder does not exist\n");
                    }
                }
                else if (compareStrings(command, "..") == 0)
                {
                    if (directory[1] != '\0')
                    {
                        char* current = directory + directoryLength - 2;
                        uint64_t count = 0;
                        while (*current-- != '/')
                        {
                            count++;
                        }
                        directory[directoryLength - count - 1] = '\0';
                        directoryLength -= count + 1;
                    }
                }
                else if (checkFile(buffer))
                {
                    if (compareStrings(buffer + bufferLength - 4, ".bin") == 0)
                    {
                        waitForThread(execute(buffer));
                    }
                    else
                    {
                        uint64_t size = 0;
                        const char* file = (const char*)getFile(buffer, &size);
                        for (uint64_t i = 0; i < size; i++)
                        {
                            if (*file != TTY_CLEAR)
                            {
                                put(*file);
                            }
                            file++;
                        }
                    }
                }
                else
                {
                    write("Unknown command\n");
                }
            }
            unallocate(buffer);
            if (function)
            {
                function();
            }
        }
    }
}
