namespace Lab1.Task;

public class Task7 : AbstractTask
{
	/// <summary>
    /// Список простых чисел.
    /// </summary>
    private List<int> _primeNumbers;
	
    public Task7() : base("Task7",
	"Нахождение в последовательности всех простых чисел")
    {
        _primeNumbers = new List<int>();
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
		
        TimeExecution.Start();
        foreach (var element in Array)
        {
            if (IsPrimeNumber(element))
            {
				_primeNumbers.Add(element);
			}
			
		}
        TimeExecution.Stop();
		
        Console.WriteLine("Количество простых чисел: {0}",
		TaskResult.Results = _primeNumbers.Count.ToString());
        WriteTimeResult();
	}
	
	/// <summary>
    /// Выявление, является ли число простым.
    /// </summary>
    private bool IsPrimeNumber(int number)
    {
        for (var i = 2; i < number; i++) { 
            if (number % i == 0)
            {
				return false;
			}
			
		}
		
        return true;
	}
	
    protected override void ExecutionWithThread()
    {
		base.ExecutionWithThread();
		
		TimeExecution.Start();
		StartExecutionThread();
		_primeNumbers = new List<int>();
		int result = 0;
        for (int i = 0; i < CountThreads; i++)
        {
			Threads[i].Join(); 
            result += ThreadReturns[i];
		}
		TimeExecution.Stop();
		
		Console.WriteLine("Количество простых чисел: {0}",
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int countPrimeNumbers = 0;
		for (int i = begin; i < end; i++)
		{
			if (IsPrimeNumber(Array[i])) 
			{ 
                countPrimeNumbers++; 
                _primeNumbers.Add(Array[i]);
			}
		}
		
		return countPrimeNumbers;
	}
    
}