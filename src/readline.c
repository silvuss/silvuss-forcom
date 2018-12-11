#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "readline.h"

// returns a NULL-terminated char array
char *readLine(FILE *stream, unsigned int start)
{
    if (stream == NULL)
    {
        fprintf(stderr, "Error: readLine: stream == NULL\n");
        exit(EXIT_FAILURE);
    }

    fseek(stream, 0, SEEK_END);
    size_t streamSize = ftell(stream); // in bytes
    fseek(stream, 0, SEEK_SET);        // go to the start of the inputFile

    if (streamSize == 0 || start > streamSize)
    {
        return NULL;
    }

    unsigned int lineLength = 0;
    char c;
    int fseek_status = fseek(stream, start, SEEK_SET);
    if (fseek_status != 0)
    {
        perror("readLine");
        exit(errno);
    }

    while ((c = fgetc(stream)))
    {
        if (c == '\n' || c == EOF)
        {
            break;
        }

        ++lineLength;
    }

    char *dst = malloc(lineLength + 1); // +1 for terminator (NULL character)
    if (dst == NULL)
    {
        perror("readLine");
        exit(errno);
    }

    fseek_status = fseek(stream, start, SEEK_SET);
    if (fseek_status != 0)
    {
        perror("readLine");
        exit(errno);
    }

    fgets(dst, lineLength + 1, stream); // +1 for newline
    dst[lineLength] = '\0';

    return dst;
}