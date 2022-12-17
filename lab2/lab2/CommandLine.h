#pragma once
#include <iostream>
#include <windows.h>

class CommandLine 
{
public:
	CommandLine();
	void startWork();
	friend void errorOutput(std::string content);
	friend void setColorCmd(int numColor);
};



	