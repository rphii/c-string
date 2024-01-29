# Things may still change
# Very untested as of now
- I have no time to write more tests ;\_;

# c-string
WIP... Relies on a [generic vector implementation](https://www.github.com/rphii/c-vector).

- The code is C99 (and upwards) compatible. Compiles with gcc, tcc, clang
- The **goal** is dynamically easy to use, fast, reusable and secure handling of strings.
- The **idea** is making use of a *generic vector* and expanding it to fit our needs. (*In fact,
  there is currently only one function implemented within `str.c`, that is `str_fmt` which acts
  similarly to how `sprintf` would. Everything else comes from `vec.h`)*
- Clean your strings with `str_free`

## Example
```c
#include "str.h"

int main(void)
{
    Str string = {0};

    printf("string is %s empty\n", str_empty(&string) ? "indeed" : "not");

    str_fmt(&string, "Hello"); /* str_fmt always appends... I basically only ever use this function :) */
    str_push_back(&string, ',');
    str_push_back(&string, ' ');
    str_fmt(&string, "World!");

    printf("string is %s empty\n", str_empty(&string) ? "indeed" : "not");
    printf("back of string  : %c\n", str_get_back(&string)); /* '!' */
    printf("front of string : %c\n", str_get_front(&string)); /* 'H' */

    printf("%s\n", string.s); /* "Hello, World!" */
    printf("string length : %zu\n", str_length(&string)); /* 13 */

    str_reverse(&string);
    printf("%s\n", string.s); /* "!dlroW ,olleH" */

    str_swap(&string, 0, str_length(&string) - 1);
    printf("%s\n", string.s); /* "HdlroW ,olle!" */

    Str copy = {0};
    str_copy(&copy, &string);
    printf("%s\n", copy.s); /* "HdlroW ,olle!" */

    printf("reserved %zu bytes [in string]\n", str_reserved(&string)); /* 32 bytes */
    str_clear(&copy);
    printf("cleared string: [%.*s]\n", STR_F(&copy)); /* !!! anytime printing anything, this is the correct way of doing so !!! (see 12 lines below; direct access to .s field may or may not be dangerous, especially if there are operations (such as pop) happening at the front of the string !!!) */
    str_fmt(&copy, "re-using those %zu byes!", str_reserved(&copy));
    printf("string fmt after clear: %s\n", copy.s);
    str_free(&copy);
    printf("reserved %zu bytes after free [in copy]\n", str_reserved(&copy)); /* 0 bytes */
    printf("reserved %zu bytes after all above [in string]\n", str_reserved(&string)); /* 32 bytes */

    char pop = 0;
    str_pop_front(&string, &pop); /* pop is an optional argument, pass 0 to ignore */
    printf("pop front : %c\n", pop); /* 'H' */
    str_pop_back(&string, &pop);
    printf("pop back  : %c\n", pop); /* '!' */
    printf("string after pop : %s [expected to be incorrect, mainly due to directly accessing the struct] \n", string.s); /* "HdlroW ,olle!" */
    printf("string after pop : %.*s [correct access]\n", STR_F(&string)); /* "dlroW ,olle" */

    str_shrink(&string);
    printf("string after shrink : %s\n", string.s); /* "dlroW ,olle" */

    str_push_front(&string, '_');
    str_insert_at(&string, 3, 'X');
    str_set_at(&string, 10, 'Y');
    printf("after modification : %s\n", string.s); /* "_dlXroW ,oYle" */
    printf("string length : %zu\n", str_length(&string)); /* 13 */

    str_free(&string); /* clean up */
    printf("after free reserved %zu bytes\n", str_reserved(&string)); /* 0 bytes */
    printf("string length : %zu\n", str_length(&string)); /* 0 */

    return 0;
}
```

## TODO so I won't forget
- lower
- upper
- concat etc -> vec
- find etc -> vec

