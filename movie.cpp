#include "movie.h"
#include "ui_movie.h"

movie::movie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::movie)
{
    ui->setupUi(this);

    playmovie=new QMediaPlayer(this);
    videoWidget=new QVideoWidget(this);
    // 设置表格大小
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(1);

    //设置qss文件
    QFile qssFile(":/movie.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString buff = qssFile.readAll();
        setStyleSheet(buff);
    }else{
        qDebug()<<"文件打开失败"<<endl;
    }
    qssFile.close();

    // 关闭表格的自动调整行和列大小的特性
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //不显示表头
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);
    // 将QVideoWidget添加到表格单元格中
    ui->tableWidget->setCellWidget(0, 0, videoWidget);

    ui->horizontalSlider_2->setRange(0,100);

}

movie::~movie()
{
    delete ui;
}

void movie::on_pushButton_clicked()
{
    QString strCurrentPath = QDir::homePath(); //获取系统当前目录
    QString strDlgTitle = "选择视频文件";
    QString strFilter = "MP4 File(*.mp4);;All File(*.*)";// 打开视频文件过滤
    QString strAllFiles = QFileDialog::getOpenFileName(this,strDlgTitle,strCurrentPath,strFilter);

    if(strAllFiles.isEmpty())
    {
        QMessageBox::information(this,"错误","打开视频文件失败，请重新检查",QMessageBox::Yes|QMessageBox::No);
        return;
    }

    QFileInfo fileInfos(strAllFiles); // 获取文件信息
    ui->label_3->setText(fileInfos.fileName());

    playmovie->setMedia(QUrl::fromLocalFile(strAllFiles));
    playmovie->setVideoOutput(videoWidget);

    playmovie->play();

}

void movie::on_pushButton_2_clicked()//播放
{
    playmovie->play();
}

void movie::on_pushButton_3_clicked()//暂停
{
    playmovie->pause();
}

void movie::on_horizontalSlider_sliderReleased()//视频进度
{
    movietime = playmovie->duration();//获取视频时长
    ui->horizontalSlider->setRange(0,movietime);
    qint64 volume = ui->horizontalSlider->value();//获取滑块当前值
    playmovie->setPosition(volume);
}

void movie::on_horizontalSlider_2_sliderReleased()//音量调节
{
    int volume = ui->horizontalSlider_2->value();//获取滑块当前值
    playmovie->setVolume(volume);
}

void movie::on_pushButton_6_clicked()//1X
{
    playmovie->setPlaybackRate(1.0);
}

void movie::on_pushButton_7_clicked()//1.5X
{
    playmovie->setPlaybackRate(1.5);
}

void movie::on_pushButton_4_clicked()//2X
{
    playmovie->setPlaybackRate(2.0);
}

void movie::on_pushButton_8_clicked()//3X
{
    playmovie->setPlaybackRate(3.0);
}

void movie::on_pushButton_5_clicked()//4X
{
    playmovie->setPlaybackRate(4.0);
}
