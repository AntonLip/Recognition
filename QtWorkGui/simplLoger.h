#pragma once
#include <ctime>
#include <fstream>
#include <string>

extern unsigned int levelLog;

enum LogLevel
{
	_DEBUG_ = 1,
	_ERROR_ = 2,
	_INFO_ = 3,
	_FATAL_ = 4
};

class simplLoger
{
	std::string logFileName;
	std::ofstream logOut;
public:
	simplLoger();
	void logMessege(const std::string messeg,const int logType);//logType 1-
	void logInit(char* levelLog);
};

