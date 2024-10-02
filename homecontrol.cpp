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
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) //��ȡ��Ч�Ĵ����б�
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

    m_serialPort = new QSerialPort(this);//�½�һ�����ڶ���
    if(m_serialPort->isOpen())//�ж϶����Ƿ��Ѿ��򿪣�����Ǿ͹ص�
    {
        m_serialPort->clear();
        m_serialPort->close();
    }
    //���ô�������
    m_serialPort->setPortName("COM2");
    //�򿪴���
    if (!m_serialPort->open(QIODevice::ReadWrite))//��COM2���ڣ���������Ϊ��д״̬
    {
        return;
    }

    m_serialPort->setBaudRate(9600);//������
    m_serialPort->setDataBits(QSerialPort::Data8);//����λ
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//���������ƣ���ʱ���ܣ�

    m_serialPort->setParity(QSerialPort::NoParity);//��żУ��λ
    m_serialPort->setStopBits(QSerialPort::OneStop);//ֹͣλ


    //�Ѵ��ڵĿɶ��źźͲۺ�������
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
            qWarning()<<"���һ������";

        QByteArray sendBuf;
        //���ַ���תΪ�ֽ�
        sendBuf.append(info);// = info.toLocal8Bit();
        m_serialPort->write(sendBuf);
    }
}


void homecontrol::on_pushButton_clicked()//����ͷ
{
    info = "Turn on the camera";
    slotSend();
}

void homecontrol::on_pushButton_1_clicked()//���⴫����
{
    info = "Turn on the IR sensor";
    slotSend();
}

void homecontrol::on_pushButton_2_clicked()//�ŴŴ�����
{
    info = "Turn on the door magnetic sensor";
    slotSend();
}

void homecontrol::on_pushButton_3_clicked()//��������
{
    info = "Turn on the smoke sensor";
    slotSend();
}

void homecontrol::on_pushButton_4_clicked()//ú��������
{
    info = "Turn on the gas sensor";
    slotSend();
}

void homecontrol::on_pushButton_5_clicked()//�����Ž�
{
    info = "Turn on the visual door control";
    slotSend();
}

void homecontrol::on_pushButton_6_clicked()//�Զ��Ŵ�
{
    info = "Open automatic doors and windows";
    slotSend();
}

void homecontrol::on_pushButton_7_clicked()//�Զ�����
{
    info = "Turn on the automatic curtains";
    slotSend();
}

void homecontrol::on_pushButton_8_clicked()//���ܿյ�
{
    info = "Turn on the smart air conditioner";
    slotSend();
}

void homecontrol::on_pushButton_9_clicked()//����������
{
    info = "Turn on the alarm controller";
    slotSend();
}

void homecontrol::on_pushButton_10_clicked()//���ܿ���
{
    info = "Turn on the smart switch";
    slotSend();
}

void homecontrol::on_pushButton_11_clicked()//Զ�̼��
{
    info = "Turn on Remote Monitoring";
    slotSend();
}
