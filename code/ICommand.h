#ifndef I_COMMAND_H
#define I_COMMAND_H
#include "CStorageHandler.h"
#include <iostream>
#include <stdlib.h>

class ICommand
{
public:
    ~ICommand()
    {
    }
    virtual void execute(CStorageHandler* storage) = 0;
};

class CPrintCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        storage->printCurrentLine();
    }
};

class CPrintLineNumberCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        std::cout << storage->getCurrentLineNumber() + 1 << " ";
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

class CFirstLineCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        storage->setCurrentLine(0);
    }
};

class CLastLineCommand : public ICommand
{
public:
    virtual void execute(CStorageHandler* storage)
    {
        storage->setCurrentLine(storage->getTotalNumberOfLines()-1);
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

class CCommandComposite : public ICommand
{
    vector<ICommand*> children;
public:
    CCommandComposite()
    {
    }
    void add(ICommand* cmd)
    {
        children.push_back(cmd);
    }
    virtual void execute(CStorageHandler* storage)
    {
        for(int i = 0; i < children.size(); i++)
        {
            children[i]->execute(storage);
        }
    }
};

#endif
