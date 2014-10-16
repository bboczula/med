#include "CParser.h"
#include <string>
#include <iostream>
#include <utility>

void CParser::fillCommand(CCommandMetadata* metacmd, std::string rawCommand)
{
    if(rawCommand.empty())
    {
        metacmd->command.setValue("p");
    }
    else
    {
        metacmd->command.setValue(rawCommand);
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

std::pair<std::string, std::string> CParser::splitCommandAndAddress(std::string rawString)
{
    std::string rawCommand { };
    std::string rawAddress { rawString };

    std::size_t commandPosition = rawString.find_first_of(COMMAND_LIST);
    if(commandPosition != std::string::npos)
    {
        rawCommand = rawString.substr(commandPosition);
        rawAddress = rawString.substr(0, commandPosition);
    }

    return make_pair(rawCommand, rawAddress);
}

CCommandMetadata* CParser::parse(std::string command)
{
    if(command.empty())
        return 0;

    std::pair<std::string, std::string> commandAndAddress = splitCommandAndAddress(command);

    CCommandMetadata* cmd = new CCommandMetadata();
    fillCommand(cmd, commandAndAddress.first);
    fillAddress(cmd, commandAndAddress.second);;

    return cmd;
}
