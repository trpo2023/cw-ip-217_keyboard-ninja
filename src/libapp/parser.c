#include <stdio.h>
#include <stdlib.h>

#include <definitions.h>

int putStrings()
{
    FILE *file = fopen("data/input.txt", "r");
    if (file == NULL)
    {
        printf("Error! Failed to open file!\n");
        fclose(file);
        return -1;
    }

    int count = 0;

    while (fgets(strings[count], MAX_ELEMENTS / 2, file))
    {
        int length = strlen(strings[count]);
        if (strings[count][length - 1] == '\n')
        {
            strings[count][length - 1] = '\0';
        }
        count++;
    }
    fclose(file);
    return count;
}

int saveResults(int speed, int percent)
{
    FILE *file = fopen("data/data.txt", "a");
    if (file == NULL)
    {
        printf("Error! Failed to open file!\n");
        fclose(file);
        return -1;
    }

    // char speedStr[MIN_ELEMENTS];
    // char percentStr[MIN_ELEMENTS];

    // itoa(speed, speedStr, 10);
    // itoa(percentStr, percentStr, 10);

    fprintf(file, "%d %d\n", speed, percent);

    fclose(file);
    return 0;
}