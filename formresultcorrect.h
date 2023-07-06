#ifndef FORMRESULTCORRECT_H
#define FORMRESULTCORRECT_H

#include <QWidget>

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
