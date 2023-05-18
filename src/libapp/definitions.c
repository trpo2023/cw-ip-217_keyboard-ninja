#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#include <definitions.h>
#include <interface.h>

int putStrings()
{
    FILE *file = fopen("data/input.txt", "r");
    if (file == NULL)
    {
        printf("Error! Failed to open file!\n");
        fclose(file);
        return -1;
    }

    int count = 0;

    while (fgets(strings[count], MAX_ELEMENTS / 2, file))
    {
        int length = strlen(strings[count]);
        if (strings[count][length - 1] == '\n')
        {
            strings[count][length - 1] = '\0';
        }
        count++;
    }
    fclose(file);
    return count;
}

int insertPart(char *firstString, char *secondString, int j)
{
    for (int i = 0; i < strlen(secondString); i++, j++)
        firstString[j] = secondString[i];
    firstString[j] = '\0';
    return j;
}

char *createErrorString()
{
    static char errorString[255];
    char word[] = "Mistakes: ";
    char value[STANDARD_SIZE];
    itoa(mistakes, value, 10);

    int j = insertPart(errorString, word, 0);
    j = insertPart(errorString, value, j);

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

    j = insertPart(string, minStr, j);
    string[j++] = ':';

    if (sec < 10)
        string[j++] = '0';

    j = insertPart(string, secStr, j);

    return string;
}

char *createSpeedString(int speed)
{
    static char string[STANDARD_SIZE];
    char word[] = " ch/min";
    char value[STANDARD_SIZE];
    itoa(speed, value, 10);
    
    int j = insertPart(string, value, 0);
    j = insertPart(string, word, j);

    return string;
}

char *createResultString(char *text)
{
    static char string[] = "RESULTS\n\nTime: ";
    int j = strlen(string);

    j = insertPart(string, createTimerString(), j);
    string[j++] = '\n';

    j = insertPart(string, "Speed: ", j);
    int speed = strlen(text) / (min + ((float) sec / 60));
    j = insertPart(string, createSpeedString(speed), j);
    string[j++] = '\n';

    j = insertPart(string, createErrorString(), j);
    j = insertPart(string, " (", j);
    int percent = (100 * mistakes) / strlen(text);
    char value[STANDARD_SIZE];
    itoa(percent, value, 10);
    j = insertPart(string, value, j);
    j = insertPart(string, "%)", j);
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
            srand(time(NULL));
            randomIndex = rand() % amount;
            SendMessage(gameWindow.textZone, WM_SETTEXT, TRUE, (LPARAM)strings[randomIndex]);
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
                printf("%s VS %s\n", string, strings[randomIndex]);

            if (!strcmp(strings[randomIndex], string) && !isEnd)
            {
                printf("You are here\n");
                KillTimer(hwnd, timerIdt);
                hideAllGameWidgets(FALSE);
                ShowWindow(resultWindow.box, SW_SHOW);
                SendMessage(resultWindow.box, WM_SETTEXT, TRUE, (LPARAM)createResultString(string));
                SendMessage(gameWindow.inputZone, EM_SETREADONLY, TRUE, 0);
                isEnd = TRUE;
            }
            else if (!checkString(strings[randomIndex], string))
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
    // NWC.hbrBackground = (HBRUSH)CreatePatternBrush((HBITMAP)LoadImage(NULL, TEXT("data/background.bmp"), 0, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
    return NWC;
}