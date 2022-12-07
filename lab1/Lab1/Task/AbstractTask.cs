using System.Diagnostics;
using NLog;

namespace Lab1.Task;

public abstract class AbstractTask : ITask
{
    /// <summary>
    /// Название задачи.
    /// </summary>
    private readonly string _title;
	
    /// <summary>
    /// Описание задачи.
    /// </summary>
    private readonly string _description;
    
    /// <summary>
    ///Данные о времени запуске программы.
    /// </summary>
    protected Stopwatch TimeExecution;
	
    /// <summary>
    /// Количество элементов массивов.
    /// </summary>
    protected int CountElements;
	
    /// <summary>
    /// Минимальное количество элеметов массива.
    /// </summary>
    private const int MinCountElements = 100000;
	
    /// <summary>
    /// Максимальное количество элеметов массива.
    /// </summary>
    private const int MaxCountElements = 1000000;
	
    /// <summary>
    /// Количество потоков.
    /// </summary>
    protected int CountThreads = Environment.ProcessorCount;
	
    /// <summary>
    /// Последовательность натуральных чисел.
    /// </summary>
    protected int[] Array;
	
    /// <summary>
    /// Потоки.
    /// </summary>
    protected Thread[] Threads;
	
    /// <summary>
    /// Логгер приложения.
    /// <include file="nlog.config" path="nlog/[@name="nlog"]/*"/>
    /// </summary>
    protected Logger Logger { get; }
	
    /// <summary>
    /// Формат вывода целого числа.
    /// </summary>
    private const string IntFormat = "{0:## ##0}";
	
    /// <summary>
    /// Результат задачи.
    /// </summary>
    protected TaskResult TaskResult;
	
    /// <summary>
    /// Возвращаемые значения потоков.
    /// </summary>
    protected int[] ThreadReturns;
    
    protected AbstractTask(string title, string description)
    {
        _title = title;
        _description = description;
        Logger = LogManager.GetCurrentClassLogger();
        TimeExecution = new Stopwatch();
        TaskResult = new TaskResult();
	}
	
    /// <summary>
    /// Считывание входных данных.
    /// </summary>
    protected virtual void ReadInputData()
    {
        Logger.Debug("Считывание входных параметров.");
        CountElements = ReadElementsFromConsole(
            $"Введите количество элементов [{FormatInt(MinCountElements)}; {FormatInt(MaxCountElements)}]: ",
		MinCountElements, MaxCountElements);
		CountThreads = ReadThreadsFromConsole($"Введите количество потоков");
	}
	
    /// <summary>
    /// Инициализация массива случайными числами.
    /// </summary>
    /// <returns> массива заполненный случайными числами.</returns>
    protected int[] InitialArrayRandomData()
    {
        var array = new int[CountElements];
        Random random;
        for (var i = 0; i < CountElements; i++)
        {
            random = new Random();
            array[i] = random.Next(100,10000000);
		}
		
        return array;
	}
	
    /// <summary>
    /// Выполнение действий в многопоточном режиме.
    /// </summary>
    protected virtual void ExecutionWithThread()
    {
        Logger.Debug("Выполнение в многопоточном режиме.");
        TaskResult.CountThreads = CountThreads;
	}
	
    /// <summary>
    /// Выполнение действий в однопоточном потоке.
    /// </summary>
    protected virtual void ExecutionWithoutThread()
    {
        Logger.Debug("Выполнение в однопоточном режиме.");
        TaskResult.CountThreads = 1;
	}
	
    /// <summary>
    /// Считывание количества элементов с консоли.
    /// </summary>
    /// <param name="message">Сообщение перед вводом данных</param>
    /// <param name="minValue">Минимальное значение (включительно).</param>
    /// <param name="maxValue">Максимальное значение (включительно).</param>
    /// <returns>Считанное целое число с консоли.</returns>
    private int ReadElementsFromConsole(string message, int minValue, int maxValue)
    {
        bool error = true;
        int resultRead = 0;
        do
        {
            try
            {
                Logger.Info(message);
                resultRead = Convert.ToInt32(Console.ReadLine());
				
                error = (resultRead < minValue || resultRead > maxValue);
				
                if (error)
                {
                    Logger.Error($"Вводимое значение должно быть в промежутке [{minValue}; {maxValue}]");
				}
			}
            catch (FormatException formatException)
            {
                WriteError("", formatException);
			}
		} while (error);
		
        return resultRead;
	}

