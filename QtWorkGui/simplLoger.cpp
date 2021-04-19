#include "simplLoger.h"

simplLoger::simplLoger():
	logFileName("logFile.txt")
{
	if(!logOut.is_open())
	{
		logOut.open(logFileName, std::ios::app);
	}
}

void simplLoger::logMessege(std::string messeg)
{
	logOut << std::to_string(clock())<<"\t"<<messeg<<std::endl;
}
