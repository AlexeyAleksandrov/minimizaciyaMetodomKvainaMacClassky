#include "mainwindow.h"
#include "formlogin.h"
#include <QTextCodec>
#include "xorcrypter.h"

#include <QApplication>
#define XOR_CRYPT_KEY "0123456789"

int main(int argc, char *argv[])
{

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
    a.setStyle("fusion");
//    QString function = ""; // функция для минимизации

    XORCrypter xorCrypter;      // шифровальщик
    xorCrypter.setKey(XOR_CRYPT_KEY);

    MainWindow w;
    w.setXorCrypter(&xorCrypter);
//    w.setMinimumWidth(564);
//    w.setMaximumWidth(564);
//    w.setMinimumHeight(796);
//    w.setMaximumHeight(796);

    // дизайн
//    QPalette m_pal;
//    m_pal.setColor(QPalette::Active, QPalette::Window, QColor(212,211,232));
//    m_pal.setColor(QPalette::Active, QPalette::WindowText, QColor(0,0,0));
//    m_pal.setColor(QPalette::Active, QPalette::Base, QColor(232,219,216,91));
//    m_pal.setColor(QPalette::Active, QPalette::Text, QColor(0,0,0));
//    m_pal.setColor(QPalette::Active, QPalette::Button, QColor(226,232,227,94));
//    m_pal.setColor(QPalette::Active, QPalette::ButtonText, QColor(0,0,0));
//    w.setPalette(m_pal);
//    w.setAutoFillBackground(true);

    w.setWindowTitle("Минимизация логических функций, заданных векторным способом, методом Куайна Мак-Класски");
    FormLogin f(w);
    f.setXorCrypter(&xorCrypter);
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
