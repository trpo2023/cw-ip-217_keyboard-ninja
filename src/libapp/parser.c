#include <stdio.h>
#include <stdlib.h>

#include <definitions.h>
#include <parser.h>

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

    fprintf(file, "%d %d\n", speed, percent);

    fclose(file);
    return 0;
}

char *createStatisticsString()
{
    static char string[STANDARD_SIZE];
    FILE *file = fopen("data/data.txt", "r");
    if (file == NULL)
    {
        fclose(file);
        return "No games have been played yet.";
    }

    int count = 0, max = 0, sumSpeed = 0, sumMistakes = 0, j;
    char container[MIN_ELEMENTS];
    char speedStr[MIN_ELEMENTS];
    char percentStr[MIN_ELEMENTS];

    while (fgets(container, MIN_ELEMENTS, file))
    {
        if (!strlen(container))
            break;

        for (j = 0; container[j] != ' '; j++)
        {
            speedStr[j] = container[j];
        }
        speedStr[j++] = '\0';

        int i;
        for (i = 0; container[i] != '\n'; i++, j++)
        {
            percentStr[i] = container[j];
        }
        percentStr[i] = '\0';

        int speed = atoi(speedStr);
        if (speed > max)
            max = speed;
        sumSpeed += speed;

        sumMistakes += atoi(percentStr);

        count++;
    }

    if (count == 0)
        return "No games have been played yet.";

    char countStr[MIN_ELEMENTS];
    char averageMistakesStr[MIN_ELEMENTS];

    j = insertPart(string, "STATISTICS\n\nNumber of games: ", 0);
    itoa(count, countStr, 10);
    j = insertPart(string, countStr, j);

    j = insertPart(string, "\nMax speed: ", j);
    j = insertPart(string, createSpeedString(max), j);

    int averageSpeed = sumSpeed / count;
    j = insertPart(string, "\nAverage speed: ", j);
    j = insertPart(string, createSpeedString(averageSpeed), j);

    int averageMistakes = sumMistakes / count;
    itoa(averageMistakes, averageMistakesStr, 10);
    j = insertPart(string, "\nError percentage: ", j);
    j = insertPart(string, averageMistakesStr, j);
    j = insertPart(string, "%", j);

    fclose(file);
    return string;
}