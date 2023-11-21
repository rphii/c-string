#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* inclusion and configuration of vector */
#include "str.h"

#define VEC_SETTINGS_KEEP_ZERO_END 1
#define VEC_SETTINGS_STRUCT_ITEMS s

VEC_IMPLEMENT(Str, str, char, BY_VAL, 0);

/* other functions */

#define STR_DEFAULT_BLOCKSIZE   32

#if 1
int str_fmt(Str *str, char *format, ...)
{
    if(!str) return -1;
    if(!format) return -1;
    // calculate length of append string
    va_list argp;
    va_start(argp, format);
    size_t len_app = (size_t)vsnprintf(0, 0, format, argp);
    if((int)len_app < 0) {
        return -1;
    }
    va_end(argp);
    // calculate required memory
    size_t len_new = str->last + len_app + 1;
    size_t required = str->cap ? str->cap : STR_DEFAULT_BLOCKSIZE;
    while(required < len_new) required = required << 1;
    // make sure to have enough memory
    if(required > str->cap)
    {
        char *temp = realloc(str->s, required);
        // safety check
        // apply address and set new allocd
        if(!temp) return -1;
        str->s = temp;
        str->cap = required;
    }
    // actual append
    va_start(argp, format);
    int len_chng = vsnprintf(&(str->s)[str->last], len_app + 1, format, argp);
    va_end(argp);
    // check for success
    if(len_chng >= 0 && (size_t)len_chng <= len_app) {
        str->last += (size_t)len_chng; // successful, change length
    } else {
        return -1;
    }
    return 0;
}
#endif

