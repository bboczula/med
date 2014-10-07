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

void printTestcaseStarted()
{
    cout << "\033[32m### TESTCASE STARTED ###\033[0m\n";
}

void printTestcaseEnded()
{
    cout << "\033[31m### TESTCASE ENDED ###\033[0m\n";
}

void printTestStep(string msg)
{
    cout << "\033[34m(" + msg + ")\033[0m\n";
}

void terminateTestcase(CInputHandler* inputHandler)
{
    try
    {
        inputHandler->process("q");
    }
    catch(EQuit)
    {
        cout << "### TESTCASE ENDED ###" << endl;
        return;
    }
}

void TC_BasicFunctionality()
{
    printTestcaseStarted();
    CInputHandler* inputHandlerPtr = new CInputHandler(make_shared<CStorageHandler>());
    printTestStep("print current line");
    inputHandlerPtr->process("p");
    printTestStep("go to the next line");
    inputHandlerPtr->process("+");
    printTestStep("print current line");
    inputHandlerPtr->process("p");
    printTestStep("go to the last line");
    inputHandlerPtr->process("$");
    terminateTestcase(inputHandlerPtr);
    delete inputHandlerPtr;
    printTestcaseEnded();
}

void TC_ToggleCurrentLine()
{
    printTestcaseStarted();
    CInputHandler* inputHandlerPtr = new CInputHandler(make_shared<CStorageHandler>());
    for(int i = 0; i < 5; i++)
    {
        printTestStep("go to the next line");
        inputHandlerPtr->process("+");
        printTestStep("go to the previous line");
        inputHandlerPtr->process("-");
    }
    terminateTestcase(inputHandlerPtr);
    delete inputHandlerPtr;
    printTestcaseEnded();
}

void TC_GoBeforeTheFirstLine()
{
    printTestcaseStarted();
    CInputHandler* inputHandlerPtr = new CInputHandler(make_shared<CStorageHandler>());
    printTestStep("go before the first line");
    inputHandlerPtr->process("-");
    terminateTestcase(inputHandlerPtr);
    delete inputHandlerPtr;
    printTestcaseEnded();
}

int main()
{
    CLogger::getInstance()->log("Entered function main()");
    CInputHandler inputHandler(make_shared<CStorageHandler>());

    // Test1
    TC_BasicFunctionality();
    TC_ToggleCurrentLine();
    TC_GoBeforeTheFirstLine();
}
