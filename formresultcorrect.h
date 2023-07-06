#ifndef FORMRESULTCORRECT_H
#define FORMRESULTCORRECT_H

#include <QWidget>

// автоматический define сплиттера, в зависимости от версии компилятора
// если не произошла проблема, исправь версию. Чтобы узнать версию используй QString::number(QT_VERSION, 16)
#if QT_VERSION >= 0x050f00 // версия Qt 5.15.0
#define SPLITTER Qt::SplitBehavior(Qt::SkipEmptyParts)
#else
#define SPLITTER QString::SkipEmptyParts
#endif

namespace Ui {
    class FormResultCorrect;
}

class FormResultCorrect : public QWidget
{
    Q_OBJECT

public:
    explicit FormResultCorrect(QWidget *parent = nullptr);
    ~FormResultCorrect();

    void setStudent_name(const QString &value);
    void setGroup(const QString &value);
    void setType(const QString &type);
    void setFunction(const QString &value);

    void applyData();

private:
    Ui::FormResultCorrect *ui;
    QString student_name;
    QString group;
    QString m_type;
    QString function;
};

#endif // FORMRESULTCORRECT_H
