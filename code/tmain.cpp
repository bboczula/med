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

void printTestStep(string msg)
{
    cout << "\033[34m(" + msg + ")\033[0m\n";
}

class ITestCase
{
private:
    void terminateTestcase(CInputHandler* inputHandler)
    {
        try
        {
            inputHandler->process("q");
        }
        catch(EQuit)
        {
            cout << "<exception EQuit was caught>" << endl;
            return;
        }
    }
protected:
    CInputHandler* inputHandler;
    std::string name;
public:
    ITestCase(std::string tcName) : name(tcName), inputHandler(0)
    {
    }
    std::string getName()
    {
        return name;
    }
    virtual void execute() = 0;
    void setup()
    {
        inputHandler = new CInputHandler(make_shared<CStorageHandler>());
    }
    void teardown()
    {
        terminateTestcase(inputHandler);
        delete inputHandler;
    }
};

class TC_BasicFunctionality : public ITestCase
{
public:
    TC_BasicFunctionality() : ITestCase("TC_BasicFunctionality")
    {
    }
    void execute()
    {
        printTestStep("go to the first line");
        inputHandler->process("1");
        printTestStep("print current line");
        inputHandler->process("p");
        printTestStep("go to the next line");
        inputHandler->process("+");
        printTestStep("print current line");
        inputHandler->process("p");
        printTestStep("go to the last line");
        inputHandler->process("$");
    }
};

class TC_ToggleCurrentLine : public ITestCase
{
public:
    TC_ToggleCurrentLine() : ITestCase("TC_ToggleCurrentLine")
    {
    }
    void execute()
    {
        printTestStep("go to the first line");
        inputHandler->process("1");
        for(int i = 0; i < 5; i++)
        {
            printTestStep("go to the next line");
            inputHandler->process("+");
            printTestStep("go to the previous line");
            inputHandler->process("-");
        }
    }
};

class TC_GoBeforeTheFirstLine : public ITestCase
{
public:
    TC_GoBeforeTheFirstLine() : ITestCase("TC_GoBeforeTheFirstLine")
    {
    }
    void execute()
    {
        printTestStep("go to the first line");
        inputHandler->process("1");
        printTestStep("go before the first line");
        inputHandler->process("-");
        printTestStep("go before the first line");
        inputHandler->process("-");
        printTestStep("print current line");
        inputHandler->process("p");
        printTestStep("go to the next line");
        inputHandler->process("+");
        printTestStep("go to the previous line");
        inputHandler->process("-");
        printTestStep("go before the first line");
        inputHandler->process("-");
        printTestStep("print current line");
        inputHandler->process("p");
    }
};

class TC_DoubleCommands : public ITestCase
{
public:
    TC_DoubleCommands() : ITestCase("TC_DoubleCommands")
    {
    }
    void execute()
    {
        printTestStep("print first line");
        inputHandler->process("1p");
        printTestStep("print second line");
        inputHandler->process("2p");
        printTestStep("print third line");
        inputHandler->process("3p");
        printTestStep("print third line");
        inputHandler->process("3p");
        printTestStep("print second line");
        inputHandler->process("2p");
        printTestStep("print current line");
        inputHandler->process("p");
    }
};

class CTestSuite
{
    std::vector<ITestCase*> testcases;
    void printTestcaseStarted(std::string tcName)
    {
        cout << "\033[32m### TESTCASE " << tcName << " STARTED ###\033[0m\n";
    }
    void printTestcaseEnded()
    {
        cout << "\033[31m### TESTCASE ENDED ###\033[0m\n";
    }
public:
    void add(ITestCase* tc)
    {
        testcases.push_back(tc);
    }
    void run()
    {
        for(int i = 0; i < testcases.size(); ++i)
        {
            printTestcaseStarted(testcases[i]->getName());
            testcases[i]->setup();
            testcases[i]->execute();
            testcases[i]->teardown();
            printTestcaseEnded();
        }
    }
    CTestSuite()
    {
        for(int i = 0; i < testcases.size(); ++i)
            delete testcases[i];
    }
};

int main()
{
    CTestSuite generalTestSuite;
    generalTestSuite.add(new TC_BasicFunctionality);
    generalTestSuite.add(new TC_ToggleCurrentLine());
    generalTestSuite.add(new TC_GoBeforeTheFirstLine());
    generalTestSuite.add(new TC_DoubleCommands());
    generalTestSuite.run();
}
