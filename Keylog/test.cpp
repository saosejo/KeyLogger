
// Header file for input output functions 
#include<iostream>
#include <windows.h>
#include <Lmcons.h>

using namespace std; 

// main function - 
// where the execution of program begins 
int main() 
{ 
	// prints hello world
	
	HKL KeyboardLayout = GetKeyboardLayout(0);

	printf("%x \n",KeyboardLayout);
		
	return 0; 
} 