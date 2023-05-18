#include <windows.h>
#include <string.h>

#include <definitions.h>
#include <interface.h>

HFONT createFont(int size)
{
    LOGFONT logfont;
    ZeroMemory(&logfont, sizeof(LOGFONT));
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfHeight = size; // Размер шрифта
    logfont.lfWeight = 10;
    strcpy(logfont.lfFaceName, "Tahoma"); 
    return CreateFontIndirect(&logfont);
}

void createWindow()
{
    mainWindow.window = CreateWindow("Window", "KeyboardNinja", WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT / 2), WIDTH, HEIGHT, NULL, NULL, NULL, NULL);
}

void createMainWidgets()
{
    mainWindow.header = CreateWindow("static", "KEYBOARD NINJA", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 0, 75, WIDTH, 200, mainWindow.window, (HMENU)HEADER, NULL, NULL);
    SendMessage(mainWindow.header, WM_SETFONT, (WPARAM)createFont(-90), TRUE);

    mainWindow.startButton = CreateWindow("button", "Start the Game", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 250, 500, 100, mainWindow.window, (HMENU)START_GAME_BUTTON, NULL, NULL);
    SendMessage(mainWindow.startButton, WM_SETFONT, (WPARAM)createFont(-40), TRUE);

    mainWindow.statisticButton = CreateWindow("button", "Statistics", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 320, 500, 150, 50, mainWindow.window, (HMENU)STATISTICS_BUTTON, NULL, NULL);
    SendMessage(mainWindow.startButton, WM_SETFONT, (WPARAM)createFont(-40), TRUE);

    ShowWindow(mainWindow.header, SW_SHOWNORMAL);
    ShowWindow(mainWindow.startButton, SW_SHOWNORMAL);
    ShowWindow(mainWindow.statisticButton, SW_SHOWNORMAL);
}

void createGameWidgets()
{
    gameWindow.textZone = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 10, (WIDTH - 65), 210, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.textZone, WM_SETFONT, (WPARAM)createFont(-20), TRUE);

    gameWindow.errors = CreateWindow("static", createErrorString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER | WS_BORDER, 25, 235, 185, 75, mainWindow.window, (HMENU)ERRORS_WINDOW, NULL, NULL);
    SendMessage(gameWindow.errors, WM_SETFONT, (WPARAM)createFont(-27), TRUE);

    gameWindow.timer = CreateWindow("static", createTimerString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER | WS_BORDER, 300, 235, 185, 75, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.timer, WM_SETFONT, (WPARAM)createFont(-27), TRUE);

    gameWindow.speed = CreateWindow("static", createSpeedString(0), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER | WS_BORDER, 575, 235, 185, 75, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.speed, WM_SETFONT, (WPARAM)createFont(-27), TRUE);

    ShowWindow(gameWindow.textZone, SW_SHOWNORMAL);
    ShowWindow(gameWindow.errors, SW_SHOWNORMAL);
    ShowWindow(gameWindow.timer, SW_SHOWNORMAL);
    ShowWindow(gameWindow.speed, SW_SHOWNORMAL);
}

void createInputZone()
{
    gameWindow.inputZone = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 25, 325, (WIDTH - 65), 210, mainWindow.window, (HMENU)INPUT_WINDOW, NULL, NULL);
    SendMessage(gameWindow.inputZone, WM_SETFONT, (WPARAM)createFont(-20), TRUE);

    ShowWindow(gameWindow.inputZone, SW_SHOWNORMAL);
}

void createResultWidgets()
{
    resultWindow.box = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | DT_CENTER, 230, 25, 310, 205, mainWindow.window, NULL, NULL, NULL);
    SendMessage(resultWindow.box, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    resultWindow.menuButton = CreateWindow("button", "Back to menu", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 180, 240, 200, 70, mainWindow.window, (HMENU)MAIN_MENU_BUTTON, NULL, NULL);
    SendMessage(resultWindow.menuButton, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    resultWindow.nextGameButton = CreateWindow("button", "Play again", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 390, 240, 200, 70, mainWindow.window, (HMENU)NEXT_GAME_BUTTON, NULL, NULL);
    SendMessage(resultWindow.nextGameButton, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    ShowWindow(resultWindow.box, SW_SHOWNORMAL);
    ShowWindow(resultWindow.menuButton, SW_SHOWNORMAL);
    ShowWindow(resultWindow.nextGameButton, SW_SHOWNORMAL);
}

void destroyMainWidgets()
{
    DestroyWindow(mainWindow.startButton);
    DestroyWindow(mainWindow.header);
    DestroyWindow(mainWindow.statisticButton);
}

void destroyGameWidgets()
{
    DestroyWindow(gameWindow.textZone);
    DestroyWindow(gameWindow.errors);
    DestroyWindow(gameWindow.timer);
    DestroyWindow(gameWindow.speed);
}

void destroyInputZone()
{
    DestroyWindow(gameWindow.inputZone);
}

void destroyResultWidgets()
{
    DestroyWindow(resultWindow.box);
    DestroyWindow(resultWindow.menuButton);
    DestroyWindow(resultWindow.nextGameButton);
}