#ifndef C_INPUT_HANDLER_H
#define C_INPUT_HANDLER_H
#include "CStorageHandler.h"
#include "ICommand.h"
using namespace std;

enum ECommandType
{
    PRINT, INCR_LINE, DECR_LINE, QUIT
};

class CInputHandler
{
    CStorageHandler* storageHandler;
    vector<ECommandType> translateCommand(string commandString)
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
    ICommand* printCommand;
public:
    CInputHandler(CStorageHandler* s) : storageHandler(s)
    {
    }
    ~CInputHandler()
    {
        if(!storageHandler)
            delete storageHandler;
    }
    bool process(string commandString)
    {
        ICommand* cmd = getCommand(commandString);
        if(cmd)
            cmd->execute(storageHandler);
        return false;
    }
    ICommand* getCommand(string commandString)
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
};

#endif
