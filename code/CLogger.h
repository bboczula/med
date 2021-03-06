#ifndef CLOGGER_H
#define CLOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include "CClock.h"

class CLogger
{
    std::ofstream logFile;
    static CLogger* instance;
    CLogger()
    {
        logFile.open("med.log");
        logFile << "CLogger() created" << std::endl;
        logFile.close();
    }
    CLogger(const CLogger&);
    CLogger& operator=(const CLogger&);
public:
    static CLogger* getInstance()
    {
        if(!instance)
            instance = new CLogger();
        return instance;
    }
    void log(std::string message)
    {
        logFile.open("med.log", std::ios::app);
        logFile << CClock::getInstance()->getTimestamp() << " " << message << std::endl;
        logFile.close();
    }
};

#endif
