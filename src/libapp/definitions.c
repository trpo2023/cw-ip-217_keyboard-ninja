#include <stdio.h>
#include <string.h>
#include <windows.h>

#include <definitions.h>
#include <interface.h>

char *createErrorString()
{
    static char errorString[255];
    char word[] = "Mistakes: ";
    char value[STANDARD_SIZE];
    itoa(mistakes, value, 10);
    int j = 0;

    for (int i = 0; i < strlen(word); i++, j++)
        errorString[j] = word[i];

    for (int i = 0; i < strlen(value); i++, j++)
        errorString[j] = value[i];
    errorString[j] = '\0';

    return errorString;
}

char *createTimerString()
{
    static char string[STANDARD_SIZE];
    char minStr[STANDARD_SIZE];
    char secStr[STANDARD_SIZE];
    itoa(min, minStr, 10);
    itoa(sec, secStr, 10);
    int j = 0;

    if (min < 10)
        string[j++] = '0';

    for (int i = 0; i < strlen(minStr); i++, j++)
        string[j] = minStr[i];
    string[j++] = ':';

    if (sec < 10)
        string[j++] = '0';

    for (int i = 0; i < strlen(secStr); i++, j++)
        string[j] = secStr[i];
    string[j] = '\0';

    return string;
}

char *createSpeedString(int speed)
{
    static char string[STANDARD_SIZE];
    char word[] = " ch/min";
    char value[STANDARD_SIZE];
    itoa(speed, value, 10);
    int j = 0;

    for (int i = 0; i < strlen(value); i++, j++)
        string[j] = value[i];

    for (int i = 0; i < strlen(word); i++, j++)
        string[j] = word[i];
    string[j] = '\0';

    return string;
}

char *createResultString(char *text)
{
    static char resultString[] = "RESULTS\r\nTime: ";
    int j = strlen(resultString);

    char *timerString = createTimerString();
    for (int i = 0; i < strlen(timerString); i++, j++)
    {
        resultString[j] = timerString[i];
    }
    resultString[j] = '\n';
    j++;

    resultString[j] = '\0';
    return resultString;
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

LRESULT changeColor(HDC wParam, int red, int green, int blue)
{
    SetBkColor(wParam, GetSysColor(COLOR_WINDOW));
    SetTextColor(wParam, RGB(red, green, blue));
    return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
}

LRESULT WINAPI softwareMainProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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
        SendMessage(gameWindow.timer, WM_SETTEXT, TRUE, (LPARAM)createTimerString());
        int signs = numberSigns / 3;
        int currentSpeed = signs / ((float)step / 60);
        SendMessage(gameWindow.speed, WM_SETTEXT, TRUE, (LPARAM)createSpeedString(currentSpeed));
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
            hideMainWidgets();
            UpdateWindow(hwnd);
            showAllGameWidgets();
            min = 0, sec = 0;
            SetTimer(hwnd, timerIdt, 1000, NULL); // Ставим таймер на 1 секунду
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

            if (!strcmp(bigString, string))
            {
                KillTimer(hwnd, timerIdt);
                hideAllGameWidgets(FALSE);
                ShowWindow(resultWindow.box, SW_SHOWNORMAL);
                SendMessage(resultWindow.box, WM_SETTEXT, TRUE, (LPARAM)createResultString(string));
                SendMessage(gameWindow.inputZone, EM_SETREADONLY, TRUE, 0);
            }
            else if (!checkString(bigString, string))
            {
                if (!errorZone)
                {
                    mistakes++;
                    errorZone = TRUE;
                    SendMessage(gameWindow.errors, WM_SETTEXT, TRUE, (LPARAM)createErrorString());
                }
                return changeColor((HDC)wParam, 255, 0, 0);
            }
            else
            {
                if (errorZone)
                    errorZone = FALSE;
                return changeColor((HDC)wParam, 0, 0, 0);
            }
        }
        break;
    }
    default:
        return DefWindowProcA(hwnd, message, wParam, lParam);
    }
    return 0;
}

WNDCLASSA newWindowClass(HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, char *name, WNDPROC procedure)
{
    WNDCLASSA NWC;
    memset(&NWC, 0, sizeof(WNDCLASSA));
    NWC.hbrBackground = BGColor;
    NWC.hCursor = cursor;
    NWC.hInstance = hInst;
    NWC.lpszClassName = name;
    NWC.lpfnWndProc = softwareMainProcedure;
    // wcl.hbrBackground = (HBRUSH)CreatePatternBrush((HBITMAP)LoadImage(NULL, TEXT("1.bmp"), 0, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
    return NWC;
}