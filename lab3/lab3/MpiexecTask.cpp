#include "MpiexecTask.h"

/// <summary>Конструктор класса MpiexecTask.</summary>
MpiexecTask::MpiexecTask()
{
	// Инициализируем библиотеку MPI
	MPI_Init(NULL, NULL);
	// Сообщаем размер группы и порядковый номер вызывающей задачи
	MPI_Comm_size(MPI_COMM_WORLD, &countThreads);
	MPI_Comm_rank(MPI_COMM_WORLD, &numbThread);
	// Досрочно выходим, если процесс всего один
	if (countThreads < 2) {
		writeError("Too few processes! Press any key to exit...");
		MPI_Finalize();
		exit(0);
	}
	// Ставим точку синхронизации
	MPI_Barrier(MPI_COMM_WORLD);
}


/// <summary>Метод для запуска взаимодействия через передачу сообщений (MPI).</summary>
void MpiexecTask::run()
{
	// Если работает 0 процесс (root процесс)
	if (numbThread == 0) {
		
		// Считываем входные параметры и создаем массив с случанйыми числами
		CommandLine cmd;
		countElements = cmd.readInputData();
		double *arrElem = initArrayRandomData();
		
		// Запускаем однопоточное вычисление 
		executionWithoutThread(arrElem);
		
		// Запускаем многопоточное вычисление(взаимодействие) в root процессе
		executionWithRootThread(arrElem);
	}
	else { // Иначе, если работают остальные процессы
		
		// Запускаем многопоточное вычисление(взаимодействие) в остальных процессах
		executionWithOtherThreads();
	}
	
	// Закрываем библиотеку MPI
	MPI_Finalize();
}


/// <summary>Метод для инициализации последовательности псевдослучайными числами.</summary>
/// <returns>Массив c псевдослучайными числами.</returns>
double* MpiexecTask::initArrayRandomData()
{
	double *arrElem = new double[countElements];
	for (int i = 0; i < countElements; i++) {
		arrElem[i] = rand() % ((10000000 + 1) - 100) + 100;
	}
	return arrElem;
}


/// <summary>Метод для однопоточного вычисления.</summary>
/// <param name="arrElem">Массив c псевдослучайными числами</param>
void MpiexecTask::executionWithoutThread(double* arrElem)
{
	time = MPI_Wtime();
	double sum = 0;
	for (int i = 0; i < countElements; i++) {
		sum += sqrt(arrElem[i]);
	}
	time = MPI_Wtime() - time;
	writeOutputData("\nExecution in single-threaded mode.", sum, time);
}


/// <summary>Метод для запуска многопоточного вычисления в root процессе.</summary>
/// <param name="arrElem">Массив c псевдослучайными числами</param>
void MpiexecTask::executionWithRootThread(double* arrElem)
{
	std::cout << "\nThe number of processes: " << countThreads << std::endl;
	time = MPI_Wtime();
	// Помещаем кол-во элементов в другие процессы
	for (int i = 1; i < countThreads; i++) {
		MPI_Send(&countElements, 1, MPI_INT, i, 7, MPI_COMM_WORLD);
	}	
	// Помещаем массив данных в другие процессы
	for (int i = 1; i < countThreads; i++) {
		MPI_Send(arrElem, countElements, MPI_DOUBLE, i, 3, MPI_COMM_WORLD);
	}
	// Вычисляем сумму для 0 процесса
	double sum = calcPartElemThread(arrElem, countElements);
	// Берем промеж. суммы из других процессов и суммируем 
	for (int i = 1; i < countThreads; i++) {
		double psum = 0;
		MPI_Recv(&psum, 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD, &status);
		sum += psum;
	}
	// Получаем и выводим результат
	time = MPI_Wtime() - time;
	writeOutputData("\nExecution in multi-threaded mode.", sum, time);
}


/// <summary>Метод для запуска многопоточного вычисления в остальных процессах.</summary>
void MpiexecTask::executionWithOtherThreads()
{
	int getCountElements = 0;
	// Берем ков-во элементов из 0 процесса
	MPI_Recv(&getCountElements, 1, MPI_INT, 0, 7, MPI_COMM_WORLD, &status);
	double *getArrElem = new double[getCountElements];
	// Берем массив данных из 0 процесса
	MPI_Recv(getArrElem, getCountElements, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD, &status);
	// Вычисляем промежуточные сумму и помещаем их в 0 процесс
	double psum = calcPartElemThread(getArrElem, getCountElements);
	MPI_Send(&psum, 1, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD);
}


/// <summary>Метод для вычисления части элементов конкретным потоком.</summary>
/// <param name="arrElem">Массив c псевдослучайными числами</param>
/// <param name="sizeArr">Размер массива</param>
/// <returns>Промежуточная сумма корней элементов.</returns>
double MpiexecTask::calcPartElemThread(double* arrElem, int sizeArr)
{
	int beginPart, sizePart, endPart;
	double psum = 0;
	// Находим длину части последовательности, ее начало и конец
	sizePart = sizeArr / countThreads;
	beginPart = sizePart * numbThread;
	endPart = beginPart + sizePart;
	if (numbThread == countThreads - 1) endPart = sizeArr;
	// Вычисляем промежуточную сумму коней элементов на отрезке
	for (int i = beginPart; i < endPart; i++) {
		psum += sqrt(arrElem[i]);
	}
	return psum;
}



