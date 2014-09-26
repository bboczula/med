#ifndef CLOGGER_H
#define CLOGGER_H
#include <iostream>

class CLogger
{
    static CLogger* instance;
    CLogger()
    {
    }
    CLogger(const CLogger&);
    CLogger& operator=(const CLogger&);
public:
    static CLogger* getInstance()
    {
        std::cout << "instance" << std::endl;
    }
    void log()
    {
        std::cout << "test" << std::endl;
    }
};

CLogger* CLogger::instance = nullptr;

#endif
