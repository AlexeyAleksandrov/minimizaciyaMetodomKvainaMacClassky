#include "mainwindow.h"

bool MainWindow::proverkaTableOfTrue()
{
    allowSave = true; // разрешаем сохранение
    return proverkaTable(tableWidgetTot, mdnf->getSschTableList());
}

bool MainWindow::proverkaOnesOnly()
{
    return proverkaTable(tableWidgetOnesOnlyEditing, mdnf->getListOnes(typeMin));
}

bool MainWindow::proverkaSkleyki(QTableWidget *tableValues, QTableWidget *tableSkleyki)
{
    QStringList values;     // список значений
    QStringList skleyki;    // список склеек

    if(!getTWTextList(tableValues, values))
    {
        return false;
    }
    if(!getTWTextList(tableSkleyki, skleyki))
    {
        return false;
    }
    return proverkaTable(values, skleyki);
}

bool MainWindow::proverkaSkleyki1()
{
    return proverkaSkleyki(tablesWidgetOnes[0], tableWidgetsSkleykiEditing[0]);
//    return proverkaTable(tableWidgetsSkleykiEditing[0], mdnf->getSkleyki1(typeMin), true);
}

bool MainWindow::proverkaSkleyki2()
{
    return proverkaSkleyki(tablesWidgetOnes[1], tableWidgetsSkleykiEditing[1]);
//    return proverkaTable(tableWidgetsSkleykiEditing[1], mdnf->getSkleyki2(typeMin), true);
}

bool MainWindow::proverkaSkleyki3()
{
    return proverkaSkleyki(tablesWidgetOnes[2], tableWidgetsSkleykiEditing[2]);
//    return proverkaTable(tableWidgetsSkleykiEditing[2], mdnf->getSkleyki3(typeMin), true);
}

bool MainWindow::proverkaKartaMinimizacii()
{
    qDebug() << "Проверяем карту минимизации";
    int rows = tableWidgetKartaMinimizacii->rowCount(); // получаем количество строк
    int cols = tableWidgetKartaMinimizacii->columnCount(); // получаем количество строк
    if(!rows || !cols)
    {
//        criticalError("Таблица пустая!");
        qDebug() << "Нет ячеек!";
        return false;
    }
    QStringList horizontalList; // создаем список заголовков столбцов
    for (int i=0; i<cols; i++)
    {
        horizontalList.append(tableWidgetKartaMinimizacii->horizontalHeaderItem(i)->text());
        qDebug() << "horisontal header: " << horizontalList[i];
    }
    QStringList verticalList; // создаем список заголовков строк
    for (int i=0; i<rows; i++)
    {
        verticalList.append(tableWidgetKartaMinimizacii->verticalHeaderItem(i)->text());
        qDebug() << "vertical header: " << verticalList[i];
    }
    qDebug() << "Начинаем проверку.";
    qDebug() << "rows =" << rows << "horizontalList =" << horizontalList.size() << "cols =" << cols << "verticalList =" << verticalList.size();
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            qDebug() << "Цикл " << i << j;
            int count_v = verticalList[i].count(); // количество символов в элементе столбца
            int count_h = horizontalList[j].count(); // количество символов в элементе строки
            if(count_v != count_h) // если количество символов почему-то не совпадает
            {
                qDebug() << "Не совпадает количество элементов строки/столбца" << i << j;
                return false;
            }
            qDebug() << "Проверили на совпадение количества символов";
//            bool *ok = new bool [count_v]; // есть ли совпадение в этом столбце с этой строкой
            int sovpadenie = 0;
            for (int k=0; k<count_v; k++) // проходим по каждому символу
            {
//                qDebug() << "k =" << k << verticalList[i] << horizontalList[j];
                bool ok = ((verticalList[i].at(k) == "X") || (verticalList[i].at(k) == horizontalList[j].at(k))); // сохраняем результат сравнения (true/false)
                sovpadenie += static_cast<int>(ok); // прибавляем результат (+1 если true, +0 если false)
            }
            qDebug() << "Посчитали совпадение";
            QTableWidgetItem *item = tableWidgetKartaMinimizacii->item(i, j); // создаем указатель на ячейку
            if(item == nullptr)
            {
                qDebug() << "Ячейка не существует! Столбец" << j << ", строка" << i;
                return false;
            }
            if(sovpadenie == count_h) // если все символы совпадают
            {
                if(item->text() != "+") // но в карте минимизации этого + нет
                {
                    qDebug() << "Ошибка! " <<  verticalList[i] << horizontalList[j] << "символы совпадают, но нет +";
//                    warningError();
                    return false;
                }
            }
            else // если символы не совпадают, т.е. + быть не должно
            {
                if(item->text() == "+") // но в карте минимизации + есть
                {
                    qDebug() << "Ошибка! " <<  verticalList[i] << horizontalList[j] << "не должно быть +";
//                    warningError();
                    return false;
                }
            }
        }
    }
    return true;
}

