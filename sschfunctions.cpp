#include "mainwindow.h"

bool MainWindow::to2ssch(QString number16, QString &number2)
{
    int razryad = number16.count(); // получаем количество разрядов числа
    if(razryad == 0) // если пустая строка
    {
        return false;
    }
    bool ok; // флаг перевода
    int ch10 = number16.toInt(&ok, 16); // переводим число из 16й в 10ю ССЧ
    if(!ok) // если число не переводится выдаем ошибку
    {
        return false; // не переводится
    }
    QString ch2 = QString::number(ch10, 2); // переводим число из 10й в 2ю ССЧ
    int count = ch2.count(); // определяем количество знаков
    int razryad2;
//    razryad2 = static_cast<int>(pow(2, razryad)); // получаем количество разрядов, которое должно быть в 2й записи числа
    razryad2 = 4 * razryad; // получаем количество разрядов, которое должно быть в 2й записи числа
    if(count < razryad2) // если количество разрядов после перевода меньше (int отбрасывает незначащие нули), то добавляем нули вперед до нужного количества
    {
        int k = razryad2 - count; // считаем количество нулей, котрое надо добавить
        for (int i=0; i<k; i++)
        {
            ch2 = "0" + ch2; // добавляем нули
        }
    }
    number2 = ch2; // возвращаем переведенное число
    return true; // перевод успешный
}

bool MainWindow::to16ssch(QString number2, QString &number16)
{
    if(number2 == "")
    {
        return false;
    }
    bool ok = false;
    int num10 = number2.toInt(&ok, 2); // переводим в 10 ССЧ
    if(!ok)
    {
        return false;
    }
    number16 = QString::number(num10, 16);
    return true;
}

QStringList MainWindow::getSschTableList()
{
    // переводим число в 2 ССЧ
    QString ch2;
    if(!to2ssch(function_16, ch2)) // проверяем перевод в 2ю ССЧ
    {
        //СКРЫТО qDebug() << "Введена не 16-я функция!\nПроверьте правильность ввода!";
//        error = "Введена не 16-я функция!\nПроверьте правильность ввода!";
        return QStringList();
    }
    int razryad = function_16.count(); // поличество разрядов в исходном числе
    //СКРЫТО qDebug() << ch2; // выводим результат перевода
    //СКРЫТО qDebug() << "=======";
    // заносим в таблицу нашу функцию
    // определяем, сколько переменных нужно, чтобы описать функцию
    QStringList funcList = ch2.split("", SPLITTER); // разбиваем число в 2й ССЧ на символы
    int rowsTot = static_cast<int>(4 * razryad); // умножаем 4 (т.к. у нас 16-я ССЧ и она содержит по 4 двоичных разряда в числе) на количество разрядов числа и получаем количество строк
    double stepen = log2(rowsTot); // получаем, в какую степень над овозвести число 2, чтобы получить такую длину числа
    if(abs(stepen - static_cast<double>(static_cast<int>(stepen))) > 0.0) // если степень не целая
    {
        stepen = static_cast<double>(static_cast<int>(stepen)); // откидываем дробную часть
        stepen += 1.0; // прибавляем 1
    }
    int colsTot = static_cast<int>(stepen) + 1;// количство столбцов равно степени в которую надо возвезти 2, чтобы получить количество строк + 1 для функции
    if(!rowsTot || !colsTot)
    {
        return QStringList();
    }
    QStringList sschTableList;
    for (int i=0; i<rowsTot; i++)
    {
        QString num = QString::number(i, 2); // перевод из 10 в 16
        while (num.count() < colsTot-1) // пока количество разрядов меньше, чем количество колонок -1, т.к. последняя колонка это значение функции
        {
            num = "0" + num;
        }
        //СКРЫТО qDebug() << num;
        sschTableList.append(num);
    }
    int sschTableListSize = sschTableList.size();
    for (int i=0; i<sschTableListSize; i++)
    {
        sschTableList[i] = sschTableList[i] +  funcList[i]; // добавляем значение функции к элементу таблицы истинности
    }
    //СКРЫТО qDebug() << "закончено";
//    allowTot = true; // сохраняем, что таблица истинности рассчитана
    return sschTableList;
}

QStringList MainWindow::getListOnes(int type)
{
    // переводим число в 2 ССЧ
    QString ch2;
    if(!to2ssch(function_16, ch2)) // проверяем перевод в 2ю ССЧ
    {
        //СКРЫТО qDebug() << "Введена не 16-я функция!\nПроверьте правильность ввода!";
//        error = "Введена не 16-я функция!\nПроверьте правильность ввода!";
        return QStringList();
    }
    int razryad = function_16.count(); // поличество разрядов в исходном числе
    //СКРЫТО qDebug() << ch2; // выводим результат перевода
    //СКРЫТО qDebug() << "=======";
    // заносим в таблицу нашу функцию
    // определяем, сколько переменных нужно, чтобы описать функцию
    QStringList funcList = ch2.split("", SPLITTER); // разбиваем число в 2й ССЧ на символы
    int rowsTot = static_cast<int>(4 * razryad); // умножаем 4 (т.к. у нас 16-я ССЧ и она содержит по 4 двоичных разряда в числе) на количество разрядов числа и получаем количество строк
    double stepen = log2(rowsTot); // получаем, в какую степень над овозвести число 2, чтобы получить такую длину числа
    if(abs(stepen - static_cast<double>(static_cast<int>(stepen))) > 0.0) // если степень не целая
    {
        stepen = static_cast<double>(static_cast<int>(stepen)); // откидываем дробную часть
        stepen += 1.0; // прибавляем 1
    }
    int colsTot = static_cast<int>(stepen) + 1;// количство столбцов равно степени в которую надо возвезти 2, чтобы получить количество строк + 1 для функции
    if(!rowsTot || !colsTot)
    {
        return QStringList();
    }
    QStringList sschTableList;
    for (int i=0; i<rowsTot; i++)
    {
        QString num = QString::number(i, 2); // перевод из 10 в 16
        while (num.count() < colsTot-1) // пока количество разрядов меньше, чем количество колонок -1, т.к. последняя колонка это значение функции
        {
            num = "0" + num;
        }
        //СКРЫТО qDebug() << num;
        sschTableList.append(num);
    }
    int sschTableListSize = sschTableList.size();
    QStringList ones;
    for (int i=0; i<sschTableListSize; i++)
    {
        if(funcList[i].toInt() == type)
        {
            ones.append(sschTableList[i]);  // добавляем значение функции к списку подходящих
        }
    }
    //СКРЫТО qDebug() << "закончено";
//    allowTot = true; // сохраняем, что таблица истинности рассчитана
    return ones;
}
