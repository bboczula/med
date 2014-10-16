#ifndef C_PARSER_H
#define C_PARSER_H
#include <string>
#include "SCommonStructures.h"

class CParser
{
    const std::string COMMAND_LIST = "pnP.+-$q";
    void fillCommand(CCommandMetadata* metacmd, std::string rawCommand);
    void fillAddress(CCommandMetadata* metacmd, std::string rawAddressString);
    std::pair<std::string, std::string> splitCommandAndAddress(std::string rawString);
public:
    CParser()
    {
    }
    CCommandMetadata* parse(std::string commandString);
};

#endif