bool MainWindow::proverkaItogMdnf()
{
//    if(lineEdit_itogMdnf == nullptr)
//    {
//        qDebug() << "lineEdit_itogMdnf == nullptr";
//        return false;
//    }
//    QString userMdnf = lineEdit_itogMdnf->text(); // получаем текст из строки, куда вводится МДНФ
    QString userMdnf = editor->getFormulaText(); // получаем формулу из редатора
    qDebug() << "МДНФ ввдённая пользователем:" << userMdnf;
    if(userMdnf.isEmpty()) // если строка пустая
    {
//        criticalError("Введите МДНФ в поле ввода!"); // выдаем ошибку
        qDebug() << "Не введена МДНФ";
        return false;
    }
    int skobkaStartCount = 0; // переменная для подсчёта открывающихся скобок - (
    int skobkaEndCount = 0; // переменная для подсчёта закрывающихся скобок - )
    for (int i=0; i<userMdnf.count(); i++)
    {
        if(userMdnf.at(i) == "(")
        {
            skobkaStartCount++;
        }
        if(userMdnf.at(i) == ")")
        {
            skobkaEndCount++;
        }
    }
    if(skobkaStartCount != skobkaEndCount) // если количество скобок разное
    {
        qDebug() << "Количество скобок разное " << skobkaStartCount << skobkaEndCount;
//        warningError("Ошибка! Проверьте скобки!");
        return false;
    }
    if(mdnf->isMnf(userMdnf, typeMin))
    {
//        message();
        return true;
    }
    else
    {
//        warningError();
        return false;
    }
}

