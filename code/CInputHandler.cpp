#include <vector>
#include <iostream>
#include "CInputHandler.h"
#include "CLogger.h"
#include "CExceptions.h"
#include "CParser.h"

CInputHandler::CInputHandler(const shared_ptr<CStorageHandler>& sh, shared_ptr<CCommandFactory> cf) : storageHandler(sh), commandFactory(cf), currentErrorMsg("")
{
    CLogger::getInstance()->log("CInputHandler() created");
}

CInputHandler::~CInputHandler()
{
    CLogger::getInstance()->log("CInputHandler() destroyed");
}

void CInputHandler::process(string command) throw(EQuit)
{
    ICommand* cmd = 0;
    try
    {
        cmd = getCommand(command);
    }
    catch(EInvalidAddress e)
    {
        std::cout << "?" << std::endl;
        return;
    }

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

ICommand* CInputHandler::getCommand(string command)
{
    CParser parser;
    CCommandMetadata* metacmd = parser.parse(command);
    if(!isValid(metacmd))
    {
        throw EInvalidAddress();
        return 0;
    }
    return commandFactory->getCommand(metacmd);
}

bool CInputHandler::isValid(CCommandMetadata* metacmd)
{
    if(metacmd->startAddress.isPresent)
        if(!storageHandler->isInRange(metacmd->startAddress.value))
            return false;
    if(metacmd->endAddress.isPresent)
        if(!storageHandler->isInRange(metacmd->endAddress.value))
            return false;
    return true;
}
