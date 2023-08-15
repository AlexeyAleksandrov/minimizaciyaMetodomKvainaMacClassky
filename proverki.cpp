#include "mainwindow.h"

bool MainWindow::proverkaTableOfTrue()
{
    allowSave = true; // разрешаем сохранение
    return proverkaTable(tableWidgetTot, getSschTableList());
}

bool MainWindow::proverkaOnesOnly()
{
    return proverkaTable(tableWidgetOnesOnlyEditing, getListOnes(typeMin));
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
    return proverkaTable(values, skleyki) && proverkaAllSkleykiInTable(values, skleyki);    // проверяем, что склейки в таблице покрывают все значения и все значения образуют все возможные склейки
}

bool MainWindow::proverkaSkleyki1()
{
    return proverkaSkleyki(tablesWidgetOnes[0], tableWidgetsSkleykiEditing[0]);
}

bool MainWindow::proverkaSkleyki2()
{
    return proverkaSkleyki(tablesWidgetOnes[1], tableWidgetsSkleykiEditing[1]);
}

bool MainWindow::proverkaSkleyki3()
{
    return proverkaSkleyki(tablesWidgetOnes[2], tableWidgetsSkleykiEditing[2]);
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
            bool result = checkKartaPokritiyaItem(i, j, horizontalList, verticalList);
            if(!result)
            {
                return false;
            }
        }
    }
    return true;
}

// функция проверки итоговой функции МДНФ по карте покрытия
int MainWindow::proverkaItogMdnfByKartaPokritiya()
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

    if(skobkaStartCount != skobkaEndCount) // если количество скобок разное
    {
        qDebug() << "Количество скобок разное " << skobkaStartCount << skobkaEndCount;
        //        warningError("Ошибка! Проверьте скобки!");
        return false;
    }

    // превращаем нашу формулу в список наборов цифр - т.е. a^b^!c^d -> 1101
    userMdnf.replace('+', 'v'); // переводим + в дизъюнкцию
    userMdnf.replace('*', '^'); // переводим * в коньюнкцию

    QString separator = (typeMin == TYPE_MKNF ? "^" : "v");   // если МКНФ, то разделитель - коньюнкция, если МДНФ - дизъюнкция

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

    QStringList userMdnfList = userMdnf.split(separator, SPLITTER); // разбиваем строку по коньюнкциям, чтобы получить список с ДНФ
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
    for (const QString &value : formulaValues)
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
    for (const QString &core : coreValues)
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

    if(variativeValues.size() == 0)     // если нет вариативной части
    {
        return true;
    }

    // простой вариант
//    // Проверяем, что введённые пользователем значения покрывают непокрытые
//    for (const QString &skleyka : formulaValues)     // берём все значения введённые пользователем
//    {
//        for (const QString &value : variativeValues)   // берем все непокрытые значения
//        {
//            if(checkPokritie(value, skleyka))   // если значение покрывается склейкой
//            {
//                variativeValues.removeAll(value);   // убираем его из спсика непокрытых
//            }
//        }
//    }

