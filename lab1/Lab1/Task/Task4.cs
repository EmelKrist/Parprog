namespace Lab1.Task;

public class Task4 : AbstractTask
{
    public Task4() : base(
        "Task4",
	"Вычисление произведения последовательности чисел")
    {
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
		
        TimeExecution.Start();
        Console.WriteLine("Произведение чисел: {0}", 
		TaskResult.Results = Array.Aggregate((x, y) => x * y).ToString());
        TimeExecution.Stop();
		
        WriteTimeResult();
	}
	
    protected override void ExecutionWithThread()
    {
		base.ExecutionWithThread();
		
		TimeExecution.Start();
		StartExecutionThread();
		int result = 1;
		for (int i = 0; i < CountThreads; i++)
		{
			Threads[i].Join();
			result *= ThreadReturns[i];
		}      
		TimeExecution.Stop();
		
		Console.WriteLine("Произведение чисел: {0}", 
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int multiplication = 1;
		for (int i = begin; i < end; i++)
        {
			multiplication *= Array[i];
		}
			
		return multiplication;
	}
	
}