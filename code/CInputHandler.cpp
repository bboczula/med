#include <vector>
#include "CInputHandler.h"
#include "CLogger.h"
#include "CExceptions.h"

CInputHandler::~CInputHandler()
{
    CLogger::getInstance()->log("CInputHandler() destroyed");
}

void CInputHandler::process(string commandString) throw(EQuit)
{
    ICommand* cmd = getCommand(commandString);
    if(cmd)
    {
        try
        {
            cmd->execute(storageHandler);
        }
        catch(EQuit e)
        {
            throw EQuit();
        }
    }
}

ICommand* CInputHandler::getCommand(string commandString)
{
    if(commandString.size() == 1)
    {
        if(commandString == "p" || commandString == ".")
        {
            return new CPrintCommand();
        }
        if(commandString == "n")
        {
            CCommandComposite* printWithLineNumber = new CCommandComposite();
            printWithLineNumber->add(new CPrintLineNumberCommand());
            printWithLineNumber->add(new CPrintCommand());
            return printWithLineNumber;
        }
        if(commandString == "P")
        {
            return new CPrintAroundCommand();
        }
        if(commandString == "+")
        {
            CCommandComposite* incrementAndPrint = new CCommandComposite();
            incrementAndPrint->add(new CIncrementLineCommand());
            incrementAndPrint->add(new CPrintCommand());
            return incrementAndPrint;
        }
        if(commandString == "-")
        {
            CCommandComposite* decrementAndPrint = new CCommandComposite();
            decrementAndPrint->add(new CDecrementLineCommand());
            decrementAndPrint->add(new CPrintCommand());
            return decrementAndPrint;
        }
        if(commandString == "1")
        {
            CCommandComposite* goToFirstLineAndPrint = new CCommandComposite();
            goToFirstLineAndPrint->add(new CFirstLineCommand());
            goToFirstLineAndPrint->add(new CPrintCommand());
            return goToFirstLineAndPrint;;
        }
        if(commandString == "$")
        {
            CCommandComposite* goToLastLineAndPrint = new CCommandComposite();
            goToLastLineAndPrint->add(new CLastLineCommand());
            goToLastLineAndPrint->add(new CPrintCommand());
            return goToLastLineAndPrint;
        }
        if(commandString == "q")
        {
            return new CQuitCommand();
        }
    }
    else if(commandString.size() == 2)
    {
        if(commandString == "pp")
        {
            CCommandComposite* doublePrint = new CCommandComposite();
            doublePrint->add(new CPrintCommand());
            doublePrint->add(new CIncrementLineCommand());
            doublePrint->add(new CPrintCommand());
            return doublePrint;;
        }
    }
}
