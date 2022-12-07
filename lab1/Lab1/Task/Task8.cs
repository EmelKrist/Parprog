namespace Lab1.Task;

public class Task8 : AbstractTask
{
	/// <summary>
    /// Список квадратов натуральных чисел.
    /// </summary>
    private List<int> _squaresNaturNumbers;
	
    public Task8() : base("Task8" ,
	"Нахождение в последовательности всех элементов, являющихся квадратами, любого натурального числа")
    {
        _squaresNaturNumbers = new List<int>();
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
		
        TimeExecution.Start();
        foreach (var element in Array)
        {
            if (IsSquareNumber(element))
            {
				_squaresNaturNumbers.Add(element);
			}
			
		}
        TimeExecution.Stop();
		
        Console.WriteLine("Количество квадратов любого натруального числа: {0}",
		TaskResult.Results = _squaresNaturNumbers.Count.ToString());
        WriteTimeResult();
	}
	
	/// <summary>
    /// Выявление, является ли число квадратом любого натурального числа.
    /// </summary>
	private bool IsSquareNumber(int number)
    {
        double sqrtNumber = Math.Sqrt(number);
        if (sqrtNumber == Math.Truncate(sqrtNumber))
        {
            return true;
		}
		
        return false;
	}
	
    protected override void ExecutionWithThread()
    {
		base.ExecutionWithThread();
		
		TimeExecution.Start();
		StartExecutionThread();
		_squaresNaturNumbers = new List<int>();
		int result = 0;
        for (int i = 0; i < CountThreads; i++)
        {
			Threads[i].Join(); 
            result += ThreadReturns[i];
		}
		TimeExecution.Stop();
		
		Console.WriteLine("Количество квадратов любого натруального числа: {0}",
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int countSquaresNumbers = 0;
		for (int i = begin; i < end; i++)
		{
			if (IsSquareNumber(Array[i]))
			{
				countSquaresNumbers++;
				_squaresNaturNumbers.Add(Array[i]);
			}
		}
		
		return countSquaresNumbers;
	}
	
}