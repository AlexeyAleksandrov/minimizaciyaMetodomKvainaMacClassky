#include "formresultcorrect.h"
#include "ui_formresultcorrect.h"

FormResultCorrect::FormResultCorrect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormResultCorrect)
{
    ui->setupUi(this);
}

FormResultCorrect::~FormResultCorrect()
{
    delete ui;
}

void FormResultCorrect::setStudent_name(const QString &value)
{
    student_name = value;
}

void FormResultCorrect::setGroup(const QString &value)
{
    group = value;
}

void FormResultCorrect::setType(const QString &type)
{
    m_type = type;
}

void FormResultCorrect::setFunction(const QString &value)
{
    function = value;
}

void FormResultCorrect::applyData()
{
    ui->label_fio->setText("ФИО: " + student_name);
    ui->label_group->setText("Группа: " + group);
    ui->label_func->setText("Функция: " + function);
    ui->label_type->setText("Тип минимизации: " + m_type);
}
