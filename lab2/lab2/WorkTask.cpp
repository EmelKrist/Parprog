#include "WorkTask.h"
#include "CalculateTask.h"
#include "CommandLine.h"

/// <summary>Конструктор класса WorkTask.</summary>
WorkTask::WorkTask()
{
	readInputData(); // Читаем входные данные
	initArrayRandomData(); // Инициализируем последовательность чисел
	// Создаем объект класса CalculateTask для вычислений
	CalculateTask cTsk(arrElem, countThreads);
}


/// <summary>Метод для чтения входных данных.</summary>
void WorkTask::readInputData()
{
	setColorCmd(10);
	std::cout << "\nСчитывание входных параметров." << std::endl;
	countElements = readElementsFromConsole(); // Вводим количество элементов
	countThreads = readThreadsFromConsole(); // Вводим количество потоков
}


/// <summary>Метод для ввода с консоли количества элементов в последовательности.</summary>
/// <returns>Число элементов в последовательности.</returns>
int WorkTask::readElementsFromConsole()
{
	int readResult;
	bool errorFlag = true;
	// Пока не будет не обнаружено ошибки
	do {
		setColorCmd(14);
		std::cout << "Введите количество элементов [" << MIN_COUNT_ELEMENTS << "; " << MAX_COUNT_ELEMENTS << "]:\n";
		setColorCmd(7);
		// Если ввод корректный и число положительное
		if (std::cin >> readResult && readResult >= 0) {
			// Если число соответствует заданному диапазону
			if (readResult >= MIN_COUNT_ELEMENTS && readResult <= MAX_COUNT_ELEMENTS) {
				errorFlag = false;
			} // Иначе сообщение об ошибке диапазона
			else { 
				std::stringstream errorContent;
				errorContent << "Вводимое значение должно быть в промежутке [" 
				<< MIN_COUNT_ELEMENTS << "; "<< MAX_COUNT_ELEMENTS << "]";
				errorOutput(errorContent.str());
			}

		} // Иначе сообщение о некорректном вводе
		else {
			errorOutput("Некорректный ввод! Попробуйте еще раз");
		}
		
	} while (errorFlag);
	
	return readResult;
}


/// <summary>Метод для ввода с консоли количества потоков для вычислений.</summary>
/// <returns>Число потоков.</returns>
int WorkTask::readThreadsFromConsole()
{
	int readResult;
	bool errorFlag = true;
	// Пока не будет не обнаружено ошибки
	do {
		setColorCmd(14);
		std::cout << "Введите количество потоков:\n";
		setColorCmd(7);
		// Если ввод корректный и число положительное
		if (std::cin >> readResult && readResult > 0) {
			errorFlag = false;
		} // Иначе сообщение о некорректном вводе
		else {
			errorOutput("Некорректный ввод! Попробуйте еще раз");
		}
		
	} while (errorFlag);
	
	return readResult;
}


/// <summary>Метод для инициализации последовательности псевдослучайными числами.</summary>
void WorkTask::initArrayRandomData()
{
	//srand(time(0)); для действительных случайных чисел
	for (int i = 0; i < countElements; i++) {
		arrElem.push_back(rand() % ((10000000 + 1) - 100) + 100);
	}
}


/// <summary>Метод для вывода результатов вычислений и времени выполнения.</summary>
/// <param name="name">Наименование режима вычисления</param>
/// <param name="result">Результат</param>
/// <param name="time">Время выполнения</param>
void writeOutputData(std::string name, int result, double time)
{
	setColorCmd(10);
	std::cout << name;
	setColorCmd(14);
	
	std::cout << "\nРезультат: " << result << "\nВремя выполнения: " << time << " сек.\n";
}



