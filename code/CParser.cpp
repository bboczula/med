#include "CParser.h"
#include <string>
#include <iostream>

CCommandMetadata* CParser::parse(std::string commandString)
{
    std::size_t commandPosition = commandString.find_first_of("pnP.+-$q");

    CCommandMetadata* cmd = new CCommandMetadata();
    if(commandPosition == std::string::npos)
    {
        cmd->command.setValue("p");
    }
    else
    {
        cmd->command.setValue(commandString.substr(commandPosition));
    }

    std::string temp = commandString.substr(0, commandPosition).c_str();
    if(temp.size())
    {
        std::size_t commaPosition = temp.find(",");
        if(commaPosition != std::string::npos)
        {
            std::string tempStartAddress = temp.substr(0, commaPosition);
            std::string tempEndAddress = temp.substr(commaPosition + 1, temp.length());

            if(tempStartAddress.size())
                cmd->startAddress.setValue(atoi(tempStartAddress.c_str()) - 1);

            if(tempEndAddress.size())
                cmd->endAddress.setValue(atoi(tempEndAddress.c_str()) - 1);
        }
        else
        {
            cmd->startAddress.setValue(atoi(temp.c_str()) - 1);
        }
    }

    return cmd;
}
