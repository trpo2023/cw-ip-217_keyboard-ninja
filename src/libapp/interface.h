#pragma once

#include <windows.h>

#define WIDTH 800
#define HEIGHT 600
#define HEADER 10
#define START_GAME_BUTTON 1
#define MAIN_MENU_BUTTON 2
#define NEXT_GAME_BUTTON 3
#define INPUT_WINDOW 4
#define ERRORS_WINDOW 5
#define STATISTICS_BUTTON 6

typedef struct
{
    HWND window;
    HWND header;
    HWND startButton;
    HWND statisticButton;
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
    HWND menuButton;
    HWND nextGameButton;
} ResultWindow;

HFONT createFont(int size);
void createWindow();
void createMainWidgets();
void createGameWidgets();
void createInputZone();
void createResultWidgets();
void destroyMainWidgets();
void destroyGameWidgets();
void destroyInputZone();
void destroyResultWidgets();