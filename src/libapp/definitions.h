#pragma once

#include <windows.h>

#include <interface.h>

#define OnClickedButton 1
#define OnInputWindow 2
#define STANDARD_SIZE 255
#define MAX_ELEMENTS 1024

HINSTANCE hInst;
HDC hDc;
HICON icon;
UINT_PTR timer_idt;

extern int mistakes, min, sec;
extern int numberSigns, step;
extern BOOL errorZone;

extern char bigString[];

extern MainWindow mainWindow;
extern GameWindow gameWindow;
extern ResultWindow resultWindow;

char *createErrorString();
char *createTimerString();
char *createSpeedString(int speed);
char *createResultString(char *text);
BOOL checkString(char *original, char *string);
LRESULT WINAPI softwareMainProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
WNDCLASSA newWindowClass(HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, char *name, WNDPROC procedure);