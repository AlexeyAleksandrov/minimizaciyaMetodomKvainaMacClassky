#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define OPTYMIZE_TYPE_ONLY
//#define CUSTON_INPUT_FUNCTION

//#define RED_COLOR_FOR_CORES_ONLY    // если выбран данный флаг, то закрашивать красным цветом можно только ядра, инче - все значения
//#define ENABLE_AUTO_CHECK_KORRECT_KATRA_POKRITIYA   // включение проверки на лету правильности устанвоки + в карту покрытия

/**
Конструктор главного окна. @param parent Указатель на родительское окно
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ставим запрет на изменение размера
    //    auto sizeui = ui->centralWidget->geometry();
    this->setFixedWidth(geometry().width());
    this->setFixedHeight(geometry().height());
    this->setMaximumWidth(geometry().width());
    this->setMaximumHeight(geometry().height());

    editor = new LogicEditor(ui->tableWidget_formulaEditor);
    //    editor->setEditChoseItem(true);
    //    editor->setAutoInput(false); // включаем автоматический ввод выражения
    setAutoInput(false); // включаем автоматический ввод выражения


    qDebug() << "задаем Nullptr";
    pushButton_nextStep_tot = nullptr;
    lineEditFunc_2 = nullptr;
    lineEditFunction = nullptr;
    tableWidgetTot = nullptr;
    tableWidgetOnesOnly = nullptr;
    tableWidgetsSkleyki = nullptr;
    tableWidgetOnesOnlyEditing = nullptr;
    tableWidgetKartaMinimizacii = nullptr;
    tabWidget = nullptr;

    // ставим отключение некотиорых кнопок, действие которых было заменено
    ui->pushButton_func_2->setVisible(false);
    ui->checkBox_spiltToTetrads->setChecked(true);

    qDebug() << "Прираниваем значения";
    pushButton_nextStep_tot = ui->pushButton_nextStep_tot;
    pushButton_proverka_karta_minimizacii = ui->pushButton_proverka_result_function;
    pushButton_add_skleyki_2 = ui->pushButton_add_skleyki_2;
    pushButton_proverka_karti_minimizacii = ui->pushButton_proverka_karti_minimizacii;

    tableWidgetTot = ui->tableWidget_tableOfTrue;
    tableWidgetOnesOnly = ui->tableWidget_one_only;
    tableWidgetOnesOnlyEditing = ui->tableWidget_one_only_editing;
    tableWidgetKartaMinimizacii = ui->tableWidget_kartaMinimizacii;

    lineEditFunction = ui->lineEdit_function;
    lineEditFunc_2 = ui->lineEdit_func_2;
    checkBox_spiltToTetrads = ui->checkBox_spiltToTetrads;
    //    lineEdit_itogMdnf = ui->lineEdit_itogMdnf;

    tabWidget = ui->tabWidget;

    qDebug() << "Conntects tot";
    // таблица истинности
    connect(ui->pushButton_func_2, SIGNAL(clicked()), this, SLOT(pushButtonFunc2Clicked()));
    qDebug() << "pushButton_func_2";
    connect(ui->pushButton_proverka_skleyki_3, SIGNAL(clicked()), this, SLOT(pushButton_proverka_skleyki_2_clicked()));

    checkBox_autoInputFormula = ui->checkBox_autoInputFormula;
    checkBox_editChoseItemFormula = ui->checkBox_editChoseItemFormula;

    tableWidgetsSkleyki = new QTableWidget *[2]; // выделяем память под 3 таблицы
    tableWidgetsSkleyki[0] = ui->tableWidget_skleiki_1;
    tableWidgetsSkleyki[1] = ui->tableWidget_skleiki_2;
    //    tableWidgetsSkleyki[2] = ui->tableWidget_skleiki_3;

    tableWidgetsSkleykiEditing = new QTableWidget *[3];
    tableWidgetsSkleykiEditing[0] = ui->tableWidget_skleiki_1_editing;
    tableWidgetsSkleykiEditing[1] = ui->tableWidget_skleiki_2_editing;
    tableWidgetsSkleykiEditing[2] = ui->tableWidget_skleiki_3_editing;

    tableWidget_formulaEditor = ui->tableWidget_formulaEditor;
    tableWidget_kartaMinimizacii = ui->tableWidget_kartaMinimizacii;

    tablesWidgetOnes = new QTableWidget*[3];
    tablesWidgetOnes[0] = ui->tableWidget_one_only;
    tablesWidgetOnes[1] = ui->tableWidget_skleiki_1;
    tablesWidgetOnes[2] = ui->tableWidget_skleiki_2;

    qDebug() << "Задаем видимость";

    qDebug() << "МДНФ";
//    mdnf = nullptr;
    qDebug() << "Обнуляем MDNF";
    tabWidget->setCurrentIndex(0);

    pushButton_func_2 = ui->pushButton_func_2;
    pushButton_checkTableOfTrue = ui->pushButton_checkTableOfTrue;
//    pushButton_tot_add = ui->pushButton_tot_add;
    pushButton_proverka_oneOnly = ui->pushButton_proverka_oneOnly;
    pushButton_tot_add_to_skeyki_1 = ui->pushButton_tot_add_to_skeyki_1;
//    pushButton_clear_skleiki_1_editing = ui->pushButton_clear_skleiki_1_editing;
    pushButton_proverka_skleiki_1_editing = ui->pushButton_proverka_skleiki_1_editing;
    pushButton_nextStep_onesOnly = ui->pushButton_nextStep_onesOnly;
    pushButton_add_skleyki_1 = ui->pushButton_add_skleyki_1;
//    pushButton_clear_skleiki_2_editing = ui->pushButton_clear_skleiki_2_editing;
    pushButton_proverka_skleyki_3 = ui->pushButton_proverka_skleyki_3;
    pushButton_nextStep_skleyki_2 = ui->pushButton_nextStep_skleyki_2;
    pushButton_add_skleyki_2 = ui->pushButton_add_skleyki_2;
//    pushButton_clearSkleyki_2 = ui->pushButton_clearSkleyki_2;
    pushButton_proverka_skleyki_2 = ui->pushButton_proverka_skleyki_3_0;
    pushButton_nextStep_onesOnly_3 = ui->pushButton_nextStep_onesOnly_3;
    pushButton_tot_move_to_skeyki_1 = ui->pushButton_tot_move_to_skeyki_1;
    pushButton_tot_move_to_skeyki_2 = ui->pushButton_tot_move_to_skeyki_2;
    pushButton_tot_move_to_skeyki_3 = ui->pushButton_tot_move_to_skeyki_3;
    pushButton_setRedColor = ui->pushButton_setRedColor;
    pushButton_setGreenColor = ui->pushButton_setGreenColor;
    pushButton_setWhiteColor = ui->pushButton_setWhiteColor;
    //    pushButton_loadDataFromFile = ui->pushButton_loadDataFromFile;

    // редактор формул
    pushButton_INV = ui->pushButton_INV;
    pushButton_INV->setVisible(false); // выключаем кнопку показа инверсии, т.к. она была заменена на символы с инверсией
    pushButton_A = ui->pushButton_A;
    pushButton_B = ui->pushButton_B;
    pushButton_C = ui->pushButton_C;
    pushButton_D = ui->pushButton_D;
    pushButton_AND = ui->pushButton_AND;
    pushButton__OR = ui->pushButton__OR;
    pushButton_SKOBKA_BEFORE = ui->pushButton_SKOBKA_BEFORE;
    pushButton_SKOBKA_AFTER = ui->pushButton_SKOBKA_AFTER;
    pushButton_DEL = ui->pushButton_DEL;
    pushButton_CLEAR = ui->pushButton_CLEAR;
    pushButton_notA = ui->pushButton_notA;
    pushButton_notB = ui->pushButton_notB;
    pushButton_notC = ui->pushButton_notC;
    pushButton_notD = ui->pushButton_notD;

    // блокируем все кнопки до выбора варианта
    // этап 0 (ввод функции в векторном формате)

    setStep(step); // задаём нулевой этап, т.е. ничего не выбрано
    //    ui->pushButton_

#ifndef CUSTON_INPUT_FUNCTION
    ui->pushButton_enterFunction->setVisible(false); // отключаем отображение кнопки, в связи с ненадобностью
    lineEditFunction->setReadOnly(true); // блокируем ввод в поле функции
#endif

    // для карты покрытия
    redColor = new QColor(255,101,96);          // красный цвет
    greenColor = new QColor(185,255,141);       // зеленый цвет
    yellowColor = new QColor(255, 253, 208);    // желтый цвет

    //    pushButton_loadDataFromFile->setVisible(false); // выключаем видимость кнопки загрузки решения из уже начатой работы
}

/**
Конструктор главного окна. @param parent Указатель на родительское окно
*/
MainWindow::~MainWindow()
{
    if(allowSave) // если разрешено сохранение
    {
        saveDataToFile(); // сохраняем данные
    }
    delete ui;
}

/**
 * @brief Устанавливает значение функции.
 * @param function Функция в формате QString.
 */
