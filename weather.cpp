#include "weather.h"
#include "ui_weather.h"

weather::weather(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::weather)
{
    ui->setupUi(this);
    pModel = new QStandardItemModel(7,8,ui->tableView);
    //设置数据模型的表头
    QStringList list1 = QStringList()<<"城市"<<"日期"<<"星期"<<"最低温"<<"最高温"<<"风向"<<"风力"<<"天气";
    //应用
    pModel->setHorizontalHeaderLabels(list1);//设置数据的表头
    ui->tableView->setModel(pModel);

    ui->pushButton->setShortcut(QKeySequence(Qt::Key_Return));//设置快捷键为回车
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    QFile fp(":/weather.qss");
    fp.open(QFile::ReadOnly);
    QString buff=fp.readAll();
    this->setStyleSheet(buff);
    fp.close();

}

weather::~weather()
{
    delete ui;
}

void weather::parseJson(QByteArray byteArray)
{

    QString city;
    QString ymd;
    QString week;
    QString fx;//风
    QString fl;
    QString hot;
    QString cold;
    QString type;//天气
    QString date;

    QJsonDocument doc = QJsonDocument::fromJson(byteArray);//直接从字节数组中获得一个JSON文档
    if(doc.isObject()){
        QJsonObject obj1 = doc.object();

        QJsonValue var = obj1.value("data");
        QJsonObject resultObj = var.toObject();

        if(resultObj.contains("forecast") == false){
            qDebug()<<"JSON对象没有天气"<<endl;
            return;
        }

        var = obj1.value("cityInfo");
        if(var.isObject()){
            QJsonObject cityob = var.toObject();
            var = cityob.value("city");
            city=var.toString();
        }


        QChart *chart = new QChart();//新建一个图表对象
        chart->setTitle("近15天的温度情况");
        QLineSeries *series1;
        QLineSeries *series2;
        series1 = new QLineSeries();//创建连线对象
        series2 = new QLineSeries();

        var=resultObj.value("forecast");
        if(var.isArray()){
            QJsonArray wee=var.toArray();
            for(int i=0;i<15;i++){
                if(wee[i].isObject())
                {
                    QJsonObject day0=wee[i].toObject();
                    var=day0.value("high");
                    hot=var.toString();
                    var=day0.value("low");
                    cold=var.toString();
                    var=day0.value("ymd");
                    ymd=var.toString();
                    var=day0.value("week");
                    week=var.toString();
                    var=day0.value("fx");
                    fx=var.toString();
                    var=day0.value("fl");
                    fl=var.toString();
                    var=day0.value("type");
                    type=var.toString();
                    //qDebug()<<city<<ymd<<week<<hot<<cold<<fx<<fl<<type<<endl;

                    QStandardItem *item = new QStandardItem(QString(city));
                    pModel->setItem(i, 0, item);
                    QStandardItem *item1 = new QStandardItem(QString(ymd));
                    pModel->setItem(i, 1, item1);
                    QStandardItem *item2 = new QStandardItem(QString(week));
                    pModel->setItem(i, 2, item2);
                    QStandardItem *item3 = new QStandardItem(QString(cold));
                    pModel->setItem(i, 3, item3);
                    QStandardItem *item4 = new QStandardItem(QString(hot));
                    pModel->setItem(i, 4, item4);
                    QStandardItem *item5 = new QStandardItem(QString(fx));
                    pModel->setItem(i, 5, item5);
                    QStandardItem *item6 = new QStandardItem(QString(fl));
                    pModel->setItem(i, 6, item6);
                    QStandardItem *item7 = new QStandardItem(QString(type));
                    pModel->setItem(i, 7, item7);

                    QRegExp regExp("\\d+");  // \d+ 匹配一个或多个数字
                    regExp.indexIn(hot);
                    QString numberStr = regExp.cap(0);  // 提取匹配的字符串
                    int numberhot = numberStr.toInt();

                    regExp.indexIn(cold);
                    numberStr = regExp.cap(0);
                    int numbercold = numberStr.toInt();

                    date=ymd.replace("-","");

                    series1->append(QPointF(i,numberhot));//往连线中加入点
                    series2->append(QPointF(i,numbercold));


                }
            }//end of for(int i=0;i<15;i++){
            chart->addSeries(series1);//把连线加入到图表
            chart->addSeries(series2);
            chart->createDefaultAxes();//创建坐标轴
            chart->axisX()->setTitleText("日期(距今天数)");//设置XY轴的标题
            chart->axisY()->setTitleText("温度");

            chart->setAnimationOptions(QChart::AllAnimations);
            ui->widget->setChart(chart);
        }

    }
}

void weather::replyFinished(QNetworkReply *reply)
{
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200)
    {
        qDebug()<<"访问服务器成功"<<endl;
        //qDebug()<<QString(reply->readAll())<<endl;
        parseJson(reply->readAll());
    }
}

void weather::on_pushButton_clicked()
{
    QString STR=QString("http://t.weather.sojson.com/api/weather/city/%1").arg(ui->lineEdit->text());
    manager->get(QNetworkRequest(QUrl(STR)));
}
