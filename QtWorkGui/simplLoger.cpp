#include "simplLoger.h"

unsigned int levelLog = 0;

simplLoger::simplLoger():
	logFileName("logFile.txt")
{
	if(!logOut.is_open())
	{
		logOut.open(logFileName, std::ios::app);
	}
}

void simplLoger::logMessege(const std::string messeg,const int logType)
{
	if (levelLog <= logType)
	{
		time_t now = time(0);
		tm* dt = localtime(&now);
		logOut <<std::to_string(LogLevel(logType))<< " " <<std::to_string(dt->tm_mday) + "." + std::to_string(dt->tm_mon) + " " + std::to_string(dt->tm_hour) + ":" + std::to_string(dt->tm_min) + ":" + std::to_string(dt->tm_sec) << "\t" << messeg << std::endl;
	}
}

void simplLoger::logInit(char* logType)
{
	if (std::string(logType) == "debug")
		levelLog = 1;
	else if (std::string(logType) == "error")
		levelLog = 2;
	else if (std::string(logType) == "info")
		levelLog = 3;
	else if (std::string(logType) == "fatal")
		levelLog = 4;
}

