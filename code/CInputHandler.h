#ifndef C_INPUT_HANDLER_H
#define C_INPUT_HANDLER_H
#include "CStorageHandler.h"
#include "ICommand.h"
#include <memory>
#include "CLogger.h"
#include "CExceptions.h"
using namespace std;

class CInputHandler
{
    shared_ptr<CStorageHandler> storageHandler;
    ICommand* getCommand(string commandString);
public:
    CInputHandler(const shared_ptr<CStorageHandler>& s) : storageHandler(s)
    {
        CLogger::getInstance()->log("CInputHandler() created");
    }
    ~CInputHandler();
    void process(string commandString) throw(EQuit);
};

#endif
