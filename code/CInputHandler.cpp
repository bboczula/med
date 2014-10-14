#include <vector>
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
    ICommand* cmd = getCommand(commandString);
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
    CCommandMetadata* cmd = parser.parse(commandString);
    return commandFactory->getCommand(cmd);
}
