#ifndef C_INPUT_HANDLER_H
#define C_INPUT_HANDLER_H
#include "CStorageHandler.h"
#include "CCommandFactory.h"
#include "ICommand.h"
#include <memory>
#include "CLogger.h"
#include "CExceptions.h"
using namespace std;

class CInputHandler
{
    shared_ptr<CStorageHandler> storageHandler;
    shared_ptr<CCommandFactory> commandFactory;
    ICommand* getCommand(string command);
    bool isValid(CCommandMetadata* metacmd);
public:
    CInputHandler(const shared_ptr<CStorageHandler>& sh, shared_ptr<CCommandFactory> cf);
    ~CInputHandler();
    void process(string command) throw(EQuit);
};

#endif
