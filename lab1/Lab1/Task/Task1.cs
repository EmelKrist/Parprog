using System.Diagnostics;

namespace Lab1.Task;

public class Task1 : AbstractTask
{
	/// <summary>
    /// Последовательность чисел С.
    /// </summary>
	private int[] _arrayC;
	
	public Task1()
	: base("Task1",
	"Совпадают ли поэлементно массивы А и С")
	{
	}
	
	protected override void ReadInputData()
	{
		base.ReadInputData();
		
		_arrayC = new int[CountElements];
		_arrayC = InitialArrayRandomData();
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
		
		Console.WriteLine("Количество совпадающих элементов: {0}", 
		TaskResult.Results = result.ToString());
		WriteTimeResult();
		
	}
	
    protected override int CalculateThreadFunction(int begin, int end) 
    {
		int countEqualElements = 0;
		for (int i = begin; i < end; i++)
        {
			if (Array[i] == _arrayC[i])
            {
                countEqualElements++;
			}
			
		}
		
		return countEqualElements;
	}
	
	protected override void ExecutionWithoutThread()
	{
		base.ExecutionWithoutThread();
		int countEqualElements = 0;
		
		TimeExecution.Start();
		for (var i = 0; i < CountElements; i++)
        {
			if (Array[i] == _arrayC[i])
            {
                countEqualElements++;
			}
			
		}   
		TimeExecution.Stop();
		
		Console.WriteLine("Количество совпадающих элементов: {0}", 
		TaskResult.Results = countEqualElements.ToString());
		WriteTimeResult();
	}
}
