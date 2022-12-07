namespace Lab1.Task;

public class Task9 : AbstractTask
{
	
    public Task9() : base("Task9",
	"Вычисдление суммы последовательности с чередованием знака.")
    {
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
        int znak = 1;
		
        TimeExecution.Start();
        Console.WriteLine("Результат вычисления выражения: {0}",
		TaskResult.Results = Array.Aggregate((x, y) => x + y * (znak *= -1)).ToString());
        TimeExecution.Stop();
		
        WriteTimeResult();
	}
	
    protected override void ExecutionWithThread()
    {
		base.ExecutionWithThread();
		
		TimeExecution.Start();
		StartExecutionThread(); 
		int result = 0;
        for (int i = 0; i < CountThreads; i++)
        {
			Threads[i].Join(); 
            result += ThreadReturns[i];
		}
		TimeExecution.Stop();
		
		Console.WriteLine("Результат вычисления выражения: {0}",
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {  
		int calculate = 0;
		int znak = -1;
		if (begin % 2 == 0)
		{
			znak = 1;
		}

		for (int i = begin; i < end; i++)
		{
			calculate += Array[i] * znak;
			znak *= -1;
		}
		
		return calculate;
	}
	
}