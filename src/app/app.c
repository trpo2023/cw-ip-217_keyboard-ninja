#include <locale.h>
#include <windows.h>
#include <string.h>
#include <stdio.h>

#include <definitions.h>
#include <interface.h>

int mistakes = 0, min = 0, sec = 0;
int numberSigns = 0, step = 1;
BOOL errorZone = FALSE;

char bigString[] = "SI often take books from the school library. The library is helpful when I have to make a report or when I need information on some subjects. The choice of books in our school library is very good. There are many short stories and novels, textbooks and reference books, dictionaries and encyclopedias there.";

MainWindow mainWindow;
GameWindow gameWindow;
ResultWindow resultWindow;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    WNDCLASSA NWC = newWindowClass((HBRUSH)(WHITE_BRUSH + 1), LoadCursor(NULL, IDC_ARROW), hInst, icon, "Window", softwareMainProcedure);
    RegisterClassA(&NWC);

    createWindow();
    ShowWindow(mainWindow.window, SW_SHOWNORMAL);
    UpdateWindow(mainWindow.window);
    createAllWidgets();

    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return 0;
}