#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "output.h"

char *handleOutputFileName(size_t outputFileNameLength, char *outputFileName)
{
    size_t newOutputFileNameLength = outputFileNameLength;
    char *newOutputFileName = malloc(newOutputFileNameLength);
    memcpy(newOutputFileName, outputFileName, newOutputFileNameLength);

    char *numberString = malloc(2); // 2 instead of 1 because +1 for the char array terminator (the NULL character)
    memset(numberString, '1', 1);
    memset(numberString + 1, '\0', 1);

    // check whether the file exist (without checking permissions)
    while (access(newOutputFileName, F_OK) == 0)
    {
        ++newOutputFileNameLength;
        newOutputFileName = realloc(newOutputFileName, newOutputFileNameLength); // allocate memory for the new max filename length
        if (newOutputFileName == NULL)
        {
            perror("handleOutputFileName");
            exit(errno);
        }
        memcpy(newOutputFileName + newOutputFileNameLength - strlen(numberString), numberString, strlen(numberString)); // change the filename
    }

    free(numberString);

    return newOutputFileName;
}