#ifndef I_COMMAND_H
#define I_COMMAND_H
#include "CStorage.h"

class ICommand
{
public:
    ~ICommand();
    virtual void execute(CStorage& storage) = 0;;
};

class CPrintCommand : public ICommand
{
public:
    virtual void execute(CStorage& storage)
    {
    }
};

class CIncrementLineCommand : public ICommand
{
public:
    virtual void execute(CStorage& storage)
    {
    }
};

class CDecrementLineCommand : public ICommand
{
public:
    virtual void execute(CStorage& storage)
    {
    }
};

class CQuitCommand : public ICommand
{
public:
    virtual void execute(CStorage& storage)
    {
    }
};

#endif
