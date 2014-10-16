#ifndef C_PARSER_H
#define C_PARSER_H
#include <string>
#include "SCommonStructures.h"

class CParser
{
    void fillCommand(CCommandMetadata* metacmd, std::size_t commandPosition, std::string commandString);
    void fillAddress(CCommandMetadata* metacmd, std::string rawAddressString);
public:
    CParser()
    {
    }
    CCommandMetadata* parse(std::string commandString);
};

#endif
