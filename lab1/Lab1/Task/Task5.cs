namespace Lab1.Task;

public class Task5 : AbstractTask
{
    public Task5() : base("Task5",
	"Поиск максимального значения последовательности")
    {
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
		
        TimeExecution.Start();
        Console.WriteLine("Максимальное число: {0}", 
		TaskResult.Results = Array.Max().ToString());
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
		int result = ThreadReturns.Max();
		TimeExecution.Stop();
		
		Console.WriteLine("Маскимальное число: {0}", 
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int max = Array[begin];
		for (int i = begin; i < end; i++)
        {
			if (Array[i] > max)
            {
                max = Array[i];
			}
			
		}
		
		return max;
	}
	
}