void MainWindow::setFunction(QString function)
{
    //    QString text = lineEditFunction->text(); // берем текст функции
    if(function == "") // проверяем на пустоту
    {
        //        QMessageBox::critical(this, "Ошибка", "Поле ввода функции пустое!");
        criticalError("Поле ввода функции пустое!");
        return;
    }
    QString ch2;
    if(!to2ssch(function, ch2)) // проверяем перевод в 2ю ССЧ
    {
        QMessageBox::critical(this, "Ошибка", "Введена не 16-я функция!\nПроверьте правильность ввода!");
        return;
    }
    function_16 = function; // сохраняем функцию
    lineEditFunction->setText(function); // выводим функцию
    int razryad = function.count(); // поличество разрядов в исходном числе
    qDebug() << ch2; // выводим результат перевода
    qDebug() << "=======";
    setTableStepenTwo(razryad);
    qDebug() << "Количество строк " <<  tableWidgetTot->rowCount();
    qDebug() << "Количество столбцов " <<  tableWidgetTot->columnCount();

    setTableOfTrueNumbers(); // создаем таблицу истиности (заполняем числами от 0 до N в 2й ССЧ)
    // заносим в таблицу нашу функцию
    QStringList funcList = ch2.split(""); // разбиваем число в 2й ССЧ на символы
//    if(mdnf != nullptr)
//    {
//        delete mdnf;
//        mdnf = nullptr;
//    }
//    qDebug() << "Проверили mdnf";
//    mdnf = new mdnfMacKlassky; // создаем МДНФ
//    if(!mdnf->setFunction(function)) // если не удаётся рассчитать
//    {
//        QMessageBox::critical(this, "Program ERROR", "Неожиданная ошибка при вычислении МНФ!");
//        qDebug() << "Ошибка";
//        return;
//    }
    // =================================================================
    qDebug() << "Отчищаем талицы";
    clearTW(tableWidgetOnesOnly);
    qDebug() << "Таблица с 1 очищена";
    clearTW(tableWidgetOnesOnlyEditing);
    qDebug() << "Таблица с 1 для редактирования очищена";
    for (int i=0; i<2; i++)
    {
        clearTW(tableWidgetsSkleyki[i]);
        qDebug() << "Таблица со склейками " << i << "очищена";
        clearTW(tableWidgetsSkleykiEditing[i]);
        qDebug() << "Таблица со склейками для редактирования" << i << "очищена";
    }
    clearTW(tableWidgetsSkleykiEditing[2]);
    clearTW(tableWidgetKartaMinimizacii);
    qDebug() << "Таблица карты минимизации очищена";
    qDebug() << "Талицы отчищены";
    step = 0;
    setStep(step);// переходим к следующему шагу

    addCheckBoxesInLastColumn(tableWidgetTot, checkBoxes);  // добавляем checkBox для таблицы истинности
    // соединяем слот stateChenged
    int rows = tableWidgetTot->rowCount();
    for (int i=0; i<rows; i++)
    {
        connect(checkBoxes[i], &QCheckBox::stateChanged, this, &MainWindow::updateCheckBoxTotState); // соединяем сигнал изменения состояния с нажатием на кнопку добавить
    }

    nextStep();
    nextStep(); // увеличваем шаг на 2, из-за ошибки

    setSklykiResultTableColor(tableWidgetTot);  // делаем таблицу более тусклой
    clearSelectionAdDisableClickTableWidget(tableWidgetTot);    // убираем выделение и блокируем таблицу
}

void MainWindow::criticalError(QString error)
{
    if(noMessage) // если включена блокировка на отправлку сообщений
    {
        return;
    }
    QMessageBox::critical(this, "Ошибка", error);
}

void MainWindow::warningError(QString error)
{
    if(noMessage) // если включена блокировка на отправлку сообщений
    {
        return;
    }
    QMessageBox::warning(this, "Ошибка", error);
}

void MainWindow::message(QString message, QString title)
{
    if(noMessage) // если включена блокировка на отправлку сообщений
    {
        return;
    }
    QMessageBox::information(this, title, message);
}

/**

@brief Проверяет, содержит ли каждый элемент в первом QStringList второй QStringList.
@param firstList Первый QStringList для сравнения.
@param secondList Второй QStringList для сравнения.
@return true, если каждый элемент первого списка содержится во втором списке, иначе false.
*/
bool MainWindow::isAllElementsFirstQStrlingListContainsInSecondQStringList(QStringList firstList, QStringList secondList)
{
    bool ok = true; // флаг проверки наличия данной склейки в рассчитанном списке
    for (int i=0; i<firstList.size(); i++)  // сравниваем каждый элемент первого списка
    {
        bool contained = false;
        for (int j=0; j<secondList.size(); j++)  // с каждым элементом второго списка
        {
            if(firstList.at(i) == secondList.at(j)) // если элементы равны
            {
                contained = true; // сохраняем, что этот элемент найден
            }
        }
        if(!contained) // если элемент не содержится
        {
            ok = false; // то сохрняем, что есть ошибка
            break; // дальше нет смысла проверять
        }
    }
    return ok;
}

void MainWindow::setStudentName(const QString &value)
{
    studentName = value;
}

void MainWindow::setStudentGroup(const QString &value)
{
    StudentGroup = value;
}

void MainWindow::loadDataFromFile()
{
    noMessage = true; // отключаем показ подсказок
    readDataFromFile(); // считываем данные из файла
    qDebug() << "выводим выражение в редактор " << itogMdnfTextLine;
    editor->setFormula(itogMdnfTextLine); // выводим выражение в редактор
    noMessage = false; // включаем показ подсказок
    allowSave = true; // разрешаем сохранение
}

void MainWindow::setNoMessage(bool value)
{
    noMessage = value;
}


//void MainWindow::pushButtonAddTSkeyki_1() // кнопка добавления склейки на основе таблицы со значениями, где функция принимает значение 1
//{
//    createSkleyka(tableWidgetOnesOnly, checkBoxes_ones, tableWidgetsSkleykiEditing[0], 1); // создаем склейку и добавляем её в таблицу
//}

//void MainWindow::pushButton_add_skleyki_2_clicked()
//{

//}

void MainWindow::pushButton_add_skleyki_3_clicked() // кнопка создания 3й склейки
{
    createSkleyka(tableWidgetsSkleyki[1], checkBoxes_skleyki_2, tableWidgetsSkleykiEditing[2]); // создаем склейки 3
}

void MainWindow::pushButton_clear_skleyki_1() // кнопка отчистки таблицы со склейками 1
{
    clearTW(tableWidgetsSkleykiEditing[0]); // отчищаем таблицу
}

void MainWindow::pushButton_clear_skleyki_2()
{
    clearTW(tableWidgetsSkleykiEditing[1]); // отчищаем таблицу
}

//void MainWindow::pushButton_proverka_skleyki_1_clicked()
//{


//}

void MainWindow::pushButton_delete_last_skleiki_1_editingClicked() // кнопка удаления последней добавленной склейки в таблице склеек 1
{
    deletelastRow(tableWidgetsSkleykiEditing[0]); // удалаяем последнюю строку в таблице склеек 1
}

//void MainWindow::pushButton_nextStep_tot_2Clicked() // переход от 1й склейки ко 2й
//{

//}

void MainWindow::pushButton_proverka_skleyki_2_clicked()
{
    if(proverkaSkleyki2()) // если все нормально при проверке
    {
        message();
        nextStep();
    }
    else
    {
        warningError();
    }
}

void MainWindow::pushButton_delete_last_skleiki_2_editingClicked()
{
    deletelastRow(tableWidgetsSkleykiEditing[1]); // удалаяем последнюю строку в таблице склеек 2
}

//void MainWindow::pushButton_nextStep_skleyki_2Clicked()
//{

//}

void MainWindow::pushButton_clear_skleyki_3()
{
    clearTW(tableWidgetsSkleykiEditing[2]);
}

//void MainWindow::pushButton_proverka_skleyki_3_clicked()
//{
//    proverkaTable(tableWidgetsSkleykiEditing[2], mdnf->getSkleyki3(typeMin));
//}

void MainWindow::pushButton_delete_last_skleiki_3_editingClicked()
{
    deletelastRow(tableWidgetsSkleykiEditing[2]); // удалаяем последнюю строку в таблице склеек 3
}

