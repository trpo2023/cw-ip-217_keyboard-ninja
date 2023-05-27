#pragma once

#include <windows.h>

#include <interface.h>

#define STANDARD_SIZE 255
#define MAX_ELEMENTS 1024
#define MIN_ELEMENTS 10

extern UINT_PTR timerIdt;

extern int mistakes, min, sec;
extern int numberSigns, step;
extern BOOL errorZone, isStart, isEnd;

extern int amount, randomIndex;
extern char strings[MAX_ELEMENTS / 2][MAX_ELEMENTS / 2];

extern MainWindow mainWindow;
extern GameWindow gameWindow;
extern ResultWindow resultWindow;

int insertPart(char *firstString, char *secondString, int j);
char *createErrorString();
char *createTimerString();
char *createSpeedString(int speed);
void createResultString(char *text, char *string);
BOOL checkString(char *original, char *string);
LRESULT changeColor(HDC wParam, int red, int green, int blue);
void prepareForStart(HWND hwnd);
LRESULT WINAPI softwareMainProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
WNDCLASSA newWindowClass(HBRUSH BGColor, HCURSOR cursor, char *name, WNDPROC procedure);