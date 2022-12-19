#pragma once
#include <ctime> 
#include <iostream>
#include "mpi.h"
#include "CommandLine.h"

class MpiexecTask {
public:
	MpiexecTask();
	void run();
private:
	MPI_Status status;
	int numbThread, countThreads, countElements;
	double time;
	double* initArrayRandomData();
	void executionWithoutThread(double* arrElem);
	void executionWithRootThread(double* arrElem);
	void executionWithOtherThreads();
	double calcPartElemThread(double *arrElem, int arrLength);
};