/**

@brief Устанавливает цвет карты.
@param color Цвет, который нужно установить.

Функция устанавливает цвет ячеек таблицы tableWidget_kartaMinimizacii в соответствии с определенными правилами.
Если таблица tableWidget_kartaMinimizacii не существует или не содержит строк или колонок, функция завершается.

Функция определяет, является ли данное значение ядром, используя лямбда-функцию checkCore.
Внутри нее определяется количество плюсов в столбце и позиция (строка) последнего плюса.

Функция покраски ячеек setItemColor устанавливает цвет ячейки в соответствии с переданным цветом.
Устанавливается белый или красный цвет, или зеленый, но только если ячейка не выделена красным цветом.

Функция fillCorePokritie выделяет все значения, покрываемые ядром. Если значение не является ядром, она просто завершается.
Внутри функции идет проход по всем столбцам и строкам, при котором ячейки, соответствующие ядру, закрашиваются в зеленый цвет.

Функция проходит по всем ячейкам таблицы и, если ячейка существует и выделена, выполняет определенные действия.
Если выделенное значение не является ядром (красного цвета), функция проверяет, является ли значение ядром.
Если значение является ядром, все значения, покрытые ядром, закрашиваются в зеленый цвет.
Если значение не является ядром, устанавливается флаг showCoreErrorMessage и пропускается значение.
Если showCoreErrorMessage установлен в true, выводится предупреждающее сообщение.

В конце функции выделение снимается и, при наличии флага showCoreErrorMessage, выводится сообщение об ошибке выделения ядер.
*/
void MainWindow::setKartaColor(QColor color)
{
    if(tableWidget_kartaMinimizacii == nullptr)
    {
        return;
    }
    int rows = tableWidget_kartaMinimizacii->rowCount(); // получаем количество строк
    int cols = tableWidget_kartaMinimizacii->columnCount(); // получаем колдичество колонок
    if((rows == 0) || (cols == 0))
    {
        return;
    }

    // функция проверки, является ли данное значения ядром
    auto checkCore = [&](int i, int j)
    {
        int pos = -1;   // позиция (строка) последнего +
        int count = 0;  // кол-во + в столбце

        for (int k = 0; k < rows; k++)
        {
            if(tableWidget_kartaMinimizacii->item(k, j) != nullptr) // если ячейка существует
            {
                if(tableWidget_kartaMinimizacii->item(k, j)->text() == "+") // если значение +
                {
                    pos = k;
                    count++;
                }
            }
        }

        return (count == 1 && i == pos);    // если кол-во + равно 1 и позиция + совпадает с проверяемым, то значение является ядром
    };

    // функция покраски ячейки
    auto setItemColor = [&](int i, int j, QColor color)
    {
        if ((color == Qt::white || color == *redColor || color == *yellowColor) || ((color == *greenColor) && (tableWidget_kartaMinimizacii->item(i, j)->background() != *redColor) && (tableWidget_kartaMinimizacii->item(i, j)->background() != *yellowColor))) // необходимо установить белый или красный цвет, или зеленый, но при том, что ячейка не выделена красным
        {
            tableWidget_kartaMinimizacii->item(i, j)->setBackground(color); // устанавливаем цвет
        }
    };

    // функция, выделяющая все значения, покрывающееся ядром
    auto fillCorePokritie = [&](int i, int j)
    {

//#ifdef RED_COLOR_FOR_CORES_ONLY
//        if(!checkCore(i, j))    // если значение не является ядром
//        {
//            return;
//        }
//#else
        if(tableWidget_kartaMinimizacii->item(i, j) == nullptr || tableWidget_kartaMinimizacii->item(i, j)->text() != "+") // если ячейка не существует или пустая
        {
            return;
        }
//#endif

        // закрашиваем все значения, покрываемые ядром
        for (int col=0; col<cols; col++)
        {
            if(tableWidget_kartaMinimizacii->item(i, col) != nullptr) // если ячейка существует
            {
                setItemColor(i, col, *greenColor);    // закрашиваем ячейку в зелёный цвет

                // смотрим, есть ли значения
                if(tableWidget_kartaMinimizacii->item(i, col)->text() == "+")   // если ячейка существует и в ней стоит +
                {
                    for (int row=0; row<rows; row++)  // идем по всем строчкам в этом столбце
                    {
                        setItemColor(row, col, *greenColor);    // закрашиваем в зелёный цвет
                    }
                }
            }
        }
    };

    // закрашивание выбранных ячеек
    bool showCoreErrorMessage = false;  // флаг, надо ли показать ошибку выдления ядер

    // проверка корректности выделенного диапазона
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if(tableWidget_kartaMinimizacii->item(i, j) != nullptr) // если ячейка существует
            {
                if(tableWidget_kartaMinimizacii->item(i, j)->isSelected()) // если выделен
                {
                    if(color == *redColor)   // если выделенное значение не является ядром, но оно должно быть закрашено
                    {
                        if(!checkCore(i, j)) // если значение является ядром
                        {
                            warningError("Выделенные значения не являются ядрами!");
                            return;
                        }
                    }
                    else if(color == *yellowColor)  // если мы хотим выделить вариативную часть
                    {
                        if(tableWidget_kartaMinimizacii->item(i, j) == nullptr || tableWidget_kartaMinimizacii->item(i, j)->text() != "+" || tableWidget_kartaMinimizacii->item(i, j)->background() != Qt::white || checkCore(i, j)) // если ячейка не существует, пустая или является ядром
                        {
                            warningError("Одно или несколько выделенных значений не могут быть исполльзованы для формирования вариативной части!");
                            return;
                        }
                    }
                }
            }
        }
    }

    // закраска
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            if(tableWidget_kartaMinimizacii->item(i, j) != nullptr) // если ячейка существует
            {
                if(tableWidget_kartaMinimizacii->item(i, j)->isSelected()) // если выделен
                {
                    if(color == *redColor)   // если выделенное значение не является ядром, но оно должно быть закрашено
                    {
//#ifdef RED_COLOR_FOR_CORES_ONLY
                        if(checkCore(i, j)) // если значение является ядром
                        {
                            fillCorePokritie(i, j);     // закрашиваем все значения, которые покрываются ядром
                        }
                        else
                        {
                            showCoreErrorMessage = true;    // ставим флаг и пропускаем значение
                            break;
                        }
//#else
//                        fillCorePokritie(i, j);     // закрашиваем все значения, которые покрываются ядром
//#endif
                    }
                    else if(color == *yellowColor)  // если мы хотим выделить вариативную часть
                    {
                        if(tableWidget_kartaMinimizacii->item(i, j) == nullptr || tableWidget_kartaMinimizacii->item(i, j)->text() != "+") // если ячейка не существует или пустая
                        {
                            showCoreErrorMessage = true;    // ставим флаг и пропускаем значение
                            break;
                        }
                        else if(tableWidget_kartaMinimizacii->item(i, j)->background() == Qt::white) // если ячейка без выделения
                        {
                            fillCorePokritie(i, j);     // закрашиваем все значения, которые покрываются ядром
                        }
                        else
                        {
                            showCoreErrorMessage = true;    // ставим флаг и пропускаем значение
                            break;
                        }
                    }
//#ifdef RED_COLOR_FOR_CORES_ONLY
                    setItemColor(i, j, color);  // задаем цвет
//#else
//                    if(color == *redColor && !checkCore(i, j))  // если мы хотим выделить ядро, но значение ядром не является
//                    {
//                        setItemColor(i, j, *yellowColor);  // задаем цвет
//                    }
//                    else
//                    {
//                        setItemColor(i, j, color);  // задаем цвет
//                    }
//#endif
                }
            }
        }
    }

    // убирам выделение
    clearSelectionAdDisableClickTableWidget(ui->tableWidget_kartaMinimizacii);

//    // показываем сообщение об ошибки выделения ядер
//    if(showCoreErrorMessage)
//    {
//        warningError("Выделенное значение не является ядром!");
//    }
}

void MainWindow::pusbButton_move_skleyki_to_coresTable() // кнопка переноса склеек в таблицу
{
    qDebug() << "END << Start";
    int nomerSkleyki = 0; // Хранит номер последней склейки
    //    if(tableWidgetsSkleyki[2]->rowCount() > 0) // если количество строк в таблице склеек больше 0, т.е. склейки есть
    //    {
    //        nomerSkleyki = 3; // запоминаем 3ю склейку
    //    }
    //    else
    if(tableWidgetsSkleyki[1]->rowCount() > 0)
    {
        nomerSkleyki = 2;
    }
    else if (tableWidgetsSkleyki[0]->rowCount() > 0)
    {
        nomerSkleyki = 1;
    }
    if(nomerSkleyki == 0)
    {
        criticalError("Вы не выполнили ни одной склейки!");
        qDebug() << "Нет склеек!";
        return;
    }
    qDebug() << "END << Получили номер склейки";
    //    int nomerSkleykiMDNF = 0; // хранит сколько склеек должно быть вообще
    //    nomerSkleykiMDNF = mdnf->getSkleykiMaxNumber(); // получаем номер последнего этапа
    //    if(nomerSkleyki != nomerSkleykiMDNF)
    //    {
    //        qDebug() << "Не совпадает количество этапов склейки:" << nomerSkleyki << nomerSkleykiMDNF;
    //        criticalError();
    //        return;
    //    }
    QStringList headers;
    if(!getTWTextList(tableWidgetOnesOnly, headers))
    {
        qDebug() << "В таблице, где функция равна 1 нет ни одной строки";
        criticalError("Вы не выбрали значения функции, при которых она принимает значние 1!");
        return;
    }
    qDebug() << "END << Получаем заголовки";
    QStringList vertical;
    if(!getTWTextList(tableWidgetsSkleyki[nomerSkleyki-1], vertical))
    {
        qDebug() << "Не удалось получить данные из таблцы " << nomerSkleyki-1;
        return;
    }
    if(vertical.size() == 0)
    {
        qDebug() << "END << Тублица пустая!";
        return;
    }
    qDebug() << "END << Получили заголовки";
    clearTW(tableWidgetKartaMinimizacii); // очищаем таблицу минимизации
    tableWidgetKartaMinimizacii->setRowCount(vertical.size()); // задаём количество строк равное количеству склеек
    tableWidgetKartaMinimizacii->setColumnCount(headers.size()); // задаем количество столбцов
    tableWidgetKartaMinimizacii->setHorizontalHeaderLabels(headers); // устаналиваем горизонтальные заголовки (значения равные 1)
    tableWidgetKartaMinimizacii->setVerticalHeaderLabels(vertical); // устаналиваем вертикальные заголовки (склейки)
    int rows = tableWidgetKartaMinimizacii->rowCount(); // получаем количество строк в таблице
    int cols = tableWidgetKartaMinimizacii->columnCount(); // получаем количество столбцов в таблице
    for (int i=0; i<rows; i++)  // проходим по всем строкам
    {
        for (int j=0; j<cols; j++) // проходим по всем столбцам
        {
            if(tableWidgetKartaMinimizacii->item(i, j) != nullptr) // если память уже выделена
            {
                delete tableWidgetKartaMinimizacii->item(i, j); // удаляем
            }
            QTableWidgetItem *ti = new QTableWidgetItem("");
            ti->setFlags(ti->flags()&0xfffffffd);
            ti->setTextAlignment(Qt::AlignCenter);
            tableWidgetKartaMinimizacii->setItem(i, j, ti); // выделяем память под новую ячейку
        }
    }
    qDebug() << "END << END";
    //    int indexes = tabWidget->count(); // получаем количество элементов TabWidget
    tabWidget->setCurrentIndex(4);
    setDefaultTableColor(tableWidgetKartaMinimizacii);
}

void MainWindow::setTableStepenTwo(int stepen)
{
    if(stepen < 1)
    {
        //        QMessageBox::critical(this, "Ошибка", "Система сичтления не может быть меньше 2");
        criticalError("Система сичтления не может быть меньше 2");
        return;
    }
    int rows = static_cast<int>(4 * stepen); // умножаем 4 (т.к. у нас 16-я ССЧ и она содержит по 4 двоичных разряда в числе) на количество разрядов числа и получаем количество строк
    //    int cols = static_cast<int>(log2(rows) + 1); // количство столбцов равно степени в которую надо возвезти 2, чтобы получить количество строк + 1 для функции
    double step = log2(rows); // получаем, в какую степень над овозвести числ о2, чтобы получить такую длину числа
    if(abs(step - static_cast<double>(static_cast<int>(step))) > 0.0) // если степень не целая
    {
        step = static_cast<double>(static_cast<int>(step)); // откидываем дробную часть
        step += 1.0; // прибавляем 1
    }
    int cols = static_cast<int>(step) + 1;// количство столбцов равно степени в которую надо возвезти 2, чтобы получить количество строк + 1 для функции
    tableWidgetTot->setRowCount(rows);
    tableWidgetTot->setColumnCount(cols);
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            setTWText(tableWidgetTot, i, j, "");
        }
    }
    QStringList headerList;
    for (int i=0; i<cols-1; i++) // добавляем переменные
    {
        char ch = 'a' + static_cast<char>(i);
        QString str;
        str.append(ch);
        headerList.append(str);
    }
    headerList.append("F"); // добавляем знак функции
    //    ui->tableWidget_tableOfTrue
    tableWidgetTot->setHorizontalHeaderLabels(headerList); // заполняем заголовок таблицы
    QStringList verticalList;
    for (int i=0; i<rows; i++)
    {
        verticalList.append(QString::number(i, 16).toUpper()); // добавляем числа в 16 ССЧ
        qDebug() << "Загооловк: " << verticalList[i];
        //        qDebug() << i << QString::number(i, 16);
    }
    tableWidgetTot->setVerticalHeaderLabels(verticalList); // заполняем вертикальные заголовки