//    if(variativeValues.size() > 0)  // если остались непокрытые значения, значит формула не минимальна
//    {
//        qDebug() << "Не все значения покрывают формулы покрывают значения функции!";
//        return false;
//    }

    // составим список склеек, которые могут покрыть непокрытые значения
    QStringList variativeSkleyki;
    QStringList skleykiList = verticalList;     // список доступных для использования склеек
    for (QString &core : coreValues)
    {
        skleykiList.removeAll(core);    // удаляем ядровые значения из списка - их нельзя применять
    }

    // ищём склейки, которые могут покрыть недостающие значения
    for (const QString &value : variativeValues)   // берем все непокрытые значения
    {
        for(QString &skleyka : verticalList)    // берём каждую склейку
        {
            if(checkPokritie(value, skleyka))   // если непокрытое знаячение покрывается данной склейкой
            {
                variativeSkleyki.append(skleyka);   // добавляем склейку в список
            }
        }
    }
    variativeSkleyki.removeDuplicates();    // удаляем дубликаты

    /* Берем все значения
     * Составляем map со списком склеек, которые могут покрыть это значение
     * На основе каждого значения формируем списки вариативной части
     */

    // cоставляем map со списком склеек, которые могут покрыть это значение
    QMap<QString, QStringList> variativeValuesPokritieVariants;     // вовзможные варианты покрытия значений

    for (const QString &variativeValue : variativeValues)   // берем все непокрытые значения
    {
        QStringList pokritieVariants;   // список вариантов склеек для покрытия этого значения
        for(QString &skleyka : variativeSkleyki)    // берём каждую вариативную склейку
        {
            if(checkPokritie(variativeValue, skleyka))   // если данное значение покрывается склейкой
            {
                pokritieVariants.append(skleyka);   // доабвляем склейку к списку покрывающих
            }
        }
        variativeValuesPokritieVariants.insert(variativeValue, pokritieVariants);   // добавляем значение и варианты его покрытия
    }

    // составляем списки возможных вариантов значений
    QList<QStringList> variativeVariantsList;   // список состоящий из всех возможных вариантов вариативной части

    for(QString &variativeValue : variativeValuesPokritieVariants.keys())   // делаем перебор всех значений непокрытой вариативной части
    {
        if(variativeVariantsList.isEmpty())     // если сейчас в списке нет ни одного значения
        {
            // добавляем все склейки, покрывающие первое значение
            for(const QString &pokritieVariant : variativeValuesPokritieVariants.value(variativeValue))     // перебор всех склеек, покрывающих данное значение
            {
                variativeVariantsList.append(QStringList() << pokritieVariant);     // добавляем каждую склейку как отдельный вариант
            }
        }
        else    // если в списке уже есть варианты
        {
            // копия нужна для того, чтобы не мешать основному списку добавлением элементовв него
            QList<QStringList> variativeVariantsListCopy = variativeVariantsList;   // копия списка, состоящего из всех возможных вариантов вариативной части

            for(const QStringList &variativeVariants : variativeVariantsListCopy)      // перебираем все уже имеющиеся наборы
            {
                bool valueClosedInThisList = false;     // флаг покрытия этого вариативного значения хоть одной склейкой из текущего набора
                for(const QString &variativeVariant : variativeVariants)   // перебираем все склейки текущего варианта
                {
                    if(checkPokritie(variativeValue, variativeVariant))     // если значение покрывается
                    {
                        valueClosedInThisList = true;   // ставим, что значение покрыто
                        break;
                    }
                }

                // если значение уже покрыто, то ничего нек делаем
                // если значение не покрыто, то надо удаляем из списка вариантов текущий, доабвляем в него все возможные варианты склейи и возвращаем обратно

                if(!valueClosedInThisList)      // если значение не покрыто
                {
                    QStringList variativeVariantsCopy = variativeVariants;      // берем текущий список
                    variativeVariantsList.removeOne(variativeVariantsCopy);     // удаляем текущий набор

                    for(QString skleyka : variativeValuesPokritieVariants.value(variativeValue))    // делаем перебор всех значений, которые покрывают данное значение
                    {
                        QStringList variativeVariantsVariant = variativeVariantsCopy;   // берем текущий список
                        variativeVariantsVariant.append(skleyka);   // добавляем в него текущую склейку, покрывающую это значение
                        variativeVariantsList.append(variativeVariantsVariant);     // добавляем обратно в список вариантов, но уже с новой склейкой
                    }
                }
            }
        }
    }

    // удаляем дубликаты
    auto removeDuplicates = [&](QList<QStringList>& list)
    {
        // создаем список индексов элементов, которые будут удалены
        QList<int> indexesToRemove;

        // проходим по всем парам списков внутри QList
        for (int i = 0; i < list.size(); i++)
        {
            for (int j = i + 1; j < list.size(); j++)
            {
                // проверяем, содержатся ли все элементы текущих списков друг в друге
                if (checkLists(list[i], list[j]))
                {
                    indexesToRemove.append(j);
                }
            }
        }

        // удаляем списки по индексам
        std::sort(indexesToRemove.begin(), indexesToRemove.end(), std::greater<int>());
        for (int index : indexesToRemove)
        {
            list.removeAt(index);
        }
    };

    removeDuplicates(variativeVariantsList);    // удаляем дубюликаты в списке

    qDebug() << "Получено вариантов решения: " << variativeVariantsList.size();

    // =========================================

