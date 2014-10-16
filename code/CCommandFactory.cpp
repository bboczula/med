#include "CCommandFactory.h"

ICommand* CCommandFactory::getCommand(CCommandMetadata* metadata)
{
    if(metadata->command.value == "p" || metadata->command.value == ".")
    {
        if(metadata->startAddress.isPresent)
        {
            if(metadata->endAddress.isPresent)
            {
                return new CPrintRangeCommand(metadata->startAddress.value, metadata->endAddress.value);
            }
            else
            {
                return new CPrintRangeCommand(metadata->startAddress.value, metadata->startAddress.value);
            }
        }
        else
        {
            return new CPrintCommand();
        }
    }
    if(metadata->command.value == "n")
    {
        CCommandComposite* printWithLineNumber = new CCommandComposite();
        if(metadata->startAddress.isPresent)
        {
            printWithLineNumber->add(new CSetCurrentLineCommand(metadata->startAddress.value));
        }
        printWithLineNumber->add(new CPrintLineNumberCommand());
        printWithLineNumber->add(new CPrintCommand());
        return printWithLineNumber;
    }
    if(metadata->command.value == "P")
    {
        return new CPrintAroundCommand();
    }
    if(metadata->command.value == "+")
    {
        CCommandComposite* incrementAndPrint = new CCommandComposite();
        incrementAndPrint->add(new CIncrementLineCommand());
        incrementAndPrint->add(new CPrintCommand());
        return incrementAndPrint;
    }
    if(metadata->command.value == "-")
    {
        CCommandComposite* decrementAndPrint = new CCommandComposite();
        try
        {
            decrementAndPrint->add(new CDecrementLineCommand());
        }
        catch(ETryToMoveOutOfFile)
        {
            std::cout << "?" << std::endl;
            return 0;
        }
        decrementAndPrint->add(new CPrintCommand());
        return decrementAndPrint;
    }
    if(metadata->command.value == "$")
    {
        CCommandComposite* goToLastLineAndPrint = new CCommandComposite();
        goToLastLineAndPrint->add(new CLastLineCommand());
        goToLastLineAndPrint->add(new CPrintCommand());
        return goToLastLineAndPrint;
    }
    if(metadata->command.value == "q")
    {
        return new CQuitCommand();
    }
}
