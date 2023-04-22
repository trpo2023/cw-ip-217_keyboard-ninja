#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define OnClickedButton 1
#define OnInputWindow 2
#define MAX_ELEMENTS 1024

HWND mainWindow, button, textZone, input, errorWindow, timerWindow, speedWindow;
HDC hDc;
int mistakes = 0;
BOOL wrong = FALSE;

UINT_PTR timer_idt;
int min, sec;

char bigString[] = "Some text. Write it here, please. I need you to understand it.";

char * createErrorString()
{
    static char errorString[255];
    char word[] = "Mistakes: ";
    char value[255];
    itoa(mistakes, value, 10);
    int j = 0;

    for (int i = 0; i < strlen(word); i++, j++)
        errorString[j] = word[i];

    for (int i = 0; i < strlen(value); i++, j++)
        errorString[j] = value[i];

    errorString[j] = '\0';
    return errorString;
}

char * createTimerString()
{
    static char string[255];
    char minstr[255];
    char secstr[255];
    itoa(min, minstr, 10);
    itoa(sec, secstr, 10);
    int j = 0;

    if (min < 10)
    {
        string[j] = '0';
        j++;
    }

    for (int i = 0; i < strlen(minstr); i++, j++)
        string[j] = minstr[i];

    string[j] = ':';
    j++;
    if (sec < 10)
    {
        string[j] = '0';
        j++;
    }

    for (int i = 0; i < strlen(secstr); i++, j++)
        string[j] = secstr[i];

    string[j] = '\0';
    return string;
}

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
        case WM_TIMER:
        {
            if (sec > 59)
            {
                sec = 0;
                min++;
            }
            else
            {
                sec++;
            }
            SendMessage(timerWindow, WM_SETTEXT, TRUE, (LPARAM)createTimerString());
            // KillTimer(hwnd, timer_idt);
            break;
        }
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
                    printf("Button is here!\n");
                    DestroyWindow((HWND)lParam);
                    UpdateWindow(hwnd);
                    ShowWindow(input, SW_SHOWNORMAL);
                    ShowWindow(textZone, SW_SHOWNORMAL);
                    ShowWindow(errorWindow, SW_SHOWNORMAL);
                    ShowWindow(timerWindow, SW_SHOWNORMAL);
                    ShowWindow(speedWindow, SW_SHOWNORMAL);
                    min = 0, sec = 0;
                    SetTimer(hwnd, timer_idt, 1000, NULL);  // Ставим таймер на 1 секунду
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
                
                if (!wrong)
                {
                    if (!stringHandler(bigString, string))
                    {
                        mistakes++;
                        SendMessage(errorWindow, WM_SETTEXT, TRUE, (LPARAM)createErrorString());
                        SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                        SetTextColor((HDC)wParam, RGB(255, 0, 0));
                        wrong = TRUE;
                        return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
                    }
                    else
                    {
                        SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                        SetTextColor((HDC)wParam, RGB(0, 0, 0));
                        return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
                    }
                }
                else
                {
                    if (stringHandler(bigString, string))
                    {
                        SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                        SetTextColor((HDC)wParam, RGB(0, 0, 0));
                        wrong = FALSE;
                        return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
                    }
                    else
                    {
                        SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                        SetTextColor((HDC)wParam, RGB(255, 0, 0));
                        return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
                    }
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
    // Размер шрифта
    LOGFONT logfont; 
    ZeroMemory(&logfont, sizeof(LOGFONT));
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfHeight = -20; 
    HFONT hFont = CreateFontIndirect(&logfont);

    button = CreateWindow("button", "START THE GAME", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 400, 500, 100, hwnd, (HMENU)OnClickedButton, NULL, NULL);

    // HBITMAP hImage = LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    // SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

    textZone = CreateWindow("static", bigString, WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 25, (WIDTH - 65), 200, hwnd, NULL, NULL, NULL);
    SendMessage(textZone, WM_SETFONT, (WPARAM)hFont, TRUE);

    errorWindow = CreateWindow("static", createErrorString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 25, 225, 185, 75, hwnd, NULL, NULL, NULL);
    SendMessage(errorWindow, WM_SETFONT, (WPARAM)hFont, TRUE);

    timerWindow = CreateWindow("static", createTimerString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 300, 225, 185, 75, hwnd, NULL, NULL, NULL);
    SendMessage(timerWindow, WM_SETFONT, (WPARAM)hFont, TRUE);

    speedWindow = CreateWindow("static", createTimerString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 575, 225, 185, 75, hwnd, NULL, NULL, NULL);
    SendMessage(speedWindow, WM_SETFONT, (WPARAM)hFont, TRUE);

    input = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 25, 300, (WIDTH - 65), 200, hwnd, (HMENU)OnInputWindow, NULL, NULL);
    SendMessage(input, WM_SETFONT, (WPARAM)hFont, TRUE);
    // WS_VSCROLL - для скролла

    ShowWindow(input, SW_HIDE);
    ShowWindow(textZone, SW_HIDE);
    ShowWindow(errorWindow, SW_HIDE);
    ShowWindow(timerWindow, SW_HIDE);
    ShowWindow(speedWindow, SW_HIDE);

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
    // wcl.hbrBackground = (HBRUSH)CreatePatternBrush((HBITMAP)LoadImage(NULL, TEXT("1.bmp"), 0, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
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