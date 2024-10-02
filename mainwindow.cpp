#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile fp(":/mainwindow.qss");
    fp.open(QFile::ReadOnly);
    QString buff=fp.readAll();
    this->setStyleSheet(buff);
    fp.close();

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_pushButton_clicked()
{
    weather *p=new weather;
    p->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    music *p=new music;
    p->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    movie *p=new movie;
    p->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    homecontrol *p=new homecontrol;
    p->show();
}
