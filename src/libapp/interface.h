#pragma once

#include <windows.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct
{
    HWND window;
    HWND startButton;
} MainWindow;

typedef struct
{
    HWND textZone;
    HWND inputZone;
    HWND errors;
    HWND timer;
    HWND speed;
} GameWindow;

typedef struct
{
    HWND box;
} ResultWindow;

extern MainWindow mainWindow;
extern GameWindow gameWindow;
extern ResultWindow resultWindow;

HFONT createFont(int size);
void hideMainWidgets();
void showMainWidgets();
void hideAllGameWidgets(BOOL isStart);
void showAllGameWidgets();
void createWindow();
void createAllWidgets();