#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>

#define WIDTH 800
#define HEIGHT 600
#define OnClickedButton 1
#define OnInputWindow 2
#define MAX_ELEMENTS 1024

HWND mainWindow, button, textZone, input, errorMessage;
HDC hDc;

char bigString[] = "Some text. Write it here, please. I need you to understand it.";

BOOL stringHandler(char *original, char *string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (original[i] != string[i])
            return FALSE;
    }
    return TRUE;
}

LRESULT WINAPI WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case OnClickedButton:
                {
                    printf("Button is here!");
                    DestroyWindow((HWND)lParam);
                    UpdateWindow(hwnd);
                    ShowWindow(input, SW_SHOWNORMAL);
                    ShowWindow(textZone, SW_SHOWNORMAL);
                    break;
                }               
            }
        }
        case WM_CTLCOLOREDIT:
        {
            if ((HWND)lParam == GetDlgItem(hwnd, OnInputWindow))
            {		
                int value = HIWORD(wParam); // макрос HIWORD извлекает из wParam значение кода уведомления
                char string[MAX_ELEMENTS];
                GetWindowText((HWND)lParam, string, MAX_ELEMENTS);

                if (value == EN_UPDATE) // EN_CHANGE (may be use)
                    printf("string: %s\n", string);

                if (!stringHandler(bigString, string))
                {
                    ShowWindow(errorMessage, SW_SHOWNORMAL);
                    SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                    SetTextColor((HDC)wParam, RGB(255, 0, 0));
                    return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
                }
                else
                {
                    ShowWindow(errorMessage, SW_HIDE);
                    SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                    SetTextColor((HDC)wParam, RGB(0, 0, 0));
                    return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
                }
            }
            break;
        }
        default:
            return DefWindowProcA(hwnd, message, wParam, lParam);
    }
}

void CreateAllWidgets(HWND hwnd)
{
    button = CreateWindow("button", "START THE GAME", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 400, 500, 100, hwnd, (HMENU)OnClickedButton, NULL, NULL);

    textZone = CreateWindow("static", bigString, WS_VISIBLE | WS_CHILD, 25, 25, (WIDTH - 65), 200, hwnd, NULL, NULL, NULL);
    
    input = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL, 25, 300, (WIDTH - 65), 200, hwnd, (HMENU)OnInputWindow, NULL, NULL);

    errorMessage = CreateWindow("static", "ERROR!", WS_VISIBLE | WS_CHILD, 50, 500, 80, 550, hwnd, NULL, NULL, NULL);

    ShowWindow(input, SW_HIDE);
    ShowWindow(textZone, SW_HIDE);
    ShowWindow(errorMessage, SW_HIDE);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.lpszClassName = "Window";
    wcl.lpfnWndProc = WndProc;
    wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcl.hbrBackground = (HBRUSH)(WHITE_BRUSH + 1);
    RegisterClassA(&wcl);

    mainWindow = CreateWindow("Window", "KeyboardNinja", WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) / 2) - (WIDTH / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (HEIGHT / 2), WIDTH, HEIGHT, NULL, NULL, NULL, NULL);
    ShowWindow(mainWindow, SW_SHOW);
    UpdateWindow(mainWindow);

    CreateAllWidgets(mainWindow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}