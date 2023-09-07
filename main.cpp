#include "mainwindow.h"
#include "formlogin.h"
#include <QTextCodec>
#include "xorcrypter.h"
#include "mmkcalculator.h"

#include <QApplication>
#define XOR_CRYPT_KEY "0A1F85C6B908372D4E5F6B17C82D39A5D8290EC8CC7256B3F19ECDCE5089F3BC2B21834E0B7A6E5D6B3C34A1B9820D3F4E5A109C8F932614B295C4B3E49568B68094DD92FBDD1A2529E1E9C0845FA3ECB937D8FA3BC47A98C0A6D591321BD840356C720498BF853DACFB20DCF0A4CE5F29328EDA05D1F96C61"

/**

@file main.cpp
@brief Главная функция приложения
*/

/**

@brief Функция main, точка входа в программу
@param argc Количество аргументов командной строки
@param argv Массив аргументов командной строки
@return Код возврата приложения
*/

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

//    QFont font = w.centralWidget()->font();
//    font.setWeight(7);
//    w.centralWidget()->setFont(font);

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
    f.loadVariants();

//    w.show();
//    w.loadDataFromFile();

//    w.setNoMessage(true); // отключаем показ подсказок (после загрузки данных, они включатся из функции)
//    w.show(); // запускасем окно
//    w.setFunction("D277"); // устанавливаем функцию
//    w.setStudentName("Иванов Иван Иванович"); // передаём имя
//    w.setStudentGroup("КИБО-00-22"); // передаём группу
//    w.loadDataFromFile(); // загружаем данные


//    MmkCalculator mk;
//    MmkData mdnf;
//    bool ok = mk.calculateFunction("7D73", MmkData::MmkType::MDNF, mdnf);
//    qDebug() << "Calculate: " << ok << mdnf.toString();
//    for(const QStringList &result : mdnf.getResults())
//    {
//        qDebug() << "Полученная формула: " << mk.getFormulaByResult(result, mdnf.getMmkType());
//    }

//    QFile file("out.txt");
//    file.open(QIODevice::WriteOnly);
//    file.write(mdnf.toString().toUtf8());
//    file.close();

    return a.exec();
}
