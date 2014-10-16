#include <iostream>
#include <string>
#include <memory>
#include "CStorageHandler.h"
#include "CCommandFactory.h"
#include "CInputHandler.h"
#include "CLogger.h"
using namespace std;

string prompt()
{
	string mode("NORMAL");
	return mode + "> ";
}

void printTestStep(string cmd, string msg)
{
    cout << "\033[34m[" << cmd << "](" + msg + ")\033[0m\n";
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
        inputHandler = new CInputHandler(make_shared<CStorageHandler>(), make_shared<CCommandFactory>());
    }
    void teardown()
    {
        terminateTestcase(inputHandler);
        delete inputHandler;
    }
    void executeCommand(string cmd, string description)
    {
            printTestStep(cmd, description);
            inputHandler->process(cmd);
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
        executeCommand("1", "go to the first line");
        executeCommand("p", "print current line");
        executeCommand("+", "go to the next line");
        executeCommand("p", "print current line");
        executeCommand("$", "go to the last line");
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
        executeCommand("1", "go to the first line");
        for(int i = 0; i < 5; i++)
        {
            executeCommand("+", "go to the next line");
            executeCommand("-", "go to the previous line");
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
        executeCommand("1", "go to the first line");
        executeCommand("-", "go before the first line");
        executeCommand("-", "go before the first line");
        executeCommand("p", "print current line");
        executeCommand("+", "go to the next line");
        executeCommand("-", "go to the previous line");
        executeCommand("-", "go before the first line");
        executeCommand("p", "print current line");
    }
};

class TC_BasicDoublePrintCommand : public ITestCase
{
public:
    TC_BasicDoublePrintCommand() : ITestCase("TC_BasicDoublePrintCommand")
    {
    }
    void execute()
    {
        executeCommand("1p", "print first line");
        executeCommand("2p", "print second line");
        executeCommand("3p", "print third line");
        executeCommand("3p", "print third line");
        executeCommand("2p", "print second line");
        executeCommand("p", "print current line");
    }
};

class TC_BasicDoublePrintWithNumberCommand : public ITestCase
{
public:
    TC_BasicDoublePrintWithNumberCommand() : ITestCase("TC_BasicDoublePrintWithNumberCommand")
    {
    }
    void execute()
    {
        executeCommand("1n", "print first line");
        executeCommand("2n", "print second line");
        executeCommand("3n", "print third line");
        executeCommand("3n", "print third line");
        executeCommand("2n", "print second line");
        executeCommand("n", "print current line");
    }
};

class TC_MovingOnlyWithNumbers : public ITestCase
{
public:
    TC_MovingOnlyWithNumbers() : ITestCase("TC_MovingOnlyWithNumbers")
    {
    }
    void execute()
    {
        executeCommand("1", "print first line");
        executeCommand("2", "print second line");
        executeCommand("3", "print third line");
        executeCommand("4", "print third line");
        executeCommand("5", "print third line");
    }
};

class TC_BasicRangePrinting : public ITestCase
{
public:
    TC_BasicRangePrinting() : ITestCase("TC_BasicRangePrinting")
    {
    }
    void execute()
    {
        executeCommand("1,1", "print first line");
        executeCommand("1,3", "print firts three lines");
        executeCommand("1,6p", "print entire file");
        executeCommand("4,6p", "print last three lines");
        executeCommand("p", "print current line");
    }
};

class TC_InvalidRangePrinting : public ITestCase
{
public:
    TC_InvalidRangePrinting() : ITestCase("TC_InvalidRangePrinting")
    {
    }
    void execute()
    {
        executeCommand("1,1", "print first line");
        executeCommand("1,6", "print entire file");
        executeCommand("1,7p", "second parameter out of range");
        executeCommand("8,9p", "both parameters out of range");
        executeCommand("0", "trying to print line 0");
        executeCommand("10", "trying to print non-exiting line");
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
    generalTestSuite.add(new TC_BasicDoublePrintCommand());
    generalTestSuite.add(new TC_BasicDoublePrintWithNumberCommand());
    generalTestSuite.add(new TC_MovingOnlyWithNumbers());
    generalTestSuite.add(new TC_BasicRangePrinting());
    generalTestSuite.add(new TC_InvalidRangePrinting());
    generalTestSuite.run();
}
