#ifndef I_COMMAND_H
#define I_COMMAND_H
#include "CStorageHandler.h"
#include <iostream>
#include <stdlib.h>

class ICommand
{
public:
    ~ICommand();
    virtual void execute(CStorageHandler* storage) = 0;;
};

class CPrintCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        storage->printCurrentLine();
    }
};

class CPrintAroundCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        storage->printAround();
    }
};

class CIncrementLineCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        storage->incrementLine();
    }
};

class CDecrementLineCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        storage->decrementLine();
    }
};

class CQuitCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        std::cout << "Bye! " << std::endl;
        exit(0);
    }
};

#endif
