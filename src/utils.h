#ifndef UTILS_H_SENTRY
#define UTILS_H_SENTRY

#include <sys/time.h>

#define MAKE_SWAP_FUNCTION(TYPE) \
    static void swap_ ## TYPE(TYPE *a, TYPE *b) \
    { \
        TYPE tmp; \
        tmp = *a; \
        *a = *b; \
        *b = tmp; \
    }

long milliseconds_between(const struct timeval *start,
                          const struct timeval *end);

long milliseconds_elapsed(const struct timeval *from);

#endif
