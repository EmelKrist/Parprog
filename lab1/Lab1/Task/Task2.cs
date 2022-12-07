namespace Lab1.Task;

public class Task2 : AbstractTask
{
    /// <summary>
    /// Количество пар кодирующих чисел.
    /// </summary>
    private int _N;
	
    /// <summary>
    /// Массив кодирующих чисел a.
    /// </summary>
    private int[] _arrayA;
	
    /// <summary>
    /// Массив кодирующих чисел b.
    /// </summary>
    private int[] _arrayB;
	
    /// <summary>
    /// Массив для хранения последовательности чисел С.
    /// </summary>
    private int[] _arrayС;
	
    public Task2() : base("Task2","Кодировка последовательности C")
    {
	}
	
    protected override void ReadInputData()
    {
        base.ReadInputData();
		
        _N = ReadDigitFromConsole("Введите количество пар кодирующих чисел: ");
        _arrayA = InitialEncodingNumbersRandomData();
        _arrayB = InitialEncodingNumbersRandomData();
	}
	
    /// <summary>
    /// Инициализация массива случайными неповторяющимися числами.
    /// </summary>
    /// <returns> Массив, заполненный случайными числами.</returns>
    protected int[] InitialEncodingNumbersRandomData()
    {
        int[] arrayTemp = new int[_N];
        int temp;
        Random random;
        for (int i = 0; i < _N; i++)
        {
            random = new Random();
            temp = random.Next();
            while (arrayTemp.Contains(temp)) temp = random.Next();
            arrayTemp[i] = temp;
		}
		
        return arrayTemp;
	}
	
	protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
		_arrayС = Array.ToArray();
        int countEncodedElements = 0;
		
        TimeExecution.Start();
		for (int i = 0; i < CountElements; i++)
        {
            for (int j = 0; j < _N; j++)
            {
                if (Array[i] == _arrayA[j])
                {
                    Array[i] = _arrayB[j];
                    countEncodedElements++;
				}
				
			}
			
		}   
		TimeExecution.Stop();
		
		Console.WriteLine("Количество закодированных элементов: {0}", 
		TaskResult.Results = countEncodedElements.ToString());
		WriteTimeResult();		
	}
	
	protected override void ExecutionWithThread()
	{
        base.ExecutionWithThread();
        Array = _arrayС.ToArray();
		
        TimeExecution.Start();
		StartExecutionThread();
		int result = 0;
		for (int i = 0; i < CountThreads; i++)
        {
			Threads[i].Join(); 
			result += ThreadReturns[i];
		}
		TimeExecution.Stop();
		
		Console.WriteLine("Количество закодированных элементов: {0}", 
		TaskResult.Results = result.ToString());
		WriteTimeResult();	
	} 
	
	protected override int CalculateThreadFunction(int begin, int end) 
	{
		int countEncodedElements = 0;
		for (int i = begin; i < end; i++)
        {
			for (int j = 0; j < _N; j++)
            {
                if (Array[i] == _arrayA[j])
                {
                    Array[i] = _arrayB[j];
                    countEncodedElements++;
				}
				
			}
			
		}
		
		return countEncodedElements;
	}
 	
}