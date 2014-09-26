#include <iostream>
#include <string>
#include "CStorageHandler.h"
#include "ICommand.h"
#include "CInputHandler.h"
#include "CLogger.h"
using namespace std;

string prompt()
{
	string mode("NORMAL");
	return mode + "> ";
}

int main()
{
    CLogger::getInstance()->log("Entered function main()");
    CStorageHandler storageHandler;
    CInputHandler inputHandler(&storageHandler);;

    string choice;
    while(true)
    {
        CLogger::getInstance()->log("Entered main loop");
        cout << prompt();
        cin >> choice;
        inputHandler.process(choice);
    }
}
