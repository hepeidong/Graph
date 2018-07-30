#ifndef SPDEFINE_H
#define SPDEFINE_H

#include <assert.h>
#include <stdio.h>

#define GRAPH_DEBUG 1

#if defined(__GNUC__) && (__GNUC__ >= 4)
#define FORMAT_PRINTF(formatPos, argPos) __attribute__((format(printf,formatPos,argPos)))
#elif defined(__has_attribute)
    #if __has_attribute(format)
    #define FORMAT_PRINTF(formatPos, argPos) __attribute__((format(printf,formatPos,argPos)))
    #endif
#else
#define FORMAT_PRINTF(formatPos, argPos)
#endif

#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

#define SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define SAFE_RELEASE(p)          do { if(p) { (p)->Release(); } } while(0)
#define SAFE_RELEASE_NULL(p)     do { if(p) { (p)->Release(); (p) = nullptr; } } while(0)
#define SAFE_RETAIN(p)           do { if(p) { (p)->Retain(); } } while(0)
#define BREAK_IF(cond)           if(cond) break

#if defined(GRAPH_DEBUG) && (GRAPH_DEBUG == 1)
#define DEBUGMSG(format, ...)     printf(format, ##__VA_ARGS__)
#define DEBUGERROR(format, ...)   printf(format, ##__VA_ARGS__)

#elif GRAPH_DEBUG > 1
#define DEBUGMSG(format, ...)     printf(format, ##__VA_ARGS__)
#define DEBUGERROR(format, ...)   printf(format, ##__VA_ARGS__)

#else
#define DEBUGMSG(format, ...)
#define DEBUGERROR(format, ...)
#endif

#ifndef UNUSED_PARAM
#define UNUSED_PARAM(unused) (void)unused
#endif

#define ASSERT(cond, msg)    do{ DEBUGMSG("%s", msg); assert(cond); } while(0)

#endif // SPDEFINE_H
