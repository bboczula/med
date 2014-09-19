#include <iostream>
#include <string>
#include "CStorageHandler.h"
#include "ICommand.h"
#include "CInputHandler.h"
using namespace std;

string prompt()
{
	string mode = "NORMAL";
	return mode + "> ";
}

int main()
{
    CStorageHandler storageHandler;
    CInputHandler inputHandler(&storageHandler);;

	string choice;
	while(true)
	{
		cout << prompt();
		cin >> choice;
        if(inputHandler.process(choice))
        {
            return 0;
        }
	}
	return 0;
}
