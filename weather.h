#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include"mainwindow.h"
namespace Ui {
class weather;
}

class weather : public QWidget
{
    Q_OBJECT

public:
    explicit weather(QWidget *parent = nullptr);
    ~weather();
    void parseJson(QByteArray byteArray);

private slots:
    void on_pushButton_clicked();
    void replyFinished(QNetworkReply *reply);

private:
    Ui::weather *ui;
    QNetworkAccessManager *manager;
    QStandardItemModel * pModel;



};

#endif // WEATHER_H
