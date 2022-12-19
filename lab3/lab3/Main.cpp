#include "MpiexecTask.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	
	// Создаем объект класса MpiexecTask и запускаем на исполнение
	MpiexecTask mpiTsk;
	mpiTsk.run();
	
	return 0;
}
