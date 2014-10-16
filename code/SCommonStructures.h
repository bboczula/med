#ifndef C_COMMON_STRUCTURES_H
#define C_COMMON_STRUCTURES_H
#include <string>

template<typename T>
class TOptional
{
public:
    bool isPresent;
    T value;
    void setValue(T newValue)
    {
        isPresent = true;
        value = newValue;
    }
};

class CCommandMetadata
{
public:
    CCommandMetadata()
    {
        startAddress.isPresent = false;
        endAddress.isPresent = false;
        command.isPresent = false;
        parameters.isPresent = false;
    }
    TOptional<int> startAddress;
    TOptional<int> endAddress;
    TOptional<std::string> command;
    TOptional<std::string> parameters;;
};

#endif
