#include "CommandLine.h"

int main() 
{
    setlocale(LC_ALL, "Russian");
	
	// Запускаем консольное приложение 
    CommandLine cmd;
    cmd.startWork();
	
    return 0;
}
