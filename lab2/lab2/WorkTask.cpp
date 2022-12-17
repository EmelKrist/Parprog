#include "WorkTask.h"
#include "CalculateTask.h"
#include "CommandLine.h"

/// <summary>����������� ������ WorkTask.</summary>
WorkTask::WorkTask()
{
	readInputData(); // ������ ������� ������
	initArrayRandomData(); // �������������� ������������������ �����
	// ������� ������ ������ CalculateTask ��� ����������
	CalculateTask cTsk(arrElem, countThreads);
}


/// <summary>����� ��� ������ ������� ������.</summary>
void WorkTask::readInputData()
{
	setColorCmd(10);
	std::cout << "\n���������� ������� ����������." << std::endl;
	countElements = readElementsFromConsole(); // ������ ���������� ���������
	countThreads = readThreadsFromConsole(); // ������ ���������� �������
}


/// <summary>����� ��� ����� � ������� ���������� ��������� � ������������������.</summary>
/// <returns>����� ��������� � ������������������.</returns>
int WorkTask::readElementsFromConsole()
{
	int readResult;
	bool errorFlag = true;
	// ���� �� ����� �� ���������� ������
	do {
		setColorCmd(14);
		std::cout << "������� ���������� ��������� [" << MIN_COUNT_ELEMENTS << "; " << MAX_COUNT_ELEMENTS << "]:\n";
		setColorCmd(7);
		// ���� ���� ���������� � ����� �������������
		if (std::cin >> readResult && readResult >= 0) {
			// ���� ����� ������������� ��������� ���������
			if (readResult >= MIN_COUNT_ELEMENTS && readResult <= MAX_COUNT_ELEMENTS) {
				errorFlag = false;
			} // ����� ��������� �� ������ ���������
			else { 
				std::stringstream errorContent;
				errorContent << "�������� �������� ������ ���� � ���������� [" 
				<< MIN_COUNT_ELEMENTS << "; "<< MAX_COUNT_ELEMENTS << "]";
				errorOutput(errorContent.str());
			}

		} // ����� ��������� � ������������ �����
		else {
			errorOutput("������������ ����! ���������� ��� ���");
		}
		
	} while (errorFlag);
	
	return readResult;
}


/// <summary>����� ��� ����� � ������� ���������� ������� ��� ����������.</summary>
/// <returns>����� �������.</returns>
int WorkTask::readThreadsFromConsole()
{
	int readResult;
	bool errorFlag = true;
	// ���� �� ����� �� ���������� ������
	do {
		setColorCmd(14);
		std::cout << "������� ���������� �������:\n";
		setColorCmd(7);
		// ���� ���� ���������� � ����� �������������
		if (std::cin >> readResult && readResult > 0) {
			errorFlag = false;
		} // ����� ��������� � ������������ �����
		else {
			errorOutput("������������ ����! ���������� ��� ���");
		}
		
	} while (errorFlag);
	
	return readResult;
}


/// <summary>����� ��� ������������� ������������������ ���������������� �������.</summary>
void WorkTask::initArrayRandomData()
{
	//srand(time(0)); ��� �������������� ��������� �����
	for (int i = 0; i < countElements; i++) {
		arrElem.push_back(rand() % ((10000000 + 1) - 100) + 100);
	}
}


/// <summary>����� ��� ������ ����������� ���������� � ������� ����������.</summary>
/// <param name="name">������������ ������ ����������</param>
/// <param name="result">���������</param>
/// <param name="time">����� ����������</param>
void writeOutputData(std::string name, int result, double time)
{
	setColorCmd(10);
	std::cout << name;
	setColorCmd(14);
	
	std::cout << "\n���������: " << result << "\n����� ����������: " << time << " ���.\n";
}



