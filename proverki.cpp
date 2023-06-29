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
        int separatorsCount = userMdnf.count(separator);    // сколько раз встречается разделитель
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

                if(typeMin == TYPE_MKNF)    // для МКНФ значения инвертируются
                {
                    if(var[n] == 0)
                    {
                        var[n] = 1;
                    }
                    else if(var[n] == 1)
                    {
                        var[n] = 0;
                    }
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

    // проверяем, что введённые пользователем значения, вообще есть на карте покрытия
    for (QString value : formulaValues)
    {
        if(!verticalList.contains(value))    // если значение не содержится в склейках
        {
            qDebug() << "Значение " << value << " не содержится в результатах склейки";
            return false;
        }
    }

    auto checkPokritie = [](QString value, QString skleyka)     // функция, проверяющая, покрывается ли данное значение данной склейкой
    {
        for (int k=0; k<skleyka; k++)      // проходим по каждому символу
        {
            if(skleyka[k] != value[k] && skleyka[k].toUpper() != "X")   // сравниваем каждый символ, если символ отличается и он не Х
            {
                return false;
                break;
            }
        }
        return true;
    };

    QVector<QVector<bool>> pokritie;    // карта покрытия (строим двумерный массив покрытия значений)
    for (int i=0; i<rows; i++)
    {
        QVector<bool> line;   // строка карты покрытия
        QString verticalValue = verticalList[i];    // значение склеек, с которым сравниваем
        for (int j=0; j<cols; j++)
        {
            QString horizontalValue = horizontalList[j];    // значение, с которым сравниваем склейку

            bool correctValue = checkPokritie(horizontalValue, verticalValue);  // проверяем, покрывается ли значение склейкой
            line.append(correctValue);  // добавляем, покрывается значение или нет

            qDebug() << "Значения " << verticalValue << " и " << horizontalValue << (correctValue ? "" : " НЕ ") << " покрываются";

//            if(count <= 1 && verticalValue[position].toUpper() == "X")  // если отличий нет, или отличие в позиции с Х
//            {
//                line.append(true);
//                qDebug() << "Значения " << verticalValue << " и " << horizontalValue << " покрываются";
//            }
//            else    // если не совпадают
//            {
//                line.append(false);
//                qDebug() << "Значения " << verticalValue << " и " << horizontalValue << " НЕ покрываются";
//            }
        }
        pokritie.append(line);  // добавляем строку карты
    }

    qDebug() << "Полученная карта покрытия: " << pokritie;

    // ищем значения, которые составляют ядровую ДНФ
    QStringList coreValues; // список значений, которые являются ядрами

    for (int j=0; j<cols; j++)
    {
        int plusCount = 0;  // кол-во перекрытий в данной колонке
        int position = -1;  // позиция строки, в которой найдено последнее перекрытие
        for (int i=0; i<rows; i++)
        {
            if(pokritie[i][j])  // если значение покрыто
            {
                position = i;
                plusCount++;
            }
        }

        if(plusCount == 1)  // если в столбце только одно перекрытие
        {
            coreValues.append(verticalList[position]);  // добавляем это значение в список ядровых
        }
    }

    coreValues.removeDuplicates();  // удаляем дубликаты

    qDebug() << "Значения, которые формируют ядровую ДНФ: " << coreValues;

    // проверяем, что все ядровые значения присутствуют во введённой, пользователем, формуле
    for (QString core : coreValues)
    {
        if(!formulaValues.contains(core))    // если ядровое значение не содержится в формуле
        {
            qDebug() << "В формуле отсутсвует ядровое значение: " << core;
            return false;
        }
    }

    // ищем значения, которые не покрыты ядрами
    QStringList variativeValues = horizontalList;    // список значений, которые не покрыты ядрами

    // идём по всем ядровым значениям и удаляем покрытые ими
    for (int i=0; i<rows; i++)
    {
        if(coreValues.contains(verticalList[i]))      // если это значение является ядром
        {
            for (int j=0; j<cols; j++)
            {
                if(pokritie[i][j])  // если значение покрывается ядром
                {
                    variativeValues.removeAll(horizontalList[j]);   // убираем значение из списка непокрытых
                }
            }
        }
    }

    qDebug() << "Непокрытые ядрами значения: " << variativeValues;

    // ТУТ КОСТЫЛЬ - по хорошему надо разбить непокрытые значения на группы и понять, какие значения оптимальнее всего выбрать,
    // чтобы использовать минимум переменных, но мы просто проверим, что введённые пользователем значения покрывают непокрытые

    for (QString skleyka : formulaValues)     // берём все значения введённые пользователем
    {
        for (QString value : variativeValues)   // берем все непокрытые значения
        {
            if(checkPokritie(value, skleyka))   // если значение покрывается склейкой
            {
                variativeValues.removeAll(value);   // убираем его из спсика непокрытых
            }
        }
    }

    if(variativeValues.size() > 0)  // если остались непокрытые значения, значит формула не минимальна
    {
        return false;
    }

    return true;    // если все хорошо
}