//    for (int i=0; i<rows; i++)
//    {
//        checkBoxes[i]->setVisible(true); // делаем видимыми нужное количество чекбоксов
//    }
}

void MainWindow::setTableOfTrueNumbers()
{
    int rows = tableWidgetTot->rowCount(); // получаем количество строк в таблице
    int cols = tableWidgetTot->columnCount(); // получаем количество колонок в таблице
    if(!rows || !cols)
    {
        //        QMessageBox::critical(this, "Ошибка", "Задайте размер таблицы истиности!");
        criticalError("Задайте размер таблицы истиности!");
        return;
    }
    // заполняем числами от 0 до N в 2й ССЧ
    int maxcol = cols-2; // крайняя правая колонка, которую надо заполнить (она будет нулевым разрядом числа)
    for (int i=0; i<maxcol+1; i++)
    {
        int n = static_cast<int>(pow(2, i)); // возводим 2 в степень
        int k = 0; // сколько строк уже заполнено
        bool chislo = false; // число 0 или 1, которое записывается в таблицу
        int colnumber = maxcol-i; // вычисляем, в какую колонку будем записывать
        qDebug() << "i = " << i << "colnumber = " << colnumber;
        for (int i=0; i<rows; i++)
        {
            if(k < n) // если число цифр меньше степени, то записываем число
            {
                setTWText(tableWidgetTot, i, colnumber, QString::number(static_cast<int>(chislo))); // записывем значение числа (0 или 1)
                k++; // увелдичивам счётчик на 1
            }
            else // иначе изменяем число на противоположное (0 или 1) и заполняем дальше
            {
                chislo = !chislo; // инвертируем
                k = 0; // обнуляем счётчик
                setTWText(tableWidgetTot, i, colnumber, QString::number(static_cast<int>(chislo))); // записывем значение числа (0 или 1)
                k++; // увелдичивам счётчик на 1
            }
        }
    }

}

//void MainWindow::on_pushButton_proverka_karta_minimizacii_clicked()
//{
//    if(proverkaItogMdnf())
//    {
//        message();
//    }
//    else
//    {
//        warningError();
//    }
//}

void MainWindow::on_pushButton_proverka_karti_minimizacii_clicked()
{
    if(proverkaKartaMinimizacii())
    {
        tableWidget_kartaMinimizacii->setEditTriggers(QAbstractItemView::NoEditTriggers); // блокируем ввод данных в таблицу, если она правильная
        message();
        nextStep();
    }
    else
    {
        warningError();
    }
    //    message("Правильно!*\n\n* - Правильно при текущих входных параметрах.\nПри проверке не была учтена правильность склеек."); // если программа дошла до этого момента, значит все верно
    //    nextStep();
}

void MainWindow::on_pushButton_clear_skleiki_1_editing_clicked() // удалить последний добавленный элемент
{
    deletelastRow(ui->tableWidget_skleiki_1_editing); // удаляет последнюю обавленную склейку
}

void MainWindow::on_pushButton_clear_skleiki_2_editing_clicked()
{
    deletelastRow(ui->tableWidget_skleiki_2_editing); // удаляет последнюю обавленную склейку
}

void MainWindow::on_pushButton_clearSkleyki_2_clicked()
{
    deletelastRow(ui->tableWidget_skleiki_3_editing); // удаляет последнюю обавленную склейку
}

//void MainWindow::on_pushButton_proverka_skleyki_2_clicked()
//{
//    if(proverkaTable(tableWidgetsSkleykiEditing[1], mdnf->getSkleyki2(typeMin)))
//    {
//        message();
//        nextStep();
//        pusbButton_move_skleyki_to_coresTable();
//    }
//    else
//    {
//        warningError();
//    }

//}

void MainWindow::on_pushButton_proverka_skleyki_3_0_clicked()
{
    if(proverkaSkleyki3())
    {
        message();
        nextStep();
        //        pusbButton_move_skleyki_to_coresTable();
    }
    else
    {
        warningError();
    }
}

//void MainWindow::on_pushButton_loadDataFromFile_clicked()
//{
//    loadDataFromFile();
//}

void MainWindow::on_pushButton_nextStep_onesOnly_3_clicked()
{
    pusbButton_move_skleyki_to_coresTable();
    nextStep();
}


void MainWindow::on_pushButton_INV_clicked()
{
    editor->addInv();
}

void MainWindow::on_pushButton_A_clicked()
{
    addSymvol("A");
}

void MainWindow::on_pushButton_B_clicked()
{
    addSymvol("B");
}

void MainWindow::on_pushButton_C_clicked()
{
    addSymvol("C");
}

void MainWindow::on_pushButton_D_clicked()
{
    addSymvol("D");
}

void MainWindow::on_pushButton_notA_clicked()
{
    addSymvol("A", true);
}

void MainWindow::on_pushButton_notB_clicked()
{
    addSymvol("B", true);
}

void MainWindow::on_pushButton_notC_clicked()
{
    addSymvol("C", true);
}

void MainWindow::on_pushButton_notD_clicked()
{
    addSymvol("D", true);
}

void MainWindow::on_pushButton_AND_clicked()
{
    addSymvol("*");
}

void MainWindow::on_pushButton__OR_clicked()
{
    addSymvol("+");
}

void MainWindow::on_pushButton_SKOBKA_BEFORE_clicked()
{
    addSymvol("(");
}

void MainWindow::on_pushButton_SKOBKA_AFTER_clicked()
{
    addSymvol(")");
}

void MainWindow::on_pushButton_DEL_clicked()
{
    editor->deleteLastSymvol();
}

void MainWindow::on_pushButton_CLEAR_clicked()
{
    if (QMessageBox::question(this,"Внимание","Очистить поле редактора функции?", QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::No)
    {
        return;
    }
    editor->clearTable();
}

//void MainWindow::on_tableWidget_formulaEditor_itemActivated(QTableWidgetItem *item)
//{
//    Q_UNUSED(item);
//}

//void MainWindow::on_tableWidget_formulaEditor_itemChanged(QTableWidgetItem *item)
//{
//    Q_UNUSED(item);
//}

/**
@brief Выравнивает текст в таблице по центру.
@param tbw Указатель на таблицу, в которой нужно выравнивать текст.
Функция выравнивает содержимое ячеек таблицы tbw по центру.
Если таблица tbw не существует или не содержит строк или столбцов, функция завершается.
В цикле проходим по всем строкам и столбцам таблицы и, если ячейка существует, устанавливаем выравнивание текста по центру.
*/
void MainWindow::center_text_in_table(QTableWidget *tbw)
{
    if(tbw == nullptr)
    {
        return;
    }
    int rows = tbw->rowCount(); // получили количество строк
    int cols = tbw->columnCount(); // получаем количество столбцов
    qDebug() << "Выравниваем. Количество строк: "  << rows << "Количество столбцов: "  << cols;
    if(rows == 0 || cols == 0)
    {
        return;
    }
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            if(tbw->item(i, j) != nullptr)
            {
                tbw->item(i, j)->setTextAlignment(Qt::AlignCenter); // выравниаем все элементы по центру
            }
        }
    }
}

/**
@brief Устанавливает переменные в заголовке таблицы.
@param tbw Указатель на таблицу, в которой нужно установить переменные в заголовок.
Функция устанавливает переменные в заголовке таблицы tbw.
Если таблица tbw не существует или не содержит столбцов, функция завершается.
Создается QStringList headerList для хранения заголовков.
В цикле добавляются переменные в виде букв, начиная с 'a' и увеличивая на 1 с помощью оператора ++.
Каждая переменная преобразуется в QString и добавляется в headerList.
В результате получается список букв, который устанавливается в качестве горизонтальных заголовков таблицы.
*/
void MainWindow::setVariablesToHeader(QTableWidget *tbw)
{
    if(tbw == nullptr)
    {
        return;
    }
    int cols = tbw->columnCount(); // получаем количество столбцов
    if(cols == 0) // если нет столбцов
    {
        return;
    }
    QStringList headerList; // создаем список, который будет хранить хаголовки
    for (int i=0; i<cols; i++) // добавляем переменные
    {
        char ch = 'a' + static_cast<char>(i); // формируем переменных путём прибавления 1 к char
        QString str;
        str.append(ch);
        headerList.append(str);
    }
    tbw->setHorizontalHeaderLabels(headerList); // устаналиваем заголовки
}

void MainWindow::setSklykiResultTableColor(QTableWidget *tableWidget)
{
    int rows = tableWidget->rowCount(); // получаем количество строк
    int cols = tableWidget->columnCount(); // получаем количество столбцов

    for (int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if(item != nullptr)
            {
                item->setBackground(Qt::white); // устанавливаем цвет ячейки
                item->setForeground(QColor(100, 100, 100)); // устанавливаем цвет текста
            }
        }
    }
}

void MainWindow::setDefaultTableColor(QTableWidget *tableWidget)
{
    int rows = tableWidget->rowCount(); // получаем количество строк
    int cols = tableWidget->columnCount(); // получаем количество столбцов

    for (int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if(item != nullptr)
            {
                item->setBackground(Qt::white); // устанавливаем цвет ячейки
                item->setForeground(Qt::black); // устанавливаем цвет текста
            }

        }
    }
}

