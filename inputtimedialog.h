#ifndef INPUTTIMEDIALOG_H
#define INPUTTIMEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class InputTimeDialog;
}

class InputTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputTimeDialog(QWidget *parent = 0);
    ~InputTimeDialog();
    void setHour(int h);
    void setMin(int min);
    void setSec(int s);

private slots:
    void on_buttonBox_accepted();

    void on_hourBox_valueChanged(int arg1);

    void on_minBox_valueChanged(int arg1);

    void on_secBox_valueChanged(int arg1);

private:
    Ui::InputTimeDialog *ui;
    int _hour;
    int _minute;
    int _second;
signals:
    void inputedTime(QString);
};

#endif // INPUTTIMEDIALOG_H
