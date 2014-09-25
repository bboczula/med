#include <vector>
#include "CInputHandler.h"

CInputHandler::~CInputHandler()
{
    if(!storageHandler)
        delete storageHandler;
}

bool CInputHandler::process(string commandString)
{
    ICommand* cmd = getCommand(commandString);
    if(cmd)
        cmd->execute(storageHandler);
    return false;
}

ICommand* CInputHandler::getCommand(string commandString)
{
    if(commandString == "p")
    {
        return new CPrintCommand();
    }
    if(commandString == "pp")
    {
        CCommandComposite* doublePrint = new CCommandComposite();
        doublePrint->add(new CPrintCommand());
        doublePrint->add(new CIncrementLineCommand());
        doublePrint->add(new CPrintCommand());
        return doublePrint;;
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
        return new CDecrementLineCommand();
    }
    if(commandString == "1")
    {
        return new CFirstLineCommand();
    }
    if(commandString == "$")
    {
        return new CLastLineCommand();
    }
    if(commandString == "q")
    {
        return new CQuitCommand();
    }
}
