#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>

class CommandLine
{
public:
	CommandLine();
	int readInputData();
	friend void writeError(std::string content);
	friend void writeOutputData(std::string nameMode, double result, double time);
private:
	const int MIN_COUNT_ELEMENTS = 100000;
	const int MAX_COUNT_ELEMENTS = 1000000;

};
