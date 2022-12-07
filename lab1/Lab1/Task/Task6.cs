namespace Lab1.Task;

public class Task6 : AbstractTask
{
    public Task6() : base("Task6",
	"Поиск минимального значения последовательности")
    {
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
		
        TimeExecution.Start();
        Console.WriteLine("Минимальное число: {0}", 
		TaskResult.Results = Array.Min().ToString());
        TimeExecution.Stop();
		
        WriteTimeResult();
	}
	
    protected override void ExecutionWithThread()
    {
		base.ExecutionWithThread();
		
		TimeExecution.Start();
		StartExecutionThread();
		for (int i = 0; i < CountThreads; i++)
        {
			Threads[i].Join();
		}       
		int result = ThreadReturns.Min();
		TimeExecution.Stop();
		
		Console.WriteLine("Минимальное число: {0}", 
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int min = Array[begin];
		for (int i = begin; i < end; i++)
        {
			if (Array[i] < min)
            {
				min = Array[i];
			}
			
		} 
		
		return min;
	}
	
}