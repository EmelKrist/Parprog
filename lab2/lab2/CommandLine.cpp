#include "CommandLine.h"
#include "WorkTask.h"

/// <summary>����������� ������ CommandLine.</summary>
CommandLine::CommandLine()
{
	setColorCmd(3);
	std::cout << "������� �4. ���� ������������������ ����������� ����� {a0�an�1}.\n"
	<< "������� ������������� ���������� ��� ������ ����� ����������\n"
	<< "������ �� ��������� ������ ������������������.\n";
}


/// <summary>����� ��� ������� ������ � ��������� �������.</summary>
void CommandLine::startWork()
{
	int choise;
	bool createFlag;
	// ���� ��������� �� �������� ������, ����� ���������� ���� ������
	do {		
		createFlag = false;
		setColorCmd(7);
		std::cout << "\n���� ������:\n1. ��������� ������;\n2. ����� �� ���������.\n������� �����: ";
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
			errorOutput("����������� �������! ���������� ��� ���");
		}
		
		if (createFlag) {
			// ������� ������ ������ WorkTask ��� ������ � �������
			WorkTask wTsk;
		}
		
	} while (true);
}


/// <summary>����� ��� ������ ��������� �� ������.</summary>
/// <param name="content">���������� ���������</param>
void errorOutput(std::string content)
{
	// ������� ������� ��������� �� ������
	setColorCmd(4);
	std::cout << content << std::endl;
	setColorCmd(7);
	// ������������� ����� ������ 
	std::cin.clear();
	std::cin.ignore(256, '\n');
}


/// <summary>����� ��� ����� ����� ������ � ��������� ������.</summary>
/// <param name="numColor">����� �����</param>
void setColorCmd(int numColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, numColor);
}
