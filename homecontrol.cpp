#include "homecontrol.h"
#include "ui_homecontrol.h"

homecontrol::homecontrol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::homecontrol)
{
    ui->setupUi(this);
    QFile fp(":/h-c.qss");
    fp.open(QFile::ReadOnly);
    QString buff=fp.readAll();
    this->setStyleSheet(buff);
    fp.close();



    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) //获取有效的串口列表
    {
        m_serialPortName << info.portName();
        qWarning()<<"serialPortName:"<<info.portName();
    }

    slotOpenSerialPort();


}

homecontrol::~homecontrol()
{
    delete ui;
}



void homecontrol::slotCloseSerialPort()
{
    if (m_serialPort)
        m_serialPort->close();
}

void homecontrol::slotOpenSerialPort()
{

    m_serialPort = new QSerialPort(this);//新建一个串口对象
    if(m_serialPort->isOpen())//判断对象是否已经打开，如果是就关掉
    {
        m_serialPort->clear();
        m_serialPort->close();
    }
    //设置串口名字
    m_serialPort->setPortName("COM2");
    //打开串口
    if (!m_serialPort->open(QIODevice::ReadWrite))//打开COM2串口，并且设置为读写状态
    {
        return;
    }

    m_serialPort->setBaudRate(9600);//波特率
    m_serialPort->setDataBits(QSerialPort::Data8);//数据位
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//数据流控制（暂时不管）

    m_serialPort->setParity(QSerialPort::NoParity);//奇偶校验位
    m_serialPort->setStopBits(QSerialPort::OneStop);//停止位


    //把串口的可读信号和槽函数连接
    connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(slotReadData()));
}

void homecontrol::slotReadData()
{
    QString data = m_serialPort->readAll();
    qDebug()<<data;
}


void homecontrol::slotSend()
{
    if (m_serialPort)
    {
        if (!m_serialPort->isOpen())
            qWarning()<<"请打开一个串口";

        QByteArray sendBuf;
        //把字符串转为字节
        sendBuf.append(info);// = info.toLocal8Bit();
        m_serialPort->write(sendBuf);
    }
}


void homecontrol::on_pushButton_clicked()//摄像头
{
    info = "Turn on the camera";
    slotSend();
}

void homecontrol::on_pushButton_1_clicked()//红外传感器
{
    info = "Turn on the IR sensor";
    slotSend();
}

void homecontrol::on_pushButton_2_clicked()//门磁传感器
{
    info = "Turn on the door magnetic sensor";
    slotSend();
}

void homecontrol::on_pushButton_3_clicked()//烟雾传感器
{
    info = "Turn on the smoke sensor";
    slotSend();
}

void homecontrol::on_pushButton_4_clicked()//煤气传感器
{
    info = "Turn on the gas sensor";
    slotSend();
}

void homecontrol::on_pushButton_5_clicked()//可视门禁
{
    info = "Turn on the visual door control";
    slotSend();
}

void homecontrol::on_pushButton_6_clicked()//自动门窗
{
    info = "Open automatic doors and windows";
    slotSend();
}

void homecontrol::on_pushButton_7_clicked()//自动窗帘
{
    info = "Turn on the automatic curtains";
    slotSend();
}

void homecontrol::on_pushButton_8_clicked()//智能空调
{
    info = "Turn on the smart air conditioner";
    slotSend();
}

void homecontrol::on_pushButton_9_clicked()//报警控制器
{
    info = "Turn on the alarm controller";
    slotSend();
}

void homecontrol::on_pushButton_10_clicked()//智能开关
{
    info = "Turn on the smart switch";
    slotSend();
}

void homecontrol::on_pushButton_11_clicked()//远程监控
{
    info = "Turn on Remote Monitoring";
    slotSend();
}
