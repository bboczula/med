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
    if(commandString == "P")
    {
        return new CPrintAroundCommand();
    }
    if(commandString == "+")
    {
        return new CIncrementLineCommand();
    }
    if(commandString == "-")
    {
        return new CDecrementLineCommand();
    }
    if(commandString == "q")
    {
        return new CQuitCommand();
    }
}
