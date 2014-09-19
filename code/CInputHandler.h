#ifndef C_INPUT_HANDLER_H
#define C_INPUT_HANDLER_H
#include "CStorageHandler.h"
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
        vector<ECommandType> c = translateCommand(commandString);
        for(int i = 0; i < c.size(); i++)
        {
            if(c[i] == PRINT)
            {
                storageHandler->printCurrentLine();
            }
            if(c[i] == INCR_LINE)
            {
                storageHandler->incrementLine();
            }
            if(c[i] == DECR_LINE)
            {
                storageHandler->decrementLine();
            }
            if(c[i] == QUIT)
            {
                cout << "Goodbye!" << endl;
                return true;
            }
        }
        return false;
    }
};

#endif
