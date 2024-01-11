#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define ARRAY_SIZE 1001

unsigned concatenate(unsigned x, unsigned y) {
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

int main(void)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char lines[ARRAY_SIZE];
    int calibrationValues = 0;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("cannot find file\n");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        printf("Retrieved line of length %zu:\n", read);
        printf("%s\n", line);

        int digits[ARRAY_SIZE]; //this is way too big but fuck yeah we got memory
        int indexToInsert = 0;
        int i, j;
        char character;

        for (i = 0; i < strlen(line); i++)
        {
            character = line[i];
            if (isdigit(character)) {
                digits[indexToInsert] = character - '0';
                indexToInsert++;
            }
        }
        int concat = concatenate(digits[0], digits[indexToInsert -1]);
        calibrationValues += concat;
    }

    if (ferror(fp))
    {
        printf("there was an error reading the file\n");
    }

    printf("\nResult: %d\n", calibrationValues);

    free(line);
    fclose(fp);

    return EXIT_SUCCESS;
}