//    // составляем список приоритетов (чем больше кол-во Х, тем выше приоритет) - чем выше приоритет, тем меньше переменных будет использоваться
//    int maxPriority = 0;    // значение максимального приоритета (по умолчанию - 0)
//    QMap<QString, int> priorities;

//    for(QString &skleyka : variativeSkleyki)    // берём каждую вариативную склейку
//    {
//        int priority = skleyka.toUpper().count("X");    // считаем кол-во Х
//        priorities.insert(skleyka, priority);       // добавляем склейку и приоритет в мап

//        if(maxPriority < priority)  // проверяем максимальный приоритет
//        {
//            maxPriority = priority;
//        }
//        qDebug() << "склейка: " << skleyka << " приоритет: " << priority;
//    }

//    // берем список значений, которые надо покрыть
//    // сначала пробуем покрыть значениями из максимального приоритета
//    // если ни одно значение с максимальным приоритетом не покрывает, снижаем приоритет
//    // составляем список склеек, которые покрывают это значение
//    // для каждого следующего значения проверяем, покрывается ли оно хотя бы одним из уже применённых
//    // если не покрывается, находим значение, которое сможет покрыть

////    // добавляем все значения с максимальным приоритетом
////    for(const QString &skleyka : priorities.keys())     // делаем перебор всех доступных склеек
////    {
////        if(priorities.value(skleyka) == maxPriority)  // если приоритет совпадает с текущим
////        {
////            variativeVariantsList.append(QStringList() << skleyka);     // добавляем значение как список с 1 элементом
////        }
////    }

//    for (int i=0; i<variativeValues.count(); i++)   // берем все непокрытые значения
//    {
//        bool valueClosed = false;   // флаг покрытия значения данным приоритетом
//        for(int p=maxPriority; p>=0; p--)   // берём сначала значения с самым высоким приоритетом
//        {
//            for(const QString &skleyka : priorities.keys())     // делаем перебор всех доступных склеек
//            {
//                if(priorities.value(skleyka) == p)  // если приоритет совпадает с текущим
//                {
//                    if(checkPokritie(variativeValues[i], skleyka))   // если данное значение покрывается склейкой текущего приоритета
//                    {
//                        valueClosed = true;     // ставим флаг, что значение покрыто
//                        if(i == 0)  // если это первое значение, то создаем списки вариантов
//                        {
//                            variativeVariantsList.append(QStringList() << skleyka);     // добавляем список с одним элементом
//                        }
//                        else    // если это не первое значение
//                        {
//                            // смотрим все текущие вариативные части
//                            for (int j=0; j<variativeVariantsList.size(); j++)  // берём все уже имеющиеся варианты
//                            {
//                                bool valueClosedInThisList = false;     // проверем, покрывается ли значение хоть одной склейкой из текущего набора
//                                for(const QString &variantSkleyka : variativeVariantsList[j])      // делаем перебор всех значений в этом наборе
//                                {
//                                    if(checkPokritie(variativeValues[i], variantSkleyka))   // если значение покрывается хотя бы одной склейкой в текущем наборе
//                                    {
//                                        valueClosedInThisList = true;
//                                        break;
//                                    }
//                                }

//                                if(!valueClosedInThisList)  // если значение не покрыто ни одной склейкой в наборе, то добавляем её в набор
//                                {
//                                    variativeVariantsList[j].append(skleyka);
//                                }
//                            }
//                        }
//                    }
//                }
//            }

