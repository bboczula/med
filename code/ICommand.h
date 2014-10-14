#ifndef I_COMMAND_H
#define I_COMMAND_H
#include "CStorageHandler.h"
#include "CExceptions.h"
#include <iostream>
#include <memory>
#include <stdlib.h>

struct CLineAddress
{
    bool isPresent;
    int address;
};

class ICommand
{
    CLineAddress address;
public:
    ICommand()
    {
        address.isPresent = false;
        address.address = 0;
    }
    ICommand(int lineAddress)
    {
        address.isPresent = true;
        address.address = lineAddress;
    }
    ~ICommand() 
    {
    }
    virtual void execute(std::shared_ptr<CStorageHandler> storage) = 0;
};

class CPrintCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        storage->printCurrentLine();
    }
};

class CPrintRangeCommand : public ICommand
{
    int startRange;
    int endRange;
public:
    CPrintRangeCommand(int start, int end) : startRange(start), endRange(end)
    {
    }
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        for(int i = startRange; i <= endRange; i++)
        {
            storage->setCurrentLine(i);
            storage->printCurrentLine();
        }
    }
};

class CPrintLineNumberCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        std::cout << storage->getCurrentLineNumber() + 1 << " ";
    }
};

class CPrintAroundCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        storage->printAround();
    }
};

class CFirstLineCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        storage->setCurrentLine(0);
    }
};

class CLastLineCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        storage->setCurrentLine(storage->getTotalNumberOfLines()-1);
    }
};

class CSetCurrentLineCommand : public ICommand
{
    int newLine;
public:
    CSetCurrentLineCommand(int i) :  newLine(i)
    {
    }
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        storage->setCurrentLine(newLine);
    }
};

class CIncrementLineCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        storage->incrementLine();
    }
};

class CDecrementLineCommand : public ICommand
{
public:
    CDecrementLineCommand(std::shared_ptr<CStorageHandler> storage) throw (ETryToMoveOutOfFile)
    {
        if(storage->getCurrentLineNumber() == 0)
            throw ETryToMoveOutOfFile();
    }
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        storage->decrementLine();
    }
};

class CQuitCommand : public ICommand
{
public:
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        throw EQuit();
    }
};

class CCommandComposite : public ICommand
{
    typedef std::vector<ICommand*> TContainer;
    TContainer children;
public:
    CCommandComposite()
    {
    }
    void add(ICommand* cmd)
    {
        children.push_back(cmd);
    }
    virtual void execute(std::shared_ptr<CStorageHandler> storage)
    {
        for(TContainer::iterator it = children.begin(); it != children.end(); it++)
        {
            (*it)->execute(storage);
        }
    }
};

#endif
