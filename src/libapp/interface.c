#include <windows.h>

#include <definitions.h>
#include <interface.h>

HFONT createFont(int size)
{
    LOGFONT logfont;
    ZeroMemory(&logfont, sizeof(LOGFONT));
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfHeight = size; // Размер шрифта
    return CreateFontIndirect(&logfont);
}

void createWindow()
{
    mainWindow.window = CreateWindow("Window", "KeyboardNinja", WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT / 2), WIDTH, HEIGHT, NULL, NULL, NULL, NULL);

    // mainWindow.background = CreateWindow("static", "", SS_BITMAP | WS_VISIBLE | WS_CHILD, 0, 0, WIDTH, HEIGHT, mainWindow.window, NULL, GetModuleHandle(NULL), NULL);
}

void createMainWidgets()
{
    mainWindow.startButton = CreateWindow("button", "START THE GAME", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 400, 500, 100, mainWindow.window, (HMENU)START_GAME_BUTTON, NULL, NULL);
    SendMessage(mainWindow.startButton, WM_SETFONT, (WPARAM)createFont(-30), TRUE);

    // HBITMAP hNewBmp = LoadImage(hInst, "data/background.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
    // SendMessage(mainWindow.window, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hNewBmp);

    // HBITMAP hImage = LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    // SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

    ShowWindow(mainWindow.startButton, SW_SHOWNORMAL);
}

void createGameWidgets()
{
    gameWindow.textZone = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 25, (WIDTH - 65), 200, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.textZone, WM_SETFONT, (WPARAM)createFont(-20), TRUE);

    gameWindow.errors = CreateWindow("static", createErrorString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 25, 225, 185, 75, mainWindow.window, (HMENU)ERRORS_WINDOW, NULL, NULL);
    SendMessage(gameWindow.errors, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    gameWindow.timer = CreateWindow("static", createTimerString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 300, 225, 185, 75, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.timer, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    gameWindow.speed = CreateWindow("static", createSpeedString(0), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 575, 225, 185, 75, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.speed, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    ShowWindow(gameWindow.textZone, SW_SHOWNORMAL);
    ShowWindow(gameWindow.errors, SW_SHOWNORMAL);
    ShowWindow(gameWindow.timer, SW_SHOWNORMAL);
    ShowWindow(gameWindow.speed, SW_SHOWNORMAL);
}

void createInputZone()
{
    gameWindow.inputZone = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 25, 300, (WIDTH - 65), 200, mainWindow.window, (HMENU)INPUT_WINDOW, NULL, NULL);
    SendMessage(gameWindow.inputZone, WM_SETFONT, (WPARAM)createFont(-20), TRUE);

    ShowWindow(gameWindow.inputZone, SW_SHOWNORMAL);
}

void createResultWidgets()
{
    resultWindow.box = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | DT_CENTER, 230, 25, 310, 170, mainWindow.window, NULL, NULL, NULL);
    SendMessage(resultWindow.box, WM_SETFONT, (WPARAM)createFont(-20), TRUE);

    resultWindow.menuButton = CreateWindow("button", "Back to menu", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 180, 210, 200, 70, mainWindow.window, (HMENU)MAIN_MENU_BUTTON, NULL, NULL);
    SendMessage(resultWindow.menuButton, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    resultWindow.nextGameButton = CreateWindow("button", "Play again", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 390, 210, 200, 70, mainWindow.window, (HMENU)NEXT_GAME_BUTTON, NULL, NULL);
    SendMessage(resultWindow.nextGameButton, WM_SETFONT, (WPARAM)createFont(-25), TRUE);

    ShowWindow(resultWindow.box, SW_SHOWNORMAL);
    ShowWindow(resultWindow.menuButton, SW_SHOWNORMAL);
    ShowWindow(resultWindow.nextGameButton, SW_SHOWNORMAL);
}

void destroyMainWidgets()
{
    DestroyWindow(mainWindow.startButton);
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