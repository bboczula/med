#include <vector>
#include "CInputHandler.h"

CInputHandler::~CInputHandler()
{
    if(!storageHandler)
        delete storageHandler;
}

vector<ECommandType> CInputHandler::translateCommand(string commandString)
{
    vector<ECommandType> commands;
    if(commandString == "p")
    {
        commands.push_back(PRINT);
    }
    if(commandString == "+")
    {
        commands.push_back(INCR_LINE);
    }
    if(commandString == "-")
    {
        commands.push_back(DECR_LINE);
    }
    if(commandString == "q")
    {
        commands.push_back(QUIT);
    }
    if(commandString == "pp")
    {
        commands.push_back(PRINT);
        commands.push_back(INCR_LINE);
        commands.push_back(PRINT);
    }

    return commands;
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
