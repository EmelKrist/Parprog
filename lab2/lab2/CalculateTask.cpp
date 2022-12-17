#include "CalculateTask.h"
#include "WorkTask.h"

/// <summary>����������� ������ CalculateTask.</summary>
/// <param name="arr">������������������ �����</param>
/// <param name="countTh">���������� �������</param>
CalculateTask::CalculateTask(std::vector <int> arr, int countTh): arrElem(arr), countThreads(countTh)
{
	// ��������� ������ ����������
	executionWithoutThread(); 
	executionWithThreadCS();
	executionWithThreadRV();
}


/// <summary>����� ��� ������������� ����������.</summary>
void CalculateTask::executionWithoutThread() 
{
	double result = 0;
	
	double time = omp_get_wtime(); // ����� �������
	for (int i = 0; i < arrElem.size(); i++) {
		result += sqrt(arrElem[i]);
	}
	time = omp_get_wtime() - time; // �������� �����
	// ������� ������� � ����� ����������
	writeOutputData("���������� � ������������ ������.", result, time);
}


/// <summary>����� ��� �������������� ���������� � �������������� ����������� ������.</summary>
void CalculateTask::executionWithThreadCS()
{
	double result = 0;
    double pResult = 0;
	
	double time = omp_get_wtime();
	omp_set_dynamic(false);
	omp_set_num_threads(countThreads);
	#pragma omp parallel firstprivate(pResult) shared(result) 
	{
		pResult = 0;
		#pragma omp for
		for (int i = 0; i < arrElem.size(); i++) {
			pResult += sqrt(arrElem[i]);
		}
		#pragma omp critical
		{
			result += pResult;
		}
	}
	time = omp_get_wtime() - time;
	
	writeOutputData("���������� � ������������� ������(����������� ������).", result, time);
}


/// <summary>����� ��� �������������� ���������� � �������������� ����������� ����������.</summary>
void CalculateTask::executionWithThreadRV()
{
	double result = 0;
    
	double time = omp_get_wtime();
	#pragma omp parallel for reduction (+:result)	
	for (int i = 0; i < arrElem.size(); i++) {
		result += sqrt(arrElem[i]);
	}
	time = omp_get_wtime() - time;
	
	writeOutputData("���������� � ������������� ������(����������� ����������).", result, time);
}



