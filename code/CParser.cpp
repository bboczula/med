#include "CParser.h"
#include <string>
#include <iostream>

void CParser::fillCommand(CCommandMetadata* metacmd, std::size_t commandPosition, std::string commandString)
{
    if(commandPosition == std::string::npos)
    {
        metacmd->command.setValue("p");
    }
    else
    {
        metacmd->command.setValue(commandString.substr(commandPosition));
    }
}

void CParser::fillAddress(CCommandMetadata* metacmd, std::string rawAddressString)
{
    if(rawAddressString.empty())
        return;

    std::size_t commaPosition = rawAddressString.find(",");
    if(commaPosition != std::string::npos)
    {
        std::string tempStartAddress = rawAddressString.substr(0, commaPosition);
        std::string tempEndAddress = rawAddressString.substr(commaPosition + 1, rawAddressString.length());

        if(!tempStartAddress.empty())
            metacmd->startAddress.setValue(atoi(tempStartAddress.c_str()) - 1);

        if(!tempEndAddress.empty())
            metacmd->endAddress.setValue(atoi(tempEndAddress.c_str()) - 1);
    }
    else
    {
        metacmd->startAddress.setValue(atoi(rawAddressString.c_str()) - 1);
    }
}

CCommandMetadata* CParser::parse(std::string command)
{
    if(command.empty())
        return 0;

    std::size_t commandPosition = command.find_first_of("pnP.+-$q");

    CCommandMetadata* cmd = new CCommandMetadata();
    fillCommand(cmd, commandPosition, command);
    fillAddress(cmd, command.substr(0, commandPosition).c_str());

    return cmd;
}
