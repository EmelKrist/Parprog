using Lab1.Task;

namespace Lab1;

public class Commands
{
    private readonly Dictionary<string, ITask> _dictionaryTask;

    private readonly Dictionary<string, string> _dictionary;


    public Commands()
    {
        _dictionaryTask = new Dictionary<string, ITask>
        {
            { "1", new Task1() },
            { "2", new Task2() },
            { "3", new Task3() },
            { "4", new Task4() },
            { "5", new Task5() },
            { "6", new Task6() },
            { "7", new Task7() },
            { "8", new Task8() },
            { "9", new Task9() },
            { "10", new Task10() }
        };

        _dictionary = new Dictionary<string, string>
        {
            { "help", "Реализация отображение справки в разработке" },
            { "q", "Реализация выхода в разработке" }
        };
    }

    public bool ParseCommand(string command)
    {
        if (_dictionaryTask.ContainsKey(command))
        {
            _dictionaryTask[command].Run();
        }
        else if (_dictionary.ContainsKey(command))
        {
            Console.WriteLine(_dictionary[command]);
        }
        else
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine("Неизвестная комманда, повторите ввод!");
            Console.ResetColor();
        }

        return true;
    }
}