void MainWindow::setCheckBoxesTotFunctionValue()
{
    const int rows = tableWidgetTot->rowCount();
    const int cols = tableWidgetTot->columnCount();
    const int valueCol = cols-2;    // столбец со значением в 2 ССЧ
    const int checkBoxCol = cols-1; // столбец с checkBox

    if(checkBoxes != nullptr)
    {
        for (int i=0; i<rows; i++)
        {
            if(checkBoxes[i] != nullptr)
            {
                QTableWidgetItem *valueItem = tableWidgetTot->item(i, valueCol);        // элемент со значением функции
                QTableWidgetItem *checkBoxItem = tableWidgetTot->item(i, checkBoxCol);  // элемент с checkBox

                if(valueItem != nullptr && checkBoxItem != nullptr)
                {
                    checkBoxes[i]->setText(valueItem->text());      // заносим значение функции в checkBox
                    checkBoxItem->setText("");      // очищаем текст в ячейке checkBox
                }
            }
        }
    }
}

void MainWindow::clearSelectionAdDisableClickTableWidget(QTableWidget *tableWidget)
{
    int rows = tableWidget->rowCount();
    int cols = tableWidget->columnCount();

    // убирам выделение
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            QTableWidgetItem *item = tableWidget->item(i, j);
            if(item != nullptr) // если ячейка существует
            {
//                if(item->isSelected()) // если выделен
//                {
                    item->setFlags(item->flags()&0xfffffffd);
                    tableWidget->clearSelection();
                    tableWidget->setCurrentCell(-1, -1);
//                }
            }
        }
    }
}

/**
@brief Проверяет соответствие значения ячейки с заданными строкой и столбцом.
@param i Индекс строки.
@param j Индекс столбца.
@param horizontalList Список строк заголовка таблицы.
@param verticalList Список столбцов заголовка таблицы.
@return true, если значение ячейки соответствует заданным строке и столбцу, иначе false.
Функция проверяет, соответствует ли значение ячейки в таблице с индексами i и j заданным строке и столбцу
из списков horizontalList и verticalList соответственно.
Если количество символов в строке и столбце не совпадает, функция возвращает false.
Затем сравниваются символы посимвольно и вычисляется количество совпадений.
Если все символы совпадают и значение ячейки таблицы равно "+", функция возвращает true.
Если символы не совпадают, но значение ячейки равно "+", функция возвращает false.
Если символы совпадают, но значение ячейки не равно "+", функция возвращает false.
В противном случае функция возвращает true.
*/
bool MainWindow::checkKartaPokritiyaItem(int i, int j, QStringList &horizontalList, QStringList &verticalList)
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
    qDebug() << "Значение подходит";
    return true;
}


//void MainWindow::pushButtonFunctionClicked()
//{

//}


void MainWindow::pushButtonFunc2Clicked()
{
    QString chislo = lineEditFunc_2->text(); // получаем число из LineEdit
    if(chislo.isEmpty()) // если введена пустая строка
    {
        qDebug() << "Нет числа в функуии 2";
        warningError("Введите число!"); // выдаем ошибка
        return;
    }
    if(!chislo.contains("0") && !chislo.contains("1")) // если не содержит 0 и не содержит 1
    {
        qDebug() << "Число должно содержать нули и единицы";
        warningError("Число должно быть записано в 2й системе счисления!");
        return;
    }
    chislo.remove(" ");
    int count = chislo.count();  // получаем количество символов в строке
    int rows = tableWidgetTot->rowCount(); // получаем количество строк в таблице истинности
    if(count != rows) // если количество введенных символов не совпадает с количеством строк в таблице
    {
        qDebug() << "Количество символов в число не совпадает с количеством строк";
        warningError("Проверьте количество введеннх символов!");
        return;
    }
    int cols = tableWidgetTot->columnCount(); // получаем количетсво солбцов в таблице истинности
    QStringList list = chislo.split(""); // разбиваем число на символы
    for (int i=0; i<rows; i++)
    {
        setTWText(tableWidgetTot, i, cols-2, chislo.at(i));   // выводим значения в таблицу истинности
    }
    message("Число, полученное в 2 системе счисления добавлено в таблицу истинности. Для проверки правильности воспользуйтесь кнопкой проверка табилцы истинности.");
    //    nextStep(); // переходим к следующему шагу
    function_2 = chislo; // сохраняем 2ю запись функции
}

void MainWindow::updateCheckBoxTotState(int arg1)
{
    Q_UNUSED(arg1);
    on_pushButton_tot_add_clicked(); // вызываем нажатие кнопки добавить
}

/**

@brief Определяет тип функции.
Данная функция выполняет анализ и определение типа функции на основе переданных параметров.
Функция принимает строку func_2 - функция в виде последовательности символов '0' и '1',
и список listFunc - список значений для определения типа функции.
@param func_2 Функция в виде строки, состоящей из символов '0' и '1'.
@param listFunc Список значений для определения типа функции.
@return Возвращает целочисленный результат, обозначающий тип функции:
- 0, если функция является МКНФ (минимальной конъюнктивной нормальной формой);
- 1, если функция является МДНФ (минимальной дизъюнктивной нормальной формой);
- -1, если не удалось определить тип функции.
*/
int MainWindow::getType(QString func_2, QStringList listFunc)
{
    if(func_2.count() < listFunc.size())
    {
        qDebug() << "Размер функции меньше размера списка, для определния типа!";
        return -1;
    }
    int funcSize = func_2.count(); // получаем количество элементов в функции
    int listSize = listFunc.size(); // получаем количество элементов в списке для получения типа
    int zeroCount = 0; // количество выбранных значений, при которых функция принимает значение 0
    int oneCount = 0; // количество выбранных значений, при которых функция принимает значение 1
    for (int i=0; i<listSize; i++)
    {
        bool flag = false; // флаг перевода
        int chislo = listFunc.at(i).toInt(&flag, 2); // переводим число из 2й в 10 ссч
        if(!flag) // если число не переводится
        {
            qDebug() << "Число " << listFunc.at(i) << "не удалось перевести в 10ю ссч!";
            return -1;
        }
        if(chislo >= funcSize) // если номер больше или равен количеству элементов в функции, значит что-то не так
        {
            qDebug() << "Номер " << chislo << "значения" << listFunc.at(i) << " больше, чем размер" << funcSize << " функции" << func_2;
            return -1;
        }
        if(func_2.at(chislo) == "0") // если функция при этом значении даёт 0
        {
            zeroCount++; // увеличиваем счётчик значений, при которых F=0
        }
        if(func_2.at(chislo) == "1") // если функция при этом значении даёт 1
        {
            oneCount++; // увеличиваем счётчик значений, при которых F=1
        }
    }
    if(((zeroCount != 0) && (oneCount != 0)) || ((zeroCount == 0) && (oneCount == 0))) // если присутствуют и значения, при которых 0, и те, при которых 1, т.е. нельзя определить тип - МКНФ или МДНФ
    {
        qDebug() << "Не удалось определить тип! Значений для F=0 - " << zeroCount << ", значений для F=1 - " << oneCount;
        return -1;
    }
    int funcZeroCount = 0; // переменная для подсчёта количества нулей в исходной функции
    int funcOneCount = 0; // переменная для подсчёта количества единиц в исходной функции
    for (int i=0; i<funcSize; i++)
    {
        if(func_2.at(i) == "0") // если значение функции равно 0
        {
            funcZeroCount++; // увеличиваем счётчик нулей
        }
        if(func_2.at(i) == "1") // если значение функции равно 1
        {
            funcOneCount++; // увеличиваем счётчик единиц
        }
    }
    if((funcZeroCount == zeroCount) && (zeroCount > 0)) // если количество нулей совпадает с данными в функции
    {
        return 0;
    }
    else if((funcOneCount == oneCount) && (oneCount > 0)) // если количество единиц совпадает с данными в функции
    {
        return 1;
    }
    else // если ничего не совпадает
    {
        return -1;
    }
}

/**
@brief Получает тип оптимизации по входной функции.
Функция анализирует строку func_2 и подсчитывает количество единиц и нулей.
Если в строке содержатся символы, отличные от '0' и '1', возвращает -1.
Иначе, возвращает:
0, если количество нулей больше количества единиц;
1, если количество единиц больше количества нулей;
2, если количество нулей и единиц равны.
@param func_2 Входная функция в виде строки.
@return Тип оптимизации:
- (-1) при неверной входной функции;
CopyCopy
- 0, если количество нулей больше количества единиц;
CopyCopy
- 1, если количество единиц больше количества нулей;
CopyCopy
- 2, если количество нулей и единиц равны.
CopyCopy
*/
int MainWindow::getOptimizeType(QString func_2)
{
    int count = func_2.count(); // получаем количество символов
    if(count == 0) // если нет символов
    {
        return -1;
    }
    int zeroCount = 0; // счётчик нулей
    int oneCount = 0; // счётчик единиц
    for (int i=0; i<count; i++)
    {
        if((func_2.at(i) != "0") && (func_2.at(i) != "1"))    // если символ не 0 и не 1
        {
            return -1;
        }
        if(func_2.at(i) == "0")
        {
            zeroCount++;
        }
        if(func_2.at(i) == "1")
        {
            oneCount++;
        }
    }
    qDebug() << "Исходная функция:" << func_2 << "Количество нулей: " << zeroCount << " Количество единиц: " << oneCount;
    if(zeroCount < oneCount) // если нулей больше, чем единиц
    {
        return 0;
    }
    if(zeroCount > oneCount) // если нулей меньше, чем единиц
    {
        return 1;
    }
    if(zeroCount == oneCount) // если количество равно
    {
        return 2;
    }
    return -1;
}

void MainWindow::pushButton_delete_last_onesClicked()
{
    deletelastRow(tableWidgetOnesOnlyEditing);
}

void MainWindow::pushButtonClearOneOnlyClicked()
{
    qDebug() << "call pushButtonClearOneOnlyClicked()";
    tableWidgetOnesOnlyEditing->clear();
    tableWidgetOnesOnlyEditing->setRowCount(0);
    tableWidgetOnesOnlyEditing->setColumnCount(0);

}

void MainWindow::on_pushButton_tot_move_to_skeyki_1_clicked()
{
    qDebug() << "Нажато!";
    moveSkleyka(tableWidgetOnesOnly, checkBoxes_ones, tableWidgetsSkleykiEditing[0]); // переносим выделенные элементы без склейки
}

void MainWindow::on_pushButton_tot_move_to_skeyki_2_clicked()
{
    moveSkleyka(tableWidgetsSkleyki[0], checkBoxes_skleyki_1, tableWidgetsSkleykiEditing[1]); // переносим выделенные элементы без склейки
}

void MainWindow::on_pushButton_tot_move_to_skeyki_3_clicked()
{
    moveSkleyka(tableWidgetsSkleyki[1], checkBoxes_skleyki_2, tableWidgetsSkleykiEditing[2]); // переносим выделенные элементы без склейки
}

void MainWindow::on_pushButton_setRedColor_clicked()
{
    setKartaColor(*redColor); // задём красный цвет выделенным значениям
}

void MainWindow::on_pushButton_setGreenColor_clicked()
{
    setKartaColor(*yellowColor); // задём желтый цвет выделенным значениям
}

void MainWindow::on_pushButton_setWhiteColor_clicked()
{
    setKartaColor(Qt::white); // задём белый цвет выделенным значениям
}

/**
@brief Добавляет символ в редактор формул.
Функция добавляет указанный символ в редактор формул. Перед добавлением выполняется
проверка наличия активного объекта редактора формул. Если объект не создан, функция
просто возвращает управление.
Если включена функция автоматического ввода, функция проверяет, является ли символ буквой или
специальным символом. В зависимости от предыдущего символа и типа оптимизации, функция добавляет
соответствующий операнд.
При редактировании выбранного элемента, функция проверяет, выбран ли только один символ,
после которого необходимо добавить операнд.
@param symvol Символ, который требуется добавить в редактор формул.
@param inversiya Флаг инверсии символа (true - инвертированный символ, false - обычный символ).
*/
void MainWindow::addSymvol(QString symvol, bool inversiya)
{
    if(editor == nullptr) // если не создан объект редакора формул
    {
        return;
    }
    symvol = symvol.toUpper();
    qDebug() << symvol;
    if(autoInput) // если включена функция автоматического ввода
    {
        if(((symvol >= "A") && (symvol <= "D"))/* || (symvol == ")")*/) // если символ - буква или символ
        {
            QString formula = editor->getFormulaText(); // получаем формулу
            qDebug() << "formula = " << formula;
            if(formula != "ERROR")
            {
                qDebug() << "count =" << formula.count();
                formula = formula.toUpper();
                QString lastSymvol = formula.at(formula.count() -1); // получаем последний символ
                if(editor->isEditChoseItem()) // если происходит редактирование выбранного элемента
                {
                    int selectedItem = -1;
                    int selectedCount = 0;
                    editor->getSelectedItemNumber(tableWidget_formulaEditor, selectedItem, &selectedCount);
                    if(selectedCount > 1)
                    {
                        warningError("Выберите только один символ, после которого необходимо добавление олперанда");
                        return;
                    }
                    qDebug() << "номер выбранного столбца: " << selectedItem;
                    qDebug() << "Всего символов в строке: " << formula.count();
                    lastSymvol = tableWidget_formulaEditor->item(1, selectedItem)->text();
                }
                qDebug() << "last symvol = " << lastSymvol;
                if((lastSymvol >= "A") && (lastSymvol <= "D")/* && (symvol >= "A") && (symvol <= "D")*/) // если предыдущий символ - буква
                {
                    if(symvol > lastSymvol)
                    {
                        if(typeMin == 0)
                        {
                            editor->addSymvol("+");
                        }
                        else if(typeMin == 1)
                        {
                            editor->addSymvol("*");
                        }
                    }
                    else
                    {
                        editor->addSymvol(")");
                        if(typeMin == 0)
                        {
                            editor->addSymvol("*");
                        }
                        else if(typeMin == 1)
                        {
                            editor->addSymvol("+");
                        }
                        editor->addSymvol("(");
                    }
                }
                else if (lastSymvol == ")") // если закрывающаяся скобка
                {
                    if(typeMin == 0)
                    {
                        editor->addSymvol("*");
                    }
                    else if(typeMin == 1)
                    {
                        editor->addSymvol("+");
                    }
                    editor->addSymvol("(");
                }
            }
            else // если у нас первый символ, то ставим открывающуюся скобку
            {
                editor->addSymvol("(");
            }
        }
    }
    qDebug() << "formula = " << editor->getFormulaText();
    editor->addSymvol(symvol, inversiya);
    if(symvol == "D") // если символ D, то сразу закрываем скобку
    {
        editor->addSymvol(")");
    }
}

void MainWindow::setAutoInput(bool value)
{
    autoInput = value;
}

void MainWindow::on_checkBox_autoInputFormula_stateChanged(int arg1)
{
    setAutoInput(static_cast<bool>(arg1)); // устанавливаем значение автоматического ввода
}

void MainWindow::on_checkBox_editChoseItemFormula_stateChanged(int arg1)
{
    if(editor != nullptr)
    {
        editor->setEditChoseItem(static_cast<bool>(arg1)); // устанавливаем значение редактирования выбранного элемента
    }
}

void MainWindow::on_lineEdit_func_2_textChanged(const QString &arg1)
{
    qDebug() << "строка" << arg1;
    //    if(arg1.isEmpty())
    //    {
    //        return;
    //    }
    //    if(arg1.at(arg1.size()-1) == " ")
    //    {
    //        return;
    //    }
    QString inputString = arg1;
    inputString = inputString.remove(" ");
    splitToTetrads = ui->checkBox_spiltToTetrads->isChecked();
    if(!splitToTetrads)
    {
//        ui->lineEdit_func_2->blockSignals(true);
//        ui->lineEdit_func_2->setText(inputString);
//        ui->lineEdit_func_2->blockSignals(false);
    }
    else
    {
        QString outputString;
        //    QString tempString;
        for (int i=0; i<inputString.count(); i++)
        {
            qDebug() << "i = " << i;
            outputString.append(inputString.at(i));
            if((i+1) % 4 == 0 && i != inputString.count()-1) // делится без остатка на 4
            {
                qDebug() << ((i+1) % 4 == 0) << "i = " << i;
                outputString.append(" "); // Добавляем пробел
            }
        }
        //    int outPutSize = outputString.size();
        //    if(outPutSize > 0)
        //    {
        //        if(outputString.at(outPutSize-1) == " ")
        //        {
        //            outputString.remove(outPutSize-1);
        //        }
        //    }
        ui->lineEdit_func_2->blockSignals(true);
        ui->lineEdit_func_2->setText(outputString);
        ui->lineEdit_func_2->blockSignals(false);
    }
    int cols = tableWidgetTot->columnCount(); // получаем количетсво солбцов в таблице истинности
    int rows = tableWidgetTot->rowCount();
    QStringList list = inputString.split(""); // разбиваем число на символы
    for (int i=0; i<rows; i++)
    {
        QString itemText = "";
        if(i<inputString.count())
        {
            itemText = inputString.at(i);
        }
        setTWText(tableWidgetTot, i, cols-2, itemText);   // выводим значения в таблицу истинности
    }
    //    message("Число, полученное в 2 системе счисления добавлено в таблицу истинности. Для проверки правильности воспользуйтесь кнопкой проверка табилцы истинности.");
    //    nextStep(); // переходим к следующему шагу
    function_2 = inputString; // сохраняем 2ю запись функции
    //    }

    setSklykiResultTableColor(tableWidgetTot);  // делаем таблицу более тусклой

}

void MainWindow::on_checkBox_spiltToTetrads_stateChanged(int arg1)
{
    splitToTetrads = arg1;
    on_lineEdit_func_2_textChanged(ui->lineEdit_func_2->text());
}

void MainWindow::on_pushButton_proverka_result_function_clicked()
{
//    if(proverkaItogMdnf())
    int result = proverkaItogMdnfByKartaPokritiya();
    if(result != 0)
    {
        if(result == -1)
        {
            warningError("Ошибка! Решение не оптимальное, можно уменьшить кол-во переменных.");
        }
        else
        {
            // проверка на подмену функции в файле
            QString func16; // число в 16й системе, которое переведено в 2ю систему (на 2 этапе)
            to16ssch(function_2, func16);    // переводим число из 2 в 16ю систему

            bool validFunction = true;  // флаг валидности функции
            if(func16.toUpper() != function_16.toUpper())   // если функция не совпадает
            {
    //            qDebug() << "функции не совпадают: " << func16.toUpper() << function_16.toUpper();
                validFunction = false;  // ставим флаг некорретности
            }

            //        message();
            if(formResult == nullptr)
            {
                formResult = new FormResultCorrect;
            }
            formResult->setFunction(function_16);
            formResult->setStudent_name(studentName);
            formResult->setGroup(StudentGroup);
            formResult->setType(typeMin == 0 ? "МКНФ" : "МДНФ");
            formResult->setValidFunction(validFunction);
            formResult->show();
            formResult->applyData();
        }
    }
    else
    {
        warningError();
    }
}

void MainWindow::on_pushButton_proverka_skleiki_1_editing_clicked() // кнопка проверки склеек 1
{
    if(proverkaSkleyki1()) // сравниваем таблицу со значениями склейки
    {
        message();
        nextStep();
    }
    else
    {
        warningError();
    }
}

void MainWindow::on_pushButton_enterFunction_clicked()
{
    QString text = lineEditFunction->text(); // берем текст функции
    setFunction(text); // задаём функцию
}

void MainWindow::on_pushButton_proverka_oneOnly_clicked()
{
    QStringList listFunc;
    bool ok = getTWTextList(tableWidgetOnesOnlyEditing, listFunc); // получаем списолк значений из таблицы
    if(!ok)
    {
        warningError("Таблица пуста!");
        return;
    }
    int type = getType(function_2, listFunc); // пытаемся определить тип
    if(type == -1) // если не удалось определить тип
    {
        warningError("Ошибка! Не удалось определить тип минимизации!\nДобавьте в таблицу все значения при которых функция принимает 0 или 1!");
        return;
    }
#ifdef OPTYMIZE_TYPE_ONLY
    int optimizeType = getOptimizeType(function_2); // получаем ,какой тип минимизации предпочтительнее
    qDebug() << "Тип: " << type << " Оптимальный тип: " << optimizeType;
    if((optimizeType == -1) || (optimizeType == 3) || (optimizeType == 4)) // проверяем, если вдруг в программе получится ошибка
    {
        if(optimizeType == -1)
        {
            criticalError("Произошла непредвиденная ошибка!");
            return;
        }
        if(optimizeType == 3)
        {
            criticalError("Произошла непредвиденная ошибка!\nПопробуйте использовать МКНФ для минимизации.");
            return;
        }
        if(optimizeType == 4)
        {
            criticalError("Произошла непредвиденная ошибка!\nПопробуйте использовать МДНФ для минимизации.");
            return;
        }
    }
    if(optimizeType != 2) // если не 2й тип, т.е. тот, когда можно использовать, и МКНФ, и МДНФ, т.к. одинаковое количество 0 и 1
    {
        if(type != optimizeType)
        {
            warningError("Ошибка! Ещё раз посчитайте количество 0 и 1 в функции!");
            return;
        }
    }
#endif
    if(type == 0)
    {
//        message("Определён тип: МКНФ");
        qDebug() << "Определён тип: МКНФ";
    }
    else
    {
//        message("Определён тип: МДНФ");
        qDebug() << "Определён тип: МДНФ";
    }
    typeMin = type; // сохраняем тип
//    QStringList mmkList = mdnf->getListOnes(typeMin);

    QStringList tableOfTrue;
    getTWTextList(tableWidgetTot, tableOfTrue); // получаем значения таблицы истинности

    QStringList mmkList;
    for(QString value : qAsConst(tableOfTrue))    // перебирвем все значения таблицы истинности
    {
        if(value.endsWith(QString::number(typeMin)))    // если значение оканчивается на 0 или 1, в зависимости от типа
        {
            int lastIndex = value.size()-1;
            QString v4 = value.remove(lastIndex, 1);
            mmkList.append(v4);  // добавляем значение в список необходимых, удаляя последнее значение (значение функции)
        }
    }

    for (int i=0; i<mmkList.size(); i++)
    {
        qDebug() << "MMK List [" << i << "] = " << mmkList.at(i);
    }

    for (int i=0; i<listFunc.size(); i++)
    {
        qDebug() << "Func List [" << i << "] = " << listFunc.at(i);
    }
//    if(proverkaOnesOnly())
    if(proverkaTable(tableWidgetOnesOnlyEditing, mmkList))
    {
        editor->setAutoInputType(typeMin); // устанавливаем тип автоматического ввода
        message();
        step++; // увеличиваем шаг на 1
        setStep(step);// переходим к следующему шагу
//        skleyki[0] = mdnf->getSkleyki1(typeMin);
//        skleyki[1] = mdnf->getSkleyki2(typeMin);
//        skleyki[2] = mdnf->getSkleyki3(typeMin);
//        qDebug() << "Склека 3: " << mdnf->getSkleyki3(typeMin);
    }
    else
    {
        warningError();
    }
}


void MainWindow::on_pushButton_checkTableOfTrue_clicked()
{
    //    proverkaTable(tableWidgetTot, mdnf->getSschTableList());
    if(proverkaTableOfTrue()) // сравниваем таблицу со значениями МДНФ
    {
        message(); // если правильно
        step++; // увеличиваем шаг на 1
        setStep(step);// переходим к следующему шагу

        setCheckBoxesTotFunctionValue();    // задаем значения для checkBox как у функции
    }
    else
    {
        warningError(); // если ошибка
    }

    // выравниваем ширину и высоту ячеек по контенту
//    tableWidgetTot->resizeColumnsToContents();
//    tableWidgetTot->resizeRowsToContents();
}


void MainWindow::on_pushButton_nextStep_onesOnly_clicked()
{
    goToNextStep(tableWidgetsSkleykiEditing[0], tableWidgetsSkleyki[0], 2);
    //    sortSkleiki(tableWidgetsSkleyki[0]);
    int rows = tableWidgetsSkleyki[0]->rowCount(); // получаем колитечтво строк
    if(rows <= 0)
        return;
    int cols = tableWidgetsSkleyki[0]->columnCount(); // получаем количество столбцов
    if(cols <= 0)
        return;
    // создаем массив
    QString **tableText = nullptr; // массив для хранения элементов таблицы
    tableText = new QString *[rows]; // выделяем память под строки
    for (int i=0; i<rows; i++)
    {
        tableText[i] = new QString [cols]; // выделяем память под столбцы
    }
    // получаем данные из таблицы
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            tableText[i][j] = tableWidgetsSkleyki[0]->item(i, j)->text(); // сохраняем данные в массив
        }
    }
    // сортируем склейки
    QStringList sortSkleikyList; // создаем список для отсортированных склеек
    //    int lastRow = 0; // номер строки, в которую последний раз были занесены данные (склейка)
    for (int p=0; p<cols; p++) // p = номер позиции Х в строке
    {
        qDebug() << "Ищем Х в позиции " << p;
        for (int i=0; i<rows; i++)
        {
            for (int j=0; j<cols; j++)
            {
                if((tableText[i][j] == "X") && (j == p))  // если позиция Х совпадает с текущим номером
                {
                    qDebug() << "В строке" << i << "в столбце" << j << "X находится на позиции" << p;
                    QString skleyka;
                    for (int h=0; h<cols; h++) // проходим по всем элементам строки
                    {
                        skleyka.append(tableText[i][h]);
                        //                        tableWidgetsSkleyki[0]->setItem(lastRow, h, new QTableWidgetItem((tableText[i][h]))); // выводим в таблицу
                        //                        lastRow++; // увеличиваем на 1 номер последней строки
                    }
                    qDebug() << "Создана склейка " << skleyka;
                    sortSkleikyList.append(skleyka); // обавляем склейку в список
                }
            }
        }
    }

    for (int i=0; i<rows; i++)
    {
        delete [] tableText[i];
    }
    delete [] tableText;
    tableText = nullptr;

    // ищём повторящиеся элементы (из-за несовсем корректной работы группировщика)
    for (int i=0; i<sortSkleikyList.size(); i++)
    {
        for (int j=0; j<i; j++)
        {
            if(sortSkleikyList[j] == sortSkleikyList[i]) // если существует
            {
                sortSkleikyList.removeAt(i); // удаляем
            }
        }
    }
    QStringList ishodniyList;
    if(!getTWTextList(tableWidgetsSkleyki[0], ishodniyList))
    {
        qDebug() << "Не получилось получить данные из " << tableWidgetsSkleyki[0];
        return;
    }
    for (int i=0; i<ishodniyList.size(); i++)
    {
        if(!(ishodniyList[i].contains("X"))) // если элемент не содержит Х, то добавляем его в конец
        {
            sortSkleikyList.append(ishodniyList[i]);
        }
    }
    int size = sortSkleikyList.size(); // получаем количество склеек в списке
    for (int i=0; i<size; i++)
    {
        QString skleyka = sortSkleikyList[i]; // получаем склейку
        for (int j=0; j<skleyka.count(); j++)
        {
            tableWidgetsSkleyki[0]->setItem(i, j, new QTableWidgetItem(skleyka.at(j))); // выподим каждый элемент
        }
    }
    addCheckBoxesInLastColumn(tableWidgetsSkleyki[0], checkBoxes_skleyki_1);     // вставляем checkBox в последную колонку
    nextStep();
}


void MainWindow::on_pushButton_nextStep_tot_clicked()
{
    goToNextStep(tableWidgetOnesOnlyEditing, tableWidgetOnesOnly, 1); // переходим к следующему действию
    nextStep();
    sortOnesCount(tableWidgetOnesOnly); // сортируем значения по количеству единиц
    addCheckBoxesInLastColumn(tableWidgetOnesOnly, checkBoxes_ones);     // вставляем checkBox в последную колонку
}


void MainWindow::on_pushButton_help_1_clicked()
{
    QMessageBox::information(this,"Таблица истинности","На данном этапе необходимо перевести формулу из одной системы "
                                                       "счисления в другую. Во втором шаге, для своего удобства, вы можете "
                                                       "разделись запись в двоичной СС на тетрады. "
                                                       "Следующим шагом нужно выбрать с помощью checkbox интересующие вас "
                                                       "строки таблицы, которые автоматически перенесуться во вторую.\n"
                                                       "Не забудьте сделать проверку!");
}


void MainWindow::on_pushButton_help_2_clicked()
{
    QMessageBox::information(this,"Выполнение склеек","На этом этапе Вам необходимо провести склейки элементов."
                                                       "\nДля выполнения склейки установите 2 галочки напротив тех элементов, "
                                                       "которые необходимо \"склеить\" и нажмите кнопку Добавить.\n"
                                                       "Если склейка удалась, оба элемента будут выделены цветом. "
                                                       "Для завершения этапа необходимо получить максимальное количество склеек, "
                                                       "задействовав все исходные значения.\nЕсли какой-либо элемент "
                                                       "невозможно \"склеить\" с другими, то установите одну галочку "
                                                       "напротив этого элемента и нажмите кнопку Добавить.\n"
                                                       "Если склейки произвести невозможно, "
                                                       "оставьте таблицу со склейками пустой и нажмите Проверить.");
}


void MainWindow::on_pushButton_help_3_clicked()
{
    on_pushButton_help_2_clicked();
}


void MainWindow::on_pushButton_help_4_clicked()
{
    on_pushButton_help_2_clicked();
}


void MainWindow::on_pushButton_help_5_clicked()
{
    QMessageBox::information(this,"Карта покрытия","На данном этапе вам необходимо составить таблицу истинности "
                                                   "на основе олучившихся склеек. \n"
                                                   "'Выделить красным' - выделяет выбранную ячейку таблицы красным, означает ядро. \n"
                                                   "'Выделить былым' - возвращает ячейке пустое значение, выделяет  выбранную ячейку таблицы белым. \n"
                                                   "'Выбелить зедёным' - выделяет выбранную ячейку таблицы зелёным, обозначает пересечение.");
}


