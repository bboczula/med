#include <vector>
#include <iostream>
#include "CInputHandler.h"
#include "CLogger.h"
#include "CExceptions.h"
#include "CParser.h"

CInputHandler::~CInputHandler()
{
    CLogger::getInstance()->log("CInputHandler() destroyed");
}

void CInputHandler::process(string commandString) throw(EQuit)
{
    ICommand* cmd = 0;
    try
    {
        cmd = getCommand(commandString);
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

ICommand* CInputHandler::getCommand(string commandString)
{
    CParser parser;
    CCommandMetadata* metacmd = parser.parse(commandString);
    if(!isValid(metacmd))
        throw EInvalidAddress();
    return commandFactory->getCommand(metacmd);
}

bool CInputHandler::isValid(CCommandMetadata* cmd)
{
    if(cmd->startAddress.isPresent)
        if(!storageHandler->isInRange(cmd->startAddress.value))
            return false;
    if(cmd->endAddress.isPresent)
        if(!storageHandler->isInRange(cmd->endAddress.value))
            return false;
    return true;
}
