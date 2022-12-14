#include <QtConcurrent>
#include <QtWidgets>
#include "mywidget.h"
#include <cstdlib>

/**
* @brief perElementFunc - Функция вычисления на участве последовательности;
* @param task - Задача;
* @return result - Результат произведения.
*/
qint64 perElementFunc(const Task task) {
	qint64 result;
	//На отрезке нити находим произведение элементов массива
	for (int i=task.beginIndex; i<=task.endIndex; i++) {
		result*=task.listPtr->at(i);
        QThread::msleep(1);
	}
	return result;
}

/**
* @brief reduce - Функция объединения результатов частичного произведения к общему.
* @param multipl - Общее произведение.
* @param semiMultipl - Частичное произведение.
*/
void reduce(qint64 & multipl, const qint64 semiMultipl) {
	multipl *= semiMultipl;
}

/**
* @brief generateRandomNumber - Функция генерации случайных чисел;
* @param minVal - Минимальное генерируемое число;
* @param maxVal - Максимальное генерируемое число;
* @param seed - Базовое число для генерации случайного;
* @return - Случайное число в диапазоне.
*/
int generateRandomNumber(int minVal, int maxVal, int seed) {
    //В качестве базового числа используется системное время
    qsrand(seed);
    return (qrand() % ((maxVal + 1) - minVal) + minVal);
}

/**
* @brief mywidget::mywidget - Конструирование виджета;
* @param parent.
*/
mywidget::mywidget(QWidget *parent) : QWidget(parent) {

    //Инициализируем компоненты
    outputField = new QTextEdit();
    elementsEditField = new QLineEdit();
    threadsEditField = new QLineEdit();
    startBtn = new QPushButton(tr("Старт"));
    stopBtn = new QPushButton(tr("Остановить"));
    QPushButton *closeBtn = new QPushButton(tr("Закрыть"));
    messageLbl = new QLabel();
	
    //Настраиваем компоненты
    outputField->setReadOnly(true); //Поле вывода только для чтения
    outputField->append("Поиск произведения последовательности чисел:\n"
		"1. Данные генерируются случайным образом;\n"
		"2. Количестве элементов: от 100000 до 1000000;\n"
	"3. Количество потоков: от 2 до 100000.");
    messageLbl->setStyleSheet("color: red");
    //Валидаторы для корректного ввода данных в диапазоне
    elementsEditField->setValidator(new QIntValidator(100000, 1000000, this));
    threadsEditField->setValidator(new QIntValidator(2,100000,this));
    elementsEditField->setText("100000");
    threadsEditField->setText(QString::number(QThread::idealThreadCount()));
    stopBtn->setEnabled(false);
	
    //Создаем и настраиваем разметку
    QFormLayout *fieldsLayout = new QFormLayout;
    fieldsLayout->addRow(tr("Кол-во элементов:"), elementsEditField);
    fieldsLayout->addRow(tr("    Кол-во потоков:"), threadsEditField);
	
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(outputField);
    mainLayout->addWidget(messageLbl);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(startBtn);
    mainLayout->addWidget(stopBtn);
    mainLayout->addWidget(closeBtn);
	
    setLayout(mainLayout);
	
    //Подключаем к кнопкам обработчики событий
    connect(startBtn,SIGNAL(clicked()),this,SLOT(clickStart()));
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(clickClose()));
    connect(stopBtn,SIGNAL(clicked()),this,SLOT(clickStop()));
}

