#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdbool.h>

#include "misc.h"

// helpful: https://stackoverflow.com/a/1085120
void printNull(char *stringName, size_t size, char *string)
{
    printf("Size of %s == [%lu], %s == [", stringName, size, stringName);
    for (unsigned long i = 0; i < size; ++i)
    {
        if (string[i] == '\0')
        {
            printf("NULL");
        }
        else
        {
            printf("%c", string[i]);
        }
    }
    printf("]\n");
}