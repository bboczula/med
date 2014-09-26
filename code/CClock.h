#ifndef CCLOCK_H
#define CCLOCK_H
#include <stdio.h>
#include <time.h>
#include <string>

class CClock
{
	static CClock* instance;
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	CClock()
	{
	}
	CClock(const CClock&);
	CClock& operator=(const CClock&);
public:
	static CClock* getInstance()
	{
		if(!instance)
			instance = new CClock;
		return instance;
	}
	std::string getTimestamp()
	{
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "<%d.%m-%X>", timeinfo);
		return std::string(buffer);
	}
};

CClock* CClock::instance = nullptr;

#endif