/**
* @brief mywidget::clickStart - Событие нажатия на кнопку "Старт".
*/
void mywidget::clickStart() {
	
    /*Проверяем поля с входными данными на корректный ввод
		*Если данные введены корректно, то...
	*/
    if (elementsEditField->hasAcceptableInput() && threadsEditField->hasAcceptableInput()){
		
		//Настраиваем компоненты
		messageLbl->setText("");
		elementsEditField->setReadOnly(true);
		threadsEditField->setReadOnly(true);
		startBtn->setEnabled(false);
		//Берем количество элементов в последовательности
		int countElements = elementsEditField->text().toInt();
		
		//Заполняем массив случайными числами от 100 до 100000
		for (int i=0; i<countElements; i++) {
			array.append(generateRandomNumber(100,100000,QDateTime::currentMSecsSinceEpoch()));
		}
		
		//Запускаем однопоточный режим
		executionWithoutThread(countElements);
		
		//Запускаем многопоточный режим
		executionWithThread(countElements);
		
		//Если данные введены некорректно, то...
		} else {
		//Отображаем пользователю сообщение об ошибке
		messageLbl->setText("Ошибка!Входные данные выходят за границу диапазона.");
	}
}

/**
* @brief mywidget::executionWithoutThread - Режим однопоточного вычисления;
* @param countElements - Количество элементов в последовательности.
*/
void mywidget::executionWithoutThread(int countElements) {
	
    outputField->append("\nОднопоточный режим активирован\nВычисление...");
    timer.start();
	
    qint64 result = 1;
    for (int i=0; i<countElements; i++) {
		result*=array[i];
        QThread::msleep(1);
	}
    outputField->append(tr("Завершено.\nВремя выполнения: ")+
                        QString::number(timer.elapsed())+" мс");
}

/**
* @brief mywidget::executionWithThread - Режим многопоточного вычисления;
* @param countElements - Количество элементов в последовательности.
*/
void mywidget::executionWithThread(int countElements) {
	
    //Берем количество потоков и делим последовательность на участки
    int countThreads = threadsEditField->text().toInt();
    int perThread = countElements / countThreads;
	
    timer.restart();
    stopBtn->setEnabled(true);
    outputField->append("\nМногопоточный режим активирован\nПодготовка задач...");
    timer.start();
	
    //Выделяем участки задачам
    for (int i=0; i<=countThreads-1; i++) {
        Task task;
        task.beginIndex = i*perThread;
        task.endIndex = (i+1)*perThread-1;
        task.listPtr = &array;
        tasks.append(task);
	}
	
    //Создаем обект-наблюдатель
    watcher = new QFutureWatcher<qint64>();
    //Соединяем сигналы со слотами, выполняющими их обработку
    connect(watcher,SIGNAL(progressValueChanged(int)),this,SLOT(progressValueChanged(int)));
    connect(watcher,SIGNAL(finished()),this,SLOT(finished()));
    //Используем контейнер для результата вычислений
    future = QtConcurrent::mappedReduced(tasks, perElementFunc, reduce);
    watcher->setFuture(future);
}

/**
* @brief mywidget::progressValueChanged - Прогресс изменения состояния;
* @param value - Значение состояния в многопоточном вычислении.
*/
void mywidget::progressValueChanged(int value) {
    outputField->append(tr("Прогресс: ")+QString::number(value));
}

/**
* @brief mywidget::finished - Завершение многопоточного вычисления.
*/
void mywidget::finished() {
    outputField->append(tr("Завершено.\nВремя выполнения: ")+
                        QString::number(timer.elapsed())+" мс");
    elementsEditField->setReadOnly(false);
    threadsEditField->setReadOnly(false);
    startBtn->setEnabled(true);
    stopBtn->setEnabled(false);
}

/**
* @brief mywidget::clickClose - Событие нажатия на кнопку "Закрыть".
*/
void mywidget::clickClose() {
	watcher->cancel();
	watcher->waitForFinished();
	close();
}

/**
* @brief mywidget::clickStop - Событие нажатия на кнопку "Остановить".
*/
void mywidget::clickStop() {
	if (watcher->isFinished()) { return; }
	//если наблюдатель на паузе, возобновляем
	if (watcher->isPaused()) {
		watcher->resume();
		outputField->append(tr("Возобновлено..."));
		stopBtn->setText(tr("Остановить"));
		//иначе ставим на паузу
		} else {
        watcher->pause();
        outputField->append(tr("Остановлено..."));
        stopBtn->setText(tr("Возобновить"));
	}
	
}


