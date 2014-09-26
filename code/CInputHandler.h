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
    ICommand* printCommand;
public:
    CInputHandler(CStorageHandler* s) : storageHandler(s)
    {
    }
    ~CInputHandler();
    void process(string commandString);
    ICommand* getCommand(string commandString);
};

#endif