    /// <summary>
    /// Считывание количества потоков с консоли.
    /// </summary>
    /// <param name="message">Сообщение перед вводом данных</param>
    /// <returns>Считанное целое число с консоли.</returns>
    private int ReadThreadsFromConsole(string message)
    {
        bool error = true;
        int resultRead = 0;
        do
        {
            try
            {
                Logger.Info(message);
                resultRead = Convert.ToInt32(Console.ReadLine());
                error = false;
			}
            catch (FormatException formatException)
            {
                WriteError("Некорректный ввод данных!", formatException);
                error = true;
			}
        } while (error);
		
        return resultRead;
	}
	
    /// <summary>
    /// Считывание целового числа из консоли.
    /// </summary>
    /// <param name="message">Сообщение перед вводом данных</param>
    /// <returns>Считанное целое число с консоли.</returns>
    protected int ReadDigitFromConsole(string message)
    {
        bool error = true;
        int resultRead = 0;
        do
        {
            try
            {
                Logger.Info(message);
                resultRead = Convert.ToInt32(Console.ReadLine());
                error = false;
			}
            catch (FormatException formatException)
            {
                WriteError("Ошибка считывания числа", formatException);
			}
		} while (error);
		
        return resultRead;
	}
	
    /// <summary>
    /// Запись ошибки.
    /// </summary>
    /// <param name="errorMessage">Ошибка.</param>
    /// <param name="exception"></param>
    private void WriteError(string errorMessage, Exception exception)
    {
        Logger.Error(errorMessage);
        Logger.Trace(exception);
	}
	
    /// <summary>
    /// Запуск выполения задачи.
    /// </summary>
    public void Run()
    {
        ReadInputData();
		
        TaskResult.Title = _title;
        TaskResult.CountElements = CountElements;
		
        Array = new int[CountElements];
        Array = InitialArrayRandomData();
        
        Threads = new Thread[CountThreads];
        Threads.Initialize();
		
        ExecutionWithoutThread();
        TimeExecution.Reset();
        ExecutionWithThread();
	}
	
    /// <summary>
    /// Вывод результатов работы таймера.
    /// </summary>
    protected void WriteTimeResult()
    {
        Logger.Info($"Время сравнения массивов: {TimeExecution.ElapsedMilliseconds} ms");
        TaskResult.Time = TimeExecution.ElapsedMilliseconds.ToString();
		
        using var writer = new StreamWriter("result.csv", true);
        writer.WriteLine(TaskResult.ToString());
        writer.Flush();
	}
	
    /// <summary>
    /// Форматирование числа.
    /// </summary>
    /// <param name="number">Число</param>
    /// <returns>Отформатированное число.</returns>
    private string FormatInt(int number)
    {
        return string.Format(IntFormat, number);
	}
	
    /// <summary>
    /// Запуск выполнения потоков.
    /// </summary>
    protected void StartExecutionThread()
    {
		ThreadReturns = new int[CountThreads]; 
		
		for (var i = 0; i < CountThreads; i++)
		{
            int temp = i;
            ThreadReturns[temp] = 0;
            Threads[i] = new Thread(() => { ThreadReturns[temp] = ThreadFunction(temp); });
            Threads[i].Start();
		}
	}
	
    /// <summary>
    /// Функция разделения последовательности на подпоследовательности для вычисления функции потоком.
    /// </summary>
    /// <param name="numThread">Номер потока</param>
    /// <returns>Результат вычисления функции потоком.</returns>
    protected int ThreadFunction(int numThread) 
    {
		int begin, parts, end; 
		parts = CountElements / CountThreads; 
		begin = parts * numThread; 
		end = begin + parts;
		if (numThread == CountThreads - 1) 
		end = CountElements;   
		
		return CalculateThreadFunction(begin, end);
	}
	
    /// <summary>
    /// Вычисление функции потоком.
    /// </summary>
    /// <param name="begin">Начало подпоследовательности</param>
    /// <param name="end">Конец подпоследовательности</param>
    /// <returns>Результат вычисления функции потоком.</returns>
    protected abstract int CalculateThreadFunction(int begin, int end);
	
}