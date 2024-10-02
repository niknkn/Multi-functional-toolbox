#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMenuBar>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMovie>

#include <QFile>
#include <QFileDialog>

#include <QStringList>
#include <QStandardItemModel>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QGraphicsScene>
#include <QGraphicsVideoItem>

#include <QChartView>
#include <QDebug>
#include <QListWidgetItem>
#include <QtCharts>
#include <QVideoWidget>
#include <QWidget>


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "music.h"
#include "weather.h"
#include "movie.h"
#include "homecontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QMovie *dongtu;
};
#endif // MAINWINDOW_H
