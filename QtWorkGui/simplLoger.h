#pragma once
#include <ctime>
#include <fstream>
#include <string>

class simplLoger
{
	std::string logFileName;
	std::ofstream logOut;
public:
	simplLoger();
	void logMessege(std::string messeg);
};

