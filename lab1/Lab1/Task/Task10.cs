namespace Lab1.Task;

public class Task10 : AbstractTask
{
    public Task10() : base("Task10",
	"Вычисление суммы чётных элементов последовательности")
    {
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
        int sum = 0;
		
        TimeExecution.Start();
        foreach (var element in Array)
        {
            if (element % 2 == 0)
            {
				sum += element;
			}
			
		}
        TimeExecution.Stop();
		
        Console.WriteLine("Сумма четных чисел: {0}",
		TaskResult.Results = sum.ToString());
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
		
		Console.WriteLine("Сумма четных чисел: {0}",
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int sum = 0;
		for (int i = begin; i < end; i++)
		{
			if (Array[i] % 2 == 0)
			{
                sum += Array[i];
			}
			
		}
		
		return sum;
	}
	
}
