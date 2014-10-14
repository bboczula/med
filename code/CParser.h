#ifndef C_PARSER_H
#define C_PARSER_H
#include <string>
#include "SCommonStructures.h"

class CParser
{
public:
    CParser()
    {
    }
    CCommandMetadata* parse(std::string commandString);
};

#endif
