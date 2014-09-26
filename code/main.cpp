#include <iostream>
#include <string>
#include <memory>
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
    CInputHandler inputHandler(make_shared<CStorageHandler>());

    string choice;
    while(true)
    {
        cout << prompt();
        cin >> choice;
        inputHandler.process(choice);
    }
}
