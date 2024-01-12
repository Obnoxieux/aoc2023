#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define ARRAY_SIZE 1001

unsigned concatenateInteger(unsigned x, unsigned y)
{
    unsigned pow = 10;
    while (y >= pow)
        pow *= 10;
    return x * pow + y;
}

void strreplace(char *src, char *str, char *rep)
{
    char *p = strstr(src, str);
    do
    {
        if (p)
        {
            char buf[1024];
            memset(buf, '\0', strlen(buf));

            if (src == p)
            {
                strcpy(buf, rep);
                strcat(buf, p + strlen(str));
            }
            else
            {
                strncpy(buf, src, strlen(src) - strlen(p));
                strcat(buf, rep);
                strcat(buf, p + strlen(str));
            }

            memset(src, '\0', strlen(src));
            strcpy(src, buf);
        }

    } while (p && (p = strstr(src, str)));
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s 1 or 2\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char lines[ARRAY_SIZE];
    int calibrationValues = 0;
    int linesProcessed = 0;

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

        char *numberWords[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        int digits[ARRAY_SIZE]; // this is way too big but fuck yeah we got memory
        int indexToInsert = 0;
        int i, j, k;
        char character;

        // Part 2
        if (strcmp(argv[1], "2") == 0)
        {
            // Hack alert - this is baaaaaaaad and will most definitely only work some of the time
            strreplace(line, "twone", "twoone");
            strreplace(line, "oneight", "oneeight");
            strreplace(line, "nineight", "nineeight");
            strreplace(line, "fiveight", "fiveeight");
            strreplace(line, "threeight", "threeeight");
            strreplace(line, "sevenine", "sevennine");
            strreplace(line, "eightwo", "eighttwo");
            strreplace(line, "eighthree", "eightthree");

            // replace substrings with digits
            for (k = 0; k <= 8; k++)
            {
                char replacement[2];
                sprintf(replacement, "%d", k + 1);
                strreplace(line, numberWords[k], replacement);
                if (k == 8)
                {
                    printf("Line after conversion: %s\n", line);
                }
            }
        }

        for (i = 0; i < strlen(line); i++)
        {
            character = line[i];
            if (isdigit(character))
            {
                digits[indexToInsert] = character - '0';
                indexToInsert++;
            }
        }
        int concat = concatenateInteger(digits[0], digits[indexToInsert - 1]);
        printf("Calibration value for line: %d\n", concat);
        calibrationValues += concat;
        printf("Current Value: %d\n", calibrationValues);
        linesProcessed++;
    }

    if (ferror(fp))
    {
        printf("there was an error reading the file\n");
    }
    printf("\nLines processed: %d\n", linesProcessed);
    printf("\nResult: %d\n", calibrationValues);

    free(line);
    fclose(fp);

    return EXIT_SUCCESS;
}
