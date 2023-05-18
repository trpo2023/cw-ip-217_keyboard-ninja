#include <locale.h>
#include <windows.h>

#include <definitions.h>
#include <interface.h>

HINSTANCE hInst;
HDC hDc;
HICON icon;
UINT_PTR timerIdt;

int mistakes = 0, min = 0, sec = 0;
int numberSigns = 0, step = 1;
BOOL errorZone = FALSE, isEnd = FALSE;

char strings[MAX_ELEMENTS / 2][MAX_ELEMENTS / 2];
int amount, randomIndex;

MainWindow mainWindow;
GameWindow gameWindow;
ResultWindow resultWindow;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    WNDCLASSA NWC = newWindowClass((HBRUSH)(LTGRAY_BRUSH), LoadCursor(NULL, IDC_ARROW), hInst, icon, "Window", softwareMainProcedure);
    RegisterClassA(&NWC);

    createWindow();
    ShowWindow(mainWindow.window, SW_SHOWNORMAL);
    UpdateWindow(mainWindow.window);
    amount = putStrings();
    createAllWidgets();

    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}