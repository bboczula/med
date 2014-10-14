#include <iostream>
#include <string>
#include <memory>
#include "CStorageHandler.h"
#include "CCommandFactory.h"
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
    CInputHandler inputHandler(make_shared<CStorageHandler>(), make_shared<CCommandFactory>());

    string choice;
    while(true)
    {
        cout << prompt();
        cin >> choice;
        try
        {
            inputHandler.process(choice);
        }
        catch(EQuit)
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
    }
}