//            if(valueClosed)     // если значение покрыто хотя бы одним значением из данного приоритета, дальше не ищем
//            {
//                break;
//            }
//        }
//    }

    // ищем только самые минимальные варианты
    // сначала отсеиваем по кол-ву склеек, оставляем только с минимальным кол-вом

    int minSkleykiCount = INT_MAX;
    for (const QStringList &variativeList : qAsConst(variativeVariantsList))   // ищем минимальный размер
    {
        int size = variativeList.size();
        if(size < minSkleykiCount)
        {
            minSkleykiCount = size;
        }
    }

    QList<QStringList> notOptimalVariants;  // список вариантов, которые не являются оптимальными, но при этом верные

    // отсеиваем по кол-ву склеек
    for(int i=0; i<variativeVariantsList.size(); i++)
    {
        if(variativeVariantsList[i].size() > minSkleykiCount)   // если размер списка склеек больше минимального
        {
            qDebug() << "Удаляем вариант решенния: " << variativeVariantsList.at(i) << " т.к. он не оптимальный - кол-во минтермов " << variativeVariantsList[i].size() << " при оптимальном значении " << minSkleykiCount;
            notOptimalVariants.append(variativeVariantsList.at(i));     // добавляем вариант, как не оптимальный, но правильный
            variativeVariantsList.removeAt(i);  // удаляем из списка
            i--;
        }
    }

    qDebug() << "Окончательное кол-во вариантов решения: " << variativeVariantsList.size();
    qDebug() << "Вывод вариативной части:";
    int i = 1;
    for (const QStringList &variativeList : qAsConst(variativeVariantsList))
    {
//        variativeList = coreValues + variativeList;     // доабвляем ядровую часть к вариативной
        qDebug() << "Решение №" << i++ << ": " << coreValues + variativeList;
    }

    // выделяем вариативную часть формулы
    QStringList variativePartOfFormula = formulaValues;     // список вариативных значений формулы
    for(const QString &core : qAsConst(coreValues))
    {
        variativePartOfFormula.removeAll(core);     // удаляем ядровые значения
    }

    // проверка на кол-во минтермов в формуле
    if(formulaValues.size() != (coreValues.size() + minSkleykiCount))
    {
        qDebug() << "Кол-во минтермов/макстермов в формуле не соответсвует минимальному значени: " << formulaValues.size() << (coreValues.size() + minSkleykiCount);

        // проверяем, что введённая пользователоем формула соответствует одной из неоптимальных
        for (const QStringList &variativeList : qAsConst(notOptimalVariants))
        {
            bool compare = true;
            for(const QString &variant : variativeList)    // перебираем все значения внутри варианта вариативной части
            {
                if(!variativePartOfFormula.contains(variant))   // проверяем, содержится ли вариативное значение в формуле
                {
//                    qDebug() << "Вариативная часть " << variant << " не содержится в формуле " << variativeList;
                    compare = false;
                    break;
                }
            }

            if(compare) // если вариативная часть совпадает, значит решение правильное
            {
                return -1;  // возвращаем, что формула не оптимальная
            }
        }

        return false;
    }

    // проверяем, что введённая пользователоем формула соответствует одной из вариативных
    for (const QStringList &variativeList : qAsConst(variativeVariantsList))
    {
        bool compare = true;
        for(const QString &variant : variativeList)    // перебираем все значения внутри варианта вариативной части
        {
            if(!variativePartOfFormula.contains(variant))   // проверяем, содержится ли вариативное значение в формуле
            {
//                qDebug() << "Вариативная часть " << variant << " не содержится в формуле " << variativeList;
                compare = false;
                break;
            }
        }

        if(compare) // если вариативная часть совпадает, значит решение правильное
        {
            return true;
        }
    }

    qDebug() << "Пользовательская фнукция: " << formulaValues;
    return false;    // если проверки не были пройдены
}
