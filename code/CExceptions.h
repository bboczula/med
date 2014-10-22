#ifndef E_QUIT_H
#define E_QUIT_H

class CExceptionBase
{
    virtual std::string getMessage() = 0;
};

class EQuit : CExceptionBase
{
    virtual std::string getMessage()
    {
        return "Quit";
    }
};

class ETryToMoveOutOfFile : CExceptionBase
{
    virtual std::string getMessage()
    {
        return "Invalid address";
    }
};

class EInvalidAddress : CExceptionBase
{
    virtual std::string getMessage()
    {
        return "Invalid address";
    }
};

#endif
