#include "CalculateTask.h"
#include "WorkTask.h"

/// <summary>Конструктор класса CalculateTask.</summary>
/// <param name="arr">Последовательность чисел</param>
/// <param name="countTh">Количество потоков</param>
CalculateTask::CalculateTask(std::vector <int> arr, int countTh): arrElem(arr), countThreads(countTh)
{
	// Запускаем режимы вычислений
	executionWithoutThread(); 
	executionWithThreadCS();
	executionWithThreadRV();
}


/// <summary>Метод для однопоточного вычисления.</summary>
void CalculateTask::executionWithoutThread() 
{
	double result = 0;
	
	double time = omp_get_wtime(); // старт таймера
	for (int i = 0; i < arrElem.size(); i++) {
		result += sqrt(arrElem[i]);
	}
	time = omp_get_wtime() - time; // Получаем время
	// Выводим результ и время выполнения
	writeOutputData("Выполнение в однопоточном режиме.", result, time);
}


/// <summary>Метод для многопоточного вычисления с использованием критической секции.</summary>
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
	
	writeOutputData("Выполнение в многопоточном режиме(критическая секция).", result, time);
}


/// <summary>Метод для многопоточного вычисления с использованием редуктивной переменной.</summary>
void CalculateTask::executionWithThreadRV()
{
	double result = 0;
    
	double time = omp_get_wtime();
	#pragma omp parallel for reduction (+:result)	
	for (int i = 0; i < arrElem.size(); i++) {
		result += sqrt(arrElem[i]);
	}
	time = omp_get_wtime() - time;
	
	writeOutputData("Выполнение в многопоточном режиме(редуктивная переменная).", result, time);
}



