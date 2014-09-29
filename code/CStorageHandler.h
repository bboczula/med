#ifndef C_STORAGE_HANDLER_H
#define C_STORAGE_HANDLER_H
#include "CStorage.h"
#include "CLogger.h"

class CStorageHandler
{
	CStorage* storage;
	int currentLineNumber;
public:
	CStorageHandler() : currentLineNumber(0)
	{
		CLogger::getInstance()->log("CStorageHandler() created");
		storage = new CStorage("test1");
	}
	~CStorageHandler()
	{
		delete storage;
		CLogger::getInstance()->log("CStorageHandler() destroyed");
	}
    int getCurrentLineNumber()
    {
        return currentLineNumber;
    }
    int getTotalNumberOfLines()
    {
        return storage->getTotalNumberOfLines();
    }
    void printCurrentLine()
    {
        printLineAt(currentLineNumber);
    }
    void printLineAt(int lineNumber)
    {
        try
        {
            std::cout << storage->getLineAt(lineNumber) << std::endl;
        }
        catch(std::out_of_range)
        {
            std::cout << "Exception was caught, called line number was " << lineNumber << std::endl;
        }
    }
    void setCurrentLine(int newLineNumber)
    {
        currentLineNumber = newLineNumber;
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
        if(currentLineNumber > 0)
            printLineAt(currentLineNumber-1);
        if(currentLineNumber < storage->getTotalNumberOfLines())
            printLineAt(currentLineNumber);
        if(currentLineNumber + 1 < storage->getTotalNumberOfLines())
            printLineAt(currentLineNumber+1);
    };
};

#endif
