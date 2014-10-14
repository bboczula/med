#include <vector>
#include "CInputHandler.h"
#include "CLogger.h"
#include "CExceptions.h"
#include "CParser.h"

CInputHandler::~CInputHandler()
{
    CLogger::getInstance()->log("CInputHandler() destroyed");
}

void CInputHandler::process(string commandString) throw(EQuit)
{
    ICommand* cmd = getCommand(commandString);
    if(cmd)
    {
        try
        {
            cmd->execute(storageHandler);
        }
        catch(EQuit e)
        {
            throw EQuit();
        }
    }
}

ICommand* CInputHandler::getCommand(string commandString)
{
    std::size_t commandPosition = commandString.find_first_of("p.nP+-$q");
    CParser parser;
    CCommandMetadata* cmd = parser.parse(commandString);

    if(cmd->command.value == "p" || cmd->command.value == ".")
    {
        if(cmd->startAddress.isPresent)
        {
            CCommandComposite* goToLineAndPrint = new CCommandComposite();
            goToLineAndPrint->add(new CSetCurrentLineCommand(cmd->startAddress.value));
            goToLineAndPrint->add(new CPrintCommand());
            return goToLineAndPrint;
        }
        else
        {
            return new CPrintCommand();
        }
    }
    if(cmd->command.value == "n")
    {
        CCommandComposite* printWithLineNumber = new CCommandComposite();
        if(cmd->startAddress.isPresent)
        {
            printWithLineNumber->add(new CSetCurrentLineCommand(cmd->startAddress.value));
        }
        printWithLineNumber->add(new CPrintLineNumberCommand());
        printWithLineNumber->add(new CPrintCommand());
        return printWithLineNumber;
    }
    if(cmd->command.value == "P")
    {
        return new CPrintAroundCommand();
    }
    if(cmd->command.value == "+")
    {
        CCommandComposite* incrementAndPrint = new CCommandComposite();
        incrementAndPrint->add(new CIncrementLineCommand());
        incrementAndPrint->add(new CPrintCommand());
        return incrementAndPrint;
    }
    if(cmd->command.value == "-")
    {
        CCommandComposite* decrementAndPrint = new CCommandComposite();
        try
        {
            decrementAndPrint->add(new CDecrementLineCommand(storageHandler));
        }
        catch(ETryToMoveOutOfFile)
        {
            cout << "?" << endl;
            return 0;
        }
        decrementAndPrint->add(new CPrintCommand());
        return decrementAndPrint;
    }
    if(cmd->command.value == "1")
    {
        CCommandComposite* goToFirstLineAndPrint = new CCommandComposite();
        goToFirstLineAndPrint->add(new CFirstLineCommand());
        goToFirstLineAndPrint->add(new CPrintCommand());
        return goToFirstLineAndPrint;;
    }
    if(cmd->command.value == "$")
    {
        CCommandComposite* goToLastLineAndPrint = new CCommandComposite();
        goToLastLineAndPrint->add(new CLastLineCommand());
        goToLastLineAndPrint->add(new CPrintCommand());
        return goToLastLineAndPrint;
    }
    if(cmd->command.value == "q")
    {
        return new CQuitCommand();
    }
}
