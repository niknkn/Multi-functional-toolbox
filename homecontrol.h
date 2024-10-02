#ifndef HOMECONTROL_H
#define HOMECONTROL_H

#include <QWidget>
#include "mainwindow.h"
namespace Ui {
class homecontrol;
}


class homecontrol : public QWidget
{
    Q_OBJECT

public:
    explicit homecontrol(QWidget *parent = nullptr);
    ~homecontrol();

    void slotCloseSerialPort();
    void slotOpenSerialPort();
    void slotSend();

private slots:
    void slotReadData();
    void on_pushButton_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::homecontrol *ui;
    QSerialPort * m_serialPort;
    QString info;
};





#endif // HOMECONTROL_H
