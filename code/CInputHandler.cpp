#include <vector>
#include "CInputHandler.h"
#include "CLogger.h"
#include "CExceptions.h"

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
    if(commandPosition == std::string::npos)
    {
        cout << "Something went wrong!" << endl;
    }
    else
    {
        std::string mnemonic = commandString.substr(commandPosition);
        std::string temp = commandString.substr(0, commandPosition).c_str();
        bool isModifierPresent = false;
        int modifier = 0;
        if(temp.size())
        {
            isModifierPresent = true;
            modifier = atoi(temp.c_str()) - 1;
        }
        if(mnemonic == "p" || mnemonic == ".")
        {
            if(isModifierPresent)
            {
                CCommandComposite* goToLineAndPrint = new CCommandComposite();
                goToLineAndPrint->add(new CSetCurrentLineCommand(modifier));
                goToLineAndPrint->add(new CPrintCommand());
                return goToLineAndPrint;
            }
            else
            {
                return new CPrintCommand();
            }
        }
        if(mnemonic == "n")
        {
            CCommandComposite* printWithLineNumber = new CCommandComposite();
            if(isModifierPresent)
            {
                printWithLineNumber->add(new CSetCurrentLineCommand(modifier));
            }
            printWithLineNumber->add(new CPrintLineNumberCommand());
            printWithLineNumber->add(new CPrintCommand());
            return printWithLineNumber;
        }
        if(mnemonic == "P")
        {
            return new CPrintAroundCommand();
        }
        if(mnemonic == "+")
        {
            CCommandComposite* incrementAndPrint = new CCommandComposite();
            incrementAndPrint->add(new CIncrementLineCommand());
            incrementAndPrint->add(new CPrintCommand());
            return incrementAndPrint;
        }
        if(mnemonic == "-")
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
        if(mnemonic == "1")
        {
            CCommandComposite* goToFirstLineAndPrint = new CCommandComposite();
            goToFirstLineAndPrint->add(new CFirstLineCommand());
            goToFirstLineAndPrint->add(new CPrintCommand());
            return goToFirstLineAndPrint;;
        }
        if(mnemonic == "$")
        {
            CCommandComposite* goToLastLineAndPrint = new CCommandComposite();
            goToLastLineAndPrint->add(new CLastLineCommand());
            goToLastLineAndPrint->add(new CPrintCommand());
            return goToLastLineAndPrint;
        }
        if(mnemonic == "q")
        {
            return new CQuitCommand();
        }
    }
}
