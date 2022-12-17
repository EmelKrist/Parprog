#pragma once
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <omp.h>
#include <conio.h>
#include <vector>

class CalculateTask {
public:
	CalculateTask(std::vector <int> arr, int countTh);
private:
	int countThreads; // Количество потоков
	std::vector <int> arrElem; //Посдеовательность чисел
	void executionWithoutThread();
	void executionWithThreadCS();
	void executionWithThreadRV();
};


