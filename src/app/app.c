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

HWND mainWindow, startButton, textZone, input, errorWindow, timerWindow, speedWindow;
HDC hDc;
int mistakes = 0;
BOOL errorZone = FALSE;

UINT_PTR timer_idt;
int min = 0, sec = 0;
int numberSigns = 0;
int step = 1;

char bigString[] = "Some text. Write it here, please. I need you to understand it.";
// char bigString[] = "Exercitation esse occaecat nostrud sit sint amet. Labore ea esse laborum cupidatat. Commodo Lorem cillum minim dolore. Ex reprehenderit aute tempor commodo laborum exercitation dolore ullamco cillum consequat magna id fugiat officia.";

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

char * createSpeedString(int speed)
{
    static char string[255];
    char word[] = " ch/min";
    char value[255];
    itoa(speed, value, 10);
    int j = 0;

    for (int i = 0; i < strlen(value); i++, j++)
        string[j] = value[i];
    
    for (int i = 0; i < strlen(word); i++, j++)
        string[j] = word[i];
    string[j] = '\0';
    return string;
}

BOOL checkString(char *original, char *string)
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
            float time = (((float) min * 60) + (float) sec) / 60;
            int signs = numberSigns / 3;
            int currentSpeed = signs / ((float) step / 60);
            SendMessage(speedWindow, WM_SETTEXT, TRUE, (LPARAM)createSpeedString(currentSpeed));
            step++;
            if (step == 5)
            {
                numberSigns = 0;
                step = 1;
            }
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
                numberSigns++;
                int value = HIWORD(wParam); // макрос HIWORD извлекает из wParam значение кода уведомления
                char string[MAX_ELEMENTS];
                GetWindowText((HWND)lParam, string, MAX_ELEMENTS);

                if (value == EN_UPDATE) // EN_CHANGE (may be use)
                    printf("string: %s\n", string);
                
                if (!errorZone)
                {
                    if (!strcmp(bigString, string))
                    {
                        KillTimer(hwnd, timer_idt);
                    }
                    else if (!checkString(bigString, string))
                    {
                        mistakes++;
                        SendMessage(errorWindow, WM_SETTEXT, TRUE, (LPARAM)createErrorString());
                        SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                        SetTextColor((HDC)wParam, RGB(255, 0, 0));
                        errorZone = TRUE;
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
                    if (checkString(bigString, string))
                    {
                        SetBkColor((HDC)wParam, GetSysColor(COLOR_WINDOW));
                        SetTextColor((HDC)wParam, RGB(0, 0, 0));
                        errorZone = FALSE;
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
    logfont.lfHeight = -30;
    HFONT hFont = CreateFontIndirect(&logfont);

    startButton = CreateWindow("button", "START THE GAME", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 150, 400, 500, 100, hwnd, (HMENU)OnClickedButton, NULL, NULL);
    SendMessage(startButton, WM_SETFONT, (WPARAM)hFont, TRUE);

    // HBITMAP hImage = LoadImage(NULL, "background.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    // SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

    logfont.lfHeight = -20;
    hFont = CreateFontIndirect(&logfont);

    textZone = CreateWindow("static", bigString, WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 25, (WIDTH - 65), 200, hwnd, NULL, NULL, NULL);
    SendMessage(textZone, WM_SETFONT, (WPARAM)hFont, TRUE);

    errorWindow = CreateWindow("static", createErrorString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 25, 225, 185, 75, hwnd, NULL, NULL, NULL);
    SendMessage(errorWindow, WM_SETFONT, (WPARAM)hFont, TRUE);

    timerWindow = CreateWindow("static", createTimerString(), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 300, 225, 185, 75, hwnd, NULL, NULL, NULL);
    SendMessage(timerWindow, WM_SETFONT, (WPARAM)hFont, TRUE);

    speedWindow = CreateWindow("static", createSpeedString(0), WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | DT_CENTER, 575, 225, 185, 75, hwnd, NULL, NULL, NULL);
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