// функция проверки итоговой функции МДНФ по карте покрытия
bool MainWindow::proverkaItogMdnfByKartaPokritiya()
{
    // проверяем само выражение на корректность (только скобки)
    QString userMdnf = editor->getFormulaText(); // получаем формулу из редатора
    qDebug() << "МДНФ ввдённая пользователем:" << userMdnf;
    if(userMdnf.isEmpty()) // если строка пустая
    {
        //        criticalError("Введите МДНФ в поле ввода!"); // выдаем ошибку
        qDebug() << "Не введена МДНФ";
        return false;
    }
    int skobkaStartCount = userMdnf.count("("); // переменная для подсчёта открывающихся скобок - (
    int skobkaEndCount = userMdnf.count(")"); // переменная для подсчёта закрывающихся скобок - )
//    for (int i=0; i<userMdnf.count(); i++)
//    {
//        if(userMdnf.at(i) == "(")
//        {
//            skobkaStartCount++;
//        }
//        if(userMdnf.at(i) == ")")
//        {
//            skobkaEndCount++;
//        }
//    }
    if(skobkaStartCount != skobkaEndCount) // если количество скобок разное
    {
        qDebug() << "Количество скобок разное " << skobkaStartCount << skobkaEndCount;
        //        warningError("Ошибка! Проверьте скобки!");
        return false;
    }
    // ДОБАВИТЬ СЮДА ПРОВЕРКУ НА КОРРЕКТНОСТЬ САМОЙ ФОРМУЛЫ

    // превращаем нашу формулу в список наборов цифр - т.е. a^b^!c^d -> 1101
    userMdnf.replace('+', 'v'); // переводим + в дизъюнкцию
    userMdnf.replace('*', '^'); // переводим * в коньюнкцию

    QString separator = typeMin == TYPE_MKNF ? "^" : "v";   // если МКНФ, то разделитель - коньюнкция, если МДНФ - дизъюнкция

    if(typeMin == 0) // если тип МКНФ
    {
        int separatorsCount = skobkaStartCount + skobkaEndCount;
        if(separatorsCount != (skobkaStartCount - 1)) // если количество разделителей не совпадает с количеством скобок (-1, т.к. между 2 скобками будет один разделитель), сравниваем равенство только с количество м одних скобок, т.к. количество разных скобок проверено до этого
        {
            qDebug() << "Не все макстермы выделены в скобки!" << separatorsCount  << skobkaStartCount << skobkaStartCount-1;
                return false;
        }
    }

    qDebug() << "Удаляем лишнее";
    userMdnf.remove(" "); // удаляем пробелы
    userMdnf.remove("("); // убираем скобки
    userMdnf.remove(")");
    userMdnf.remove("");
    qDebug() << "Удалили. Переходим к обработке";

    QStringList userMdnfList = userMdnf.split(separator, Qt::SplitBehavior(Qt::SkipEmptyParts)); // разбиваем строку по коньюнкциям, чтобы получить список с ДНФ
    qDebug() << "разбили на минтермы" << userMdnfList;

    QStringList formulaValues;  // список наборов цифр минтермов из формулы

    for(int i=0; i<userMdnfList.size(); i++) // проходим по каждому минтерму
    {
        int var[4]; // массив для хранения даннх о переменных в минтерме. -1 - переменная отсутствует, 0 - переменная с инверсией, 1 - переменная без инверсии
        for(int j=0; j<4; j++)
        {
            var[j] = -1;
        }
        for(int j=0; j<userMdnfList.at(i).size(); j++) // проходим по каждому значению в минтерме
        {
            QString symvol = userMdnfList.at(i).at(j).toLower(); // сохраняем символ
            if(symvol >= "a" && symvol <= "d") // если символ a-d
            {
//                QString symvol = userMdnfList.at(i).at(j).toLower(); // сохраняем символ
                bool inversion = false; // флаг наличия инверсии у элемента
                if(j != 0) // если элемент не является первым
                {
                    QString lastSymvol = userMdnfList.at(i).at(j-1).toLower(); // предыдущий символ
                    if(lastSymvol == "!") // если предыдущий символ - инверсия
                    {
                        inversion = true;
                    }
                }
//                qDebug() << "i = " << i << " j = " << j << " символ = " << symvol;
                int n = 0; // переменная для хранения номер элемента
                if(symvol == "a")
                    n = 0;
                else if(symvol == "b")
                    n = 1;
                else if(symvol == "c")
                    n = 2;
                else if(symvol == "d")
                    n = 3;
                if(inversion) // если у элемента есть инверсия
                {
                    var[n] = 0; // ставим переменной значение с инверсией
                }
                else
                {
                    var[n] = 1; // ставим значение с инверсией
                }
            }
        }

        // собираем строку из цифр для данного минтерма
        QString mintermValue;   // значение формата 1010
        for(int j=0; j<4; j++)
        {
            mintermValue.append(var[j] >= 0 ? QString::number(var[j]) : "X");   // если значение 0 или 1, то добавляем его, иначе добавляем Х
        }

        // добавляем полученное значение в общий список
        formulaValues.append(mintermValue);
    }

    qDebug() << "Значения, в которые преобразовалась формула: " << formulaValues;

    // считываем карту покрытия
    int rows = tableWidgetKartaMinimizacii->rowCount(); // получаем количество строк
    int cols = tableWidgetKartaMinimizacii->columnCount(); // получаем количество строк
    if(!rows || !cols)
    {
        //        criticalError("Таблица пустая!");
        qDebug() << "Нет ячеек!";
        return false;
    }
    QStringList horizontalList; // создаем список заголовков столбцов
    for (int i=0; i<cols; i++)
    {
        horizontalList.append(tableWidgetKartaMinimizacii->horizontalHeaderItem(i)->text());
        qDebug() << "horisontal header: " << horizontalList[i];
    }
    QStringList verticalList; // создаем список заголовков строк
    for (int i=0; i<rows; i++)
    {
        verticalList.append(tableWidgetKartaMinimizacii->verticalHeaderItem(i)->text());
        qDebug() << "vertical header: " << verticalList[i];
    }
    qDebug() << "Начинаем проверку.";
}
