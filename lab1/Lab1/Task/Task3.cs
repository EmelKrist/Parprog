namespace Lab1.Task;

public class Task3 : AbstractTask
{
    /// <summary>
    /// Число b.
    /// </summary>
    private int _number;
    
    public Task3() : base("Task3", 
	"Определения количества вхождений числа в массив")
    {
	}
	
    protected override void ReadInputData()
    {
        base.ReadInputData();
		
        _number = ReadDigitFromConsole("Введите число: ");
	}
	
    protected override void ExecutionWithoutThread()
    {
        base.ExecutionWithoutThread();
		
        ExecutionStandard();
        ExecutionCustom();
	}
	
    /// <summary>
    /// Вычисление стандартными средствами количества вхождений числа b.
    /// </summary>
    private void ExecutionStandard()
    {
        Logger.Debug("Вычисление стандартными стредствами.");
		
        TimeExecution.Start();
        Console.WriteLine("Количество вхождений числа: {0}", 
		TaskResult.Results = Array.Count(element => element == _number).ToString());
        TimeExecution.Stop();
		
        WriteTimeResult();
	}
	
    /// <summary>
    /// Вычисление вручную количества вхождений числа b.
    /// </summary>
    private void ExecutionCustom()
    {
        Logger.Debug("Вычисление вручную.");
        int count = 0;
		
        TimeExecution.Start();
        for (var i = 0; i < CountElements; i++) 
        { 
			if (Array[i] == _number)
            {
				count++;
			}
			
		}          
        TimeExecution.Stop();
		
        Console.WriteLine("Количество вхождений числа: {0}", 
		TaskResult.Results = count.ToString());
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
		
        Console.WriteLine("Количество вхождений числа: {0}", 
		TaskResult.Results = result.ToString());
        WriteTimeResult();
		
	} 
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int count = 0;
		for (int i = begin; i < end; i++)
        {
			if (Array[i] == _number)
            {
				count++;
			}
			
		}
		
		return count;
	}
	
}