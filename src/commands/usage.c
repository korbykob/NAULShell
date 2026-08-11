#include <commands/usage.h>
#include <allocator.h>
#include <tty.h>
#include <str.h>

void shellUsage()
{
    write("Using ");
    char usage[100];
    uint64_t total = getUsage();
    uint64_t mb = total / 1000000;
    toString(usage, mb);
    write(usage);
    write(" MB, ");
    total -= mb * 1000000;
    uint64_t kb = total / 1000;
    toString(usage, kb);
    write(usage);
    write(" KB, and ");
    total -= kb * 1000;
    toString(usage, total);
    write(usage);
    write(" bytes of ram.\n");
}
