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