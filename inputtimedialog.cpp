#include "inputtimedialog.h"
#include "ui_inputtimedialog.h"

#include <QValidator>
#include <QTime>

InputTimeDialog::InputTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputTimeDialog),
    _hour(1),
    _minute(0),
    _second(0)
{
    ui->setupUi(this);
    //value is setted in ui disigner
    ui -> hourBox->setValue(1);
}

InputTimeDialog::~InputTimeDialog()
{
    delete ui;
}

void InputTimeDialog::on_buttonBox_accepted()
{
    QTime t(_hour,_minute,_second,0);
    emit inputedTime(t.toString());
}

void InputTimeDialog::setHour(int h)
{
    _hour = h;
}

void InputTimeDialog::setMin(int min)
{
    _minute = min;
}

void InputTimeDialog::setSec(int s)
{
    _second = s;
}

void InputTimeDialog::on_hourBox_valueChanged(int arg1)
{
    setHour(arg1);
}

void InputTimeDialog::on_minBox_valueChanged(int arg1)
{
    setMin(arg1);
}

void InputTimeDialog::on_secBox_valueChanged(int arg1)
{
    setSec(arg1);
}
