#include "CommandLine.h"
#include "WorkTask.h"

/// <summary>Конструктор класса CommandLine.</summary>
CommandLine::CommandLine()
{
	setColorCmd(3);
	std::cout << "Вариант №4. Дана последовательность натуральных чисел {a0…an–1}.\n"
	<< "Создать многопоточное приложение для поиска суммы квадратных\n"
	<< "корней из элементов данной последовательности.\n";
}


/// <summary>Метод для запуска работы с командной строкой.</summary>
void CommandLine::startWork()
{
	int choise;
	bool createFlag;
	// Пока программа не завершит работу, будет появляться меню выбора
	do {		
		createFlag = false;
		setColorCmd(7);
		std::cout << "\nМеню выбора:\n1. Запустить задачу;\n2. Выйти из программы.\nВведите пункт: ";
		std::cin >> choise;
		switch (choise)
		{
		case 1:
			createFlag = true;
			break;
		case 2:
			exit(0);
			break;
		default:
			errorOutput("Неизвестная команда! Попробуйте еще раз");
		}
		
		if (createFlag) {
			// Создаем объект класса WorkTask для работы с задачей
			WorkTask wTsk;
		}
		
	} while (true);
}


/// <summary>Метод для вывода сообщения об ошибке.</summary>
/// <param name="content">Содержание сообщения</param>
void errorOutput(std::string content)
{
	// Выводим красное сообщение об ошибке
	setColorCmd(4);
	std::cout << content << std::endl;
	setColorCmd(7);
	// Перезагружаем поток вывода 
	std::cin.clear();
	std::cin.ignore(256, '\n');
}


/// <summary>Метод для смены цвета текста в командной строке.</summary>
/// <param name="numColor">Номер цвета</param>
void setColorCmd(int numColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, numColor);
}
