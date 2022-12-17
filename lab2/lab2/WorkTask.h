#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class WorkTask {
public:
	WorkTask();
private:
	const int MIN_COUNT_ELEMENTS = 100000; 
	const int MAX_COUNT_ELEMENTS = 1000000;
	int countElements; 
	int countThreads;
	std::vector <int> arrElem;
	void readInputData();
	int readElementsFromConsole();
	int readThreadsFromConsole();
	friend void writeOutputData(std::string name, int result, double time);
	void initArrayRandomData();
};