void MainWindow::on_tableWidget_kartaMinimizacii_cellDoubleClicked(int row, int column)
{
    if (step == 11)
    {
        QTableWidgetItem *item = ui->tableWidget_kartaMinimizacii->item(row, column);

        if(item != nullptr)
        {
#ifdef ENABLE_AUTO_CHECK_KORRECT_KATRA_POKRITIYA
            if(item->text() != "+")
            {
#endif
                QString nextItemText;
                if (item->text().isEmpty())
                {
                    nextItemText = "+";
                }
                else
                {
                    nextItemText = "";
                }

                item->setText(nextItemText);

#ifdef ENABLE_AUTO_CHECK_KORRECT_KATRA_POKRITIYA
                // проверяем, должен ли в этой ячейке быть + или нет
                int rows = tableWidgetKartaMinimizacii->rowCount(); // получаем количество строк
                int cols = tableWidgetKartaMinimizacii->columnCount(); // получаем количество строк

                QStringList horizontalList; // создаем список заголовков столбцов
                for (int i=0; i<cols; i++)
                {
                    horizontalList.append(tableWidgetKartaMinimizacii->horizontalHeaderItem(i)->text());
                }
                QStringList verticalList; // создаем список заголовков строк
                for (int i=0; i<rows; i++)
                {
                    verticalList.append(tableWidgetKartaMinimizacii->verticalHeaderItem(i)->text());
                }

                bool result = checkKartaPokritiyaItem(row, column, horizontalList, verticalList);
                if(!result)  // если расположение + неправильное
                {
                    item->setText("");
                    ui->tableWidget_kartaMinimizacii->setCurrentCell(-1, -1);
//                    warningError("Данное значение не покрывавется выбранной склейкой!");
                }
            }
#endif

            item->setFlags(item->flags()&0xfffffffd);
            ui->tableWidget_kartaMinimizacii->clearSelection();
            ui->tableWidget_kartaMinimizacii->setCurrentCell(-1, -1);
        }

//        ui->tableWidget_kartaMinimizacii->clearSelection();
        ui->tableWidget_kartaMinimizacii->setCurrentCell(-1, -1);
    }
    else
    {
        QTableWidgetItem *item = ui->tableWidget_kartaMinimizacii->item(row, column);
        item->setFlags(item->flags()&0xfffffffd);
        ui->tableWidget_kartaMinimizacii->clearSelection();
        ui->tableWidget_kartaMinimizacii->setCurrentCell(-1, -1);
    }

    center_text_in_table(ui->tableWidget_kartaMinimizacii);     // центрируем текст
}


void MainWindow::on_pushButton_tot_add_clicked()
{
    qDebug() << "call pushButtonTotAddClicked()";
    int rows = tableWidgetTot->rowCount();
    int cols = tableWidgetTot->columnCount() - 2;   // последние 2 колонки - это значение функции

    bool *add = new bool [rows]; // проверяем, добавляет ли пользователь строку или нет для склейки
    int countChecked = 0; // переменная для подсчёта, сколько элементов выбрано
    for (int i=0; i<rows; i++)
    {
        add[i] = checkBoxes[i]->isChecked(); // Заносим данные о состоянии чекбоксов
        countChecked += static_cast<int>(checkBoxes[i]->isChecked()); // если галочка стоит, то будет +1
        //        qDebug() << i << add[i] << ui->checkBox_tot_0->isChecked() << ui->checkBox_tot_0->isDown();
    }
    if(countChecked == 0) // если не выбрано ни одной галочки
    {
        tableWidgetOnesOnlyEditing->setRowCount(0);
//        warningError("Ошибка! Выберите значения!");
        delete [] add;
        return;
    }
    //    ui->tableWidget_one_only->setRowCount(rows);
    tableWidgetOnesOnlyEditing->setColumnCount(cols);
    int c = 0; // счетчкис заполненых строк
    for (int i=0; i<rows; i++)
    {
        //        if(ui->tableWidget_tableOfTrue->item(i, cols)->text().toInt() == 1)  // если в строчке 1, то обрабатываем
        if(add[i]) // если пользователь выбрал эту строку
        {
            tableWidgetOnesOnlyEditing->setRowCount(c + 1);
            for (int j=0; j<cols; j++)
            {
                setTWText(tableWidgetOnesOnlyEditing, c, j, tableWidgetTot->item(i, j)->text()); // переносим значение ячейки в новую таблицу
            }
            c++; // увеличиваем значение счётчика
        }
    }

    delete [] add;

    setSklykiResultTableColor(tableWidgetOnesOnlyEditing);  // делаем приглёшенный цвет
}

void MainWindow::on_pushButton_tot_add_to_skeyki_1_clicked()
{
    createSkleyka(tableWidgetOnesOnly, checkBoxes_ones, tableWidgetsSkleykiEditing[0]); // создаем склейку и добавляем её в таблицу
}

void MainWindow::on_pushButton_add_skleyki_1_clicked()  // кнопка добаления склеек на основе таблицы склеек 1
{
    createSkleyka(tableWidgetsSkleyki[0], checkBoxes_skleyki_1, tableWidgetsSkleykiEditing[1]); // создаем склейку
}

void MainWindow::on_pushButton_add_skleyki_2_clicked()  // кнопка создания 3й склейки
{
    createSkleyka(tableWidgetsSkleyki[1], checkBoxes_skleyki_2, tableWidgetsSkleykiEditing[2]); // создаем склейки 3
}

/**
@brief Обрабатывает нажатие кнопки "Далее" на второй вкладке редактора склеек.
Функция переходит к следующему шагу на второй вкладке редактора склеек и
выполняет ряд операций для сортировки склеек и отображения результатов.
Перед выполнением операций, функция получает количество строк и столбцов в таблице.
Затем создает двумерный массив для хранения элементов таблицы и получает данные из таблицы.
В дальнейшем функция сортирует склейки и сохраняет их в список sortSkleikyList.
После выполнения сортировки, функция освобождает память, выделенную для двумерного массива,
и отображает отсортированные склейки в таблице.
Затем функция добавляет флажки CheckBox в последний столбец таблицы,
выполняет переход к следующему шагу и завершает свою работу.
*/
void MainWindow::on_pushButton_nextStep_skleyki_2_clicked()
{
    goToNextStep(tableWidgetsSkleykiEditing[1], tableWidgetsSkleyki[1], 3);
    int rows = tableWidgetsSkleyki[1]->rowCount(); // получаем колитечтво строк
    if(rows <= 0)
        return;
    int cols = tableWidgetsSkleyki[1]->columnCount(); // получаем количество столбцов
    if(cols <= 0)
        return;
    // создаем массив
    QString **tableText = nullptr; // массив для хранения элементов таблицы
    tableText = new QString *[rows]; // выделяем память под строки
    for (int i=0; i<rows; i++)
    {
        tableText[i] = new QString [cols]; // выделяем память под столбцы
    }
    // получаем данные из таблицы
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            tableText[i][j] = tableWidgetsSkleyki[1]->item(i, j)->text(); // сохраняем данные в массив
        }
    }
    // сортируем склейки
    QStringList sortSkleikyList; // создаем список для отсортированных склеек
    //    int lastRow = 0; // номер строки, в которую последний раз были занесены данные (склейка)
    for (int p=0; p<cols; p++) // p = номер позиции Х в строке
    {
        for (int r = 0; r < cols; ++r) // r = номер второй позиции Х в строке
        {
            qDebug() << "Ищем Х в позиции " << p << "и" << r;
            for (int i=0; i<rows; i++)
            {
                for (int j=0; j<cols; j++) // ищем первое совпадение Х
                {
                    if((tableText[i][j] == "X") && (j == p))  // если позиция Х совпадает с текущим номером
                    {
                        qDebug() << "В строке" << i << "в столбце" << j << "X находится на позиции" << p;
                        for (int k=0; k<cols; k++)
                        {
                            if((tableText[i][k] == "X") && (k == p) && (j != k))  // если позиция Х совпадает с текущим вторым номером Х
                            {
                                QString skleyka;
                                for (int h=0; h<cols; h++) // проходим по всем элементам строки
                                {
                                    skleyka.append(tableText[i][h]);
                                    //tableWidgetsSkleyki[0]->setItem(lastRow, h, new QTableWidgetItem((tableText[i][h]))); // выводим в таблицу
                                    //lastRow++; // увеличиваем на 1 номер последней строки
                                }
                                qDebug() << "Создана склейка " << skleyka;
                                sortSkleikyList.append(skleyka); // обавляем склейку в список
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i=0; i<rows; i++)
    {
        delete [] tableText[i];
        tableText[i] = nullptr;
    }
    delete [] tableText;
    tableText = nullptr;

    int size = sortSkleikyList.size(); // получаем количество склеек в списке
    for (int i=0; i<size; i++)
    {
        QString skleyka = sortSkleikyList[i]; // получаем склейку
        for (int j=0; j<skleyka.count(); j++)
        {
            tableWidgetsSkleyki[1]->setItem(i, j, new QTableWidgetItem(skleyka.at(j))); // выподим каждый элемент
        }
    }
    addCheckBoxesInLastColumn(tableWidgetsSkleyki[1], checkBoxes_skleyki_2);     // вставляем checkBox в последную колонку
    nextStep();
    //    int rows = tableWidgetsSkleyki[1]->rowCount(); // получаем количество строк
}

XORCrypter *MainWindow::getXorCrypter() const
{
    return xorCrypter;
}

void MainWindow::setXorCrypter(XORCrypter *newXorCrypter)
{
    xorCrypter = newXorCrypter;
}

bool MainWindow::checkLists(const QStringList &list1, const QStringList &list2)
{
    // перебираем все элементы первого списка
    for (const QString& item : list1)
    {
        // проверяем, содержится ли текущий элемент во втором списке
        if (!list2.contains(item))
        {
            return false; // Если элемент не найден, возвращаем false
        }
    }

    // перебираем все элементы второго списка
    for (const QString& item : list2)
    {
        // проверяем, содержится ли текущий элемент в первом списке
        if (!list1.contains(item))
        {
            return false; // Если элемент не найден, возвращаем false
        }
    }

    // если все элементы обоих списков содержатся в каждом из них, возвращаем true
    return true;
}

void MainWindow::showEvent(QShowEvent *event)
{
#ifdef __linux__
    // регулируем размер шрифта
    const QString fontSizeStyleSheet = "QWidget{font: 7pt \"Segoe UI\";}";

    QString styleSheet = this->styleSheet();
    styleSheet.append(fontSizeStyleSheet);
    this->setStyleSheet(styleSheet);

    styleSheet = ui->tabWidget->styleSheet();
    styleSheet.append(fontSizeStyleSheet);
    ui->tabWidget->setStyleSheet(styleSheet);
#endif

    event->accept();
}
