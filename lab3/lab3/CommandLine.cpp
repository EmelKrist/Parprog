#include "CommandLine.h"

/// <summary>Конструктор класса CommandLine.</summary>
CommandLine::CommandLine()
{
	std::cout << "\nTask #4. Given a sequence of natural numbers.\n"
	<< "Create a multi-threaded application to find the sum\n"
	<< "of square roots of elements of a given sequence.\n";
}


/// <summary>Метод для ввода с консоли количества элементов в последовательности.</summary>
/// <returns>Число элементов в последовательности.</returns>
int CommandLine::readInputData()
{
	int readResult;
	bool errorFlag = true;
	std::cout << "\nReading input parameters." << std::endl;
	// Пока не будет не обнаружено ошибки
	do {
		std::cout << "Enter the number of items [" << MIN_COUNT_ELEMENTS << "; " << MAX_COUNT_ELEMENTS << "]:\n";
		// Если ввод корректный 
		if (std::cin >> readResult && readResult >= 0) {
			// Если число соответствует заданному диапазону
			if (readResult >= MIN_COUNT_ELEMENTS && readResult <= MAX_COUNT_ELEMENTS) {
				errorFlag = false;
			} // Иначе сообщение об ошибке диапазона
			else {
				std::stringstream errorContent;
				errorContent << "The input value must be between ["
				<< MIN_COUNT_ELEMENTS << "; " << MAX_COUNT_ELEMENTS << "]";
				writeError(errorContent.str());
			}
			
		} // Иначе сообщение о некорректном вводе
		else {
			writeError("Invalid input! Try again");
		}
		
	} while (errorFlag);
	
	return readResult;
}


/// <summary>Дружественный метод для вывода сообщения об ошибке.</summary>
/// <param name="content">Содержание сообщения</param>
void writeError(std::string content)
{
	// Выводим сообщение об ошибке
	std::cout << content << std::endl;
	// Перезагружаем поток вывода 
	std::cin.clear();
	std::cin.ignore(256, '\n');
}


/// <summary>Дружественный метод для вывода результатов вычислений 
/// и времени выполнения.</summary>
/// <param name="name">Наименование режима вычисления</param>
/// <param name="result">Результат</param>
/// <param name="time">Время выполнения</param>
void writeOutputData(std::string nameMode, double result, double time)
{
	std::cout << nameMode
	<< "\nResult: " << std::fixed << result
	<< "\nExecution time: " << time << " sec.\n";
}

