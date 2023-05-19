#include <ctest.h>
#include <string.h>
#include <stdio.h>

#include <parser.h>
#include <definitions.h>
#include <interface.h>

UINT_PTR timerIdt;

int mistakes = 0, min = 0, sec = 0;
int numberSigns = 0, step = 1;
BOOL errorZone = FALSE, isStart = TRUE, isEnd = FALSE;

char strings[MAX_ELEMENTS / 2][MAX_ELEMENTS / 2];
int amount, randomIndex;

MainWindow mainWindow;
GameWindow gameWindow;
ResultWindow resultWindow;

// Проверяет сколько строк файла удалось прочитать
CTEST(INPUT_FILE, CHECK_AMOUNT_STRINGS)
{
    ASSERT_EQUAL(10, putStrings("data/input.txt"));
}

// Проверка на то, что функция построения статистики прекращается из-за несуществования файла
CTEST(DATA_FILE, CHECK_EMPTY_FILE)
{
    ASSERT_EQUAL(0, strcmp("No games have been played yet.", createStatisticsString("text/input/values.txt")));
}

// Проверяет добавление новой записи в файл
CTEST(OUTPUT_FILE, CHECK_NEW_LINE)
{
    ASSERT_EQUAL(0, saveResults("test/input/values.txt", 600, 2));
    ASSERT_EQUAL(0, saveResults("test/input/values.txt", 232, 6));
    ASSERT_EQUAL(0, saveResults("test/input/values.txt", 134, 0));

    FILE *file = fopen("test/input/values.txt", "r");

    int count = 0;
    char container[MAX_ELEMENTS / 2];

    while (fgets(container, MAX_ELEMENTS / 2, file))
    {
        if (count == 0)
            ASSERT_EQUAL(0, strcmp(container, "600 2\n"));
        else if (count == 1)
            ASSERT_EQUAL(0, strcmp(container, "232 6\n"));
        else if (count == 2)
            ASSERT_EQUAL(0, strcmp(container, "134 0\n"));
        else
            break;
        count++;
    }

    fclose(file);
}

// Проверка правильности построения строки скорости
CTEST(STRINGS, CHECK_SPEED_STRING)
{
    ASSERT_EQUAL(0, strcmp("430 ch/min", createSpeedString(430)));
    ASSERT_NOT_EQUAL(0, strcmp("32 ch/min", createSpeedString(320)));
}

// Проверка правильности сравнения двух строк во время печати
CTEST(STRINGS, CHECK_STRING_EQUALITY)
{
    ASSERT_TRUE(checkString("First string", "First string"));
    ASSERT_FALSE(checkString("Let's try it", "Lets try it"));
    ASSERT_TRUE(checkString("Some interesting words about something", "Some interesting words about something"));
}