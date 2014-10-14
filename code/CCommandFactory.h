#ifndef C_COMMAND_FACTORY_H
#define C_COMMAND_FACTORY_H
#include "ICommand.h"
#include "SCommonStructures.h"
class CCommandFactory
{
public:
    ICommand* getCommand(CCommandMetadata* metadata);
};
#endif
