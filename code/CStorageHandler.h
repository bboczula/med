#ifndef C_STORAGE_HANDLER_H
#define C_STORAGE_HANDLER_H
#include "CStorage.h"

class CStorageHandler
{
    CStorage* storage;
    int currentLineNumber;
public:
    CStorageHandler()
    {
        currentLineNumber = 0;
        storage = new CStorage("main.cpp");
    }
    ~CStorageHandler()
    {
        delete storage;
    }
    void printCurrentLine()
    {
        printLineAt(currentLineNumber);
    }
    void printLineAt(int lineNumber)
    {
        cout << storage->getLineAt(lineNumber) << endl;
    }
    void incrementLine()
    {
        currentLineNumber++;
    }
    void decrementLine()
    {
        currentLineNumber--;
    }
    void printAround()
    {
        printLineAt(currentLineNumber-1);
        printLineAt(currentLineNumber);
        printLineAt(currentLineNumber+1);
    };
};

#endif
