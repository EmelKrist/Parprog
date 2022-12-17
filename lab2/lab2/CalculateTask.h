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
	int countThreads; // ���������� �������
	std::vector <int> arrElem; //����������������� �����
	void executionWithoutThread();
	void executionWithThreadCS();
	void executionWithThreadRV();
};


