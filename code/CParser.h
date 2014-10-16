#ifndef C_PARSER_H
#define C_PARSER_H
#include <string>
#include "SCommonStructures.h"

class CParser
{
    void fillCommand(CCommandMetadata* metacmd, std::string rawCommand);
    void fillAddress(CCommandMetadata* metacmd, std::string rawAddressString);
public:
    CParser()
    {
    }
    CCommandMetadata* parse(std::string commandString);
};

#endif
