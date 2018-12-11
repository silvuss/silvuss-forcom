#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include "readline.h"
#include "output.h"
#include "misc.h"

// advice: learning pointers, "segmentation fault" is your friend
// advice: gcc with "-Wall" and "-Wextra" parameters may be good some deeply hidden errors
// advice: the "bad address" error may mean something like "not linked" -> do not use the "-c" option of gcc unless necessary
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("There are too little arguments given. Exit\n");
        exit(EXIT_FAILURE);
    }
    else if (argc > 3)
    {
        printf("There are too many arguments given. Exit\n");
        exit(EXIT_FAILURE);
    }

    // argv[0] is the name of this .c file
    const size_t inputFileNameLength = strlen(argv[1]);
    char *const inputFileName = calloc(inputFileNameLength, sizeof(argv[1]));
    strcpy(inputFileName, argv[1]);
    const size_t outputFileNameLength = strlen(argv[2]);
    char *outputFileName = calloc(outputFileNameLength, sizeof(argv[2]));
    strcpy(outputFileName, argv[2]);

    FILE *const inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL)
    {
        perror(inputFileName);
        exit(errno);
    }

    char *newOutputFileName = handleOutputFileName(outputFileNameLength, outputFileName);
    FILE *outputFile = fopen(newOutputFileName, "wb");
    if (outputFile == NULL)
    {
        perror(outputFileName);
        exit(errno);
    }

    // main processing

    char *line = NULL;
    unsigned long start = 0;
    bool wasCommentLine = false;
    unsigned long intendedGroupLength = 30;
    char *partToMove = malloc(1);
    memset(partToMove, '\0', 1);
    while ((line = readLine(inputFile, start)))
    {
        if (strlen(line) < 2 || !(line[0] == '/' && line[1] == '/'))
        {
            if (true == wasCommentLine)
            {
                // it is "normal line"

                // handle case that partToMove is not empty
                //  (i.e. there is still string remaining)
                while (strlen(partToMove) > intendedGroupLength)
                {
                    // copy first part
                    fputs("// ", outputFile);
                    for (unsigned long i = 0; i < intendedGroupLength; ++i)
                    {
                        fputc(partToMove[i], outputFile);
                    }
                    fputc('\n', outputFile);

                    // create new part to move
                    const size_t newPartToMoveLength = strlen(partToMove) - intendedGroupLength + 2; // +1 for one space after the string, +1 for NULL terminator
                    char *newPartToMove = malloc(newPartToMoveLength);
                    memset(newPartToMove, '\0', newPartToMoveLength);
                    memcpy(newPartToMove, partToMove + intendedGroupLength, newPartToMoveLength - 2);
                    memset(newPartToMove + newPartToMoveLength - 1, ' ', 1);
                    partToMove = newPartToMove;
                }

                // copy last line if it is not empty
                if (strlen(partToMove) > 0)
                {
                    fputs("// ", outputFile);
                    fputs(partToMove, outputFile);
                    if (NULL != readLine(inputFile, start + strlen(line) + 1))
                    {
                        // if it is not last line in file
                        fputc('\n', outputFile);
                    }
                }
            }

            fputs(line, outputFile);
            fputc('\n', outputFile);
            wasCommentLine = false;
        }
        else
        {
            // it is "comment line"

            if (false == wasCommentLine)
            {
                // it is new group

                partToMove = realloc(partToMove, 1);
                if (partToMove == NULL)
                {
                    fprintf(stderr, "Error: main: partToMove == NULL\n");
                    exit(EXIT_FAILURE);
                }
                memset(partToMove, '\0', 1);
            }

            // remove slashes and optional space
            unsigned int toLeft = (line[2] == ' ' ? 3 : 2);
            const size_t lineWithoutSlashesLength = strlen(line) - toLeft + 1; // +1 for NULL terminator
            char *lineWithoutSlashes = malloc(lineWithoutSlashesLength);
            memcpy(lineWithoutSlashes, line + toLeft, lineWithoutSlashesLength - 1);
            memset(lineWithoutSlashes + lineWithoutSlashesLength - 1, '\0', 1);

            // merge
            const size_t combinedLineLength = strlen(partToMove) + strlen(lineWithoutSlashes) + 1; // +1 for NULL terminator
            char *combinedLine = malloc(combinedLineLength);
            memcpy(combinedLine, partToMove, strlen(partToMove));
            memcpy(combinedLine + strlen(partToMove), lineWithoutSlashes, strlen(lineWithoutSlashes));
            memset(combinedLine + combinedLineLength - 1, '\0', 1);

            if (strlen(combinedLine) > intendedGroupLength)
            {
                // copy first part
                fputs("// ", outputFile);
                for (unsigned long i = 0; i < intendedGroupLength; ++i)
                {
                    fputc(combinedLine[i], outputFile);
                }
                fputc('\n', outputFile);

                // create new part to move
                const size_t newPartToMoveLength = strlen(combinedLine) - intendedGroupLength + 2; // +1 for one space after the string, +1 for NULL terminator
                if (newPartToMoveLength > 2)
                {
                    partToMove = realloc(partToMove, newPartToMoveLength);
                    if (partToMove == NULL)
                    {
                        fprintf(stderr, "Error: main: partToMove == NULL\n");
                        exit(EXIT_FAILURE);
                    }
                    memcpy(partToMove, combinedLine + intendedGroupLength, newPartToMoveLength - 2);
                }
                memset(partToMove + newPartToMoveLength - 2, ' ', 1);
                memset(partToMove + newPartToMoveLength - 1, '\0', 1);
            }

            free(combinedLine);

            wasCommentLine = true;
        }

        start += strlen(line) + 1;
    }

    // cleaning

    free(inputFileName);
    free(outputFileName);
    free(newOutputFileName);

    fclose(inputFile);
    fclose(outputFile);

    exit(EXIT_SUCCESS);
}