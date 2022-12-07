using Lab1;

Console.ForegroundColor = ConsoleColor.DarkBlue;
Console.WriteLine("Лабораторная работа 1. Организация параллельно выполняемых потоков и межпроцессное взаимодействие.");
Console.WriteLine("Для запуска задачи введите её номер.");
Console.WriteLine("Для выхода нажмите q");
Console.ResetColor();
Console.WriteLine();

bool isExit = true;
do
{
    var commands = new Commands();
    Console.Write("\nВведите данные: ");
    var command = Console.ReadLine();
    isExit = commands.ParseCommand(command);
} while (isExit);

Console.WriteLine("Завершение программы.");