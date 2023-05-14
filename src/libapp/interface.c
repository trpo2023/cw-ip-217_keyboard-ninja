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

void hideMainWidgets()
{
    ShowWindow(mainWindow.startButton, SW_HIDE);
}

void showMainWidgets()
{
    ShowWindow(mainWindow.startButton, SW_SHOWNORMAL);
}

void hideAllGameWidgets(BOOL isStart)
{
    if (isStart)
        ShowWindow(gameWindow.inputZone, SW_HIDE);
    ShowWindow(gameWindow.textZone, SW_HIDE);
    ShowWindow(gameWindow.errors, SW_HIDE);
    ShowWindow(gameWindow.timer, SW_HIDE);
    ShowWindow(gameWindow.speed, SW_HIDE);
}

void showAllGameWidgets()
{
    ShowWindow(gameWindow.inputZone, SW_SHOWNORMAL);
    ShowWindow(gameWindow.textZone, SW_SHOWNORMAL);
    ShowWindow(gameWindow.errors, SW_SHOWNORMAL);
    ShowWindow(gameWindow.timer, SW_SHOWNORMAL);
    ShowWindow(gameWindow.speed, SW_SHOWNORMAL);
}

void createWindow()
{
    mainWindow.window = CreateWindow("Window", "KeyboardNinja", WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT / 2), WIDTH, HEIGHT, NULL, NULL, NULL, NULL);
}

void createAllWidgets()
{
    HFONT hFont = createFont(-30);

    mainWindow.startButton = CreateWindow("button", "START THE GAME", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 400, 500, 100, mainWindow.window, (HMENU)OnClickedButton, NULL, NULL);
    SendMessage(mainWindow.startButton, WM_SETFONT, (WPARAM)hFont, TRUE);

    showMainWidgets();

    // HBITMAP hImage = LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    // SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

    hFont = createFont(-20);
        
    gameWindow.textZone = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 25, (WIDTH - 65), 200, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.textZone, WM_SETFONT, (WPARAM)hFont, TRUE);

    gameWindow.errors = CreateWindow("static", createErrorString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 25, 225, 185, 75, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.errors, WM_SETFONT, (WPARAM)hFont, TRUE);

    gameWindow.timer = CreateWindow("static", createTimerString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 300, 225, 185, 75, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.timer, WM_SETFONT, (WPARAM)hFont, TRUE);

    gameWindow.speed = CreateWindow("static", createSpeedString(0), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 575, 225, 185, 75, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.speed, WM_SETFONT, (WPARAM)hFont, TRUE);

    gameWindow.inputZone = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 25, 300, (WIDTH - 65), 200, mainWindow.window, (HMENU)OnInputWindow, NULL, NULL);
    SendMessage(gameWindow.inputZone, WM_SETFONT, (WPARAM)hFont, TRUE);

    // WS_VSCROLL - для скролла
    hideAllGameWidgets(TRUE);

    hFont = createFont(-25);

    resultWindow.box = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 250, 150, 250, 150, mainWindow.window, NULL, NULL, NULL);
    SendMessage(gameWindow.speed, WM_SETFONT, (WPARAM)hFont, TRUE);
    ShowWindow(resultWindow.box, SW_HIDE);
}