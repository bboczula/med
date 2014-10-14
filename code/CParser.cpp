#include "CParser.h"
#include <string>
#include <iostream>

CCommandMetadata* CParser::parse(std::string commandString)
{
    std::size_t commandPosition = commandString.find_first_of("pnP.+-$q");

    CCommandMetadata* cmd = new CCommandMetadata();
    if(commandPosition == std::string::npos)
    {
        cmd->command.isPresent = true;
        cmd->command.value = "p";
    }
    else
    {
        cmd->command.isPresent = true;
        cmd->command.value = commandString.substr(commandPosition);
    }

    std::string temp = commandString.substr(0, commandPosition).c_str();
    if(temp.size())
    {
        std::size_t commaPosition = temp.find(",");
        if(commaPosition != std::string::npos)
        {
            std::string tempEndAddress = temp.substr(commaPosition + 1, temp.length());
            cmd->endAddress.isPresent = true;
            cmd->endAddress.value = atoi(tempEndAddress.c_str()) - 1;
        }
        cmd->startAddress.isPresent = true;
        cmd->startAddress.value = atoi(temp.c_str()) - 1;
    }

    return cmd;
}
