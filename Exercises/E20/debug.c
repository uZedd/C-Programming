#include <stdio.h>
#include <stdarg.h>
static int stored_level;


void set_debug_level(int debug_level) {
    stored_level = debug_level;
}

int dprintf(int debug_level, const char *fmt, ...) {
    if (debug_level > stored_level) {
        return 0;
    }
    int prefix_count = fprintf(stderr, "[DBG%d] ", debug_level);
    if (prefix_count < 0) {
        return -1;
    }
    va_list args;
    va_start(args, fmt);
    int message_count = vfprintf(stderr, fmt, args);
    va_end(args);

    if (message_count < 0) {
        return -1;
    }

    return message_count + prefix_count;
}
