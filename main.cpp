#include "mainwindow.h"
#include "formlogin.h"
#include <QTextCodec>

#include <QApplication>

int main(int argc, char *argv[])
{

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
//    QString function = ""; // функция для минимизации


    MainWindow w;
    w.setMinimumWidth(564);
    w.setMaximumWidth(564);
    w.setMinimumHeight(796);
    w.setMaximumHeight(796);

    w.setWindowTitle("Минимизация логических функций, заданных векторным способом, методом Куайна Мак-Класски");
    FormLogin f(w);
    f.show();

//    w.show();
//    w.loadDataFromFile();

//    w.setNoMessage(true); // отключаем показ подсказок (после загрузки данных, они включатся из функции)
//    w.show(); // запускасем окно
//    w.setFunction("D277"); // устанавливаем функцию
//    w.setStudentName("Иванов Иван Иванович"); // передаём имя
//    w.setStudentGroup("КИБО-00-22"); // передаём группу
//    w.loadDataFromFile(); // загружаем данные

    return a.exec();
}
