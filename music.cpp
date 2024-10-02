#include "music.h"
#include "ui_music.h"

music::music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music)
{
    ui->setupUi(this);
    ui->pushButton_2->setShortcut(QKeySequence(Qt::Key_Return));//设置快捷键为回车
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    QFile qssFile(":/music.qss");//设置qss文件
    if (qssFile.open(QFile::ReadOnly)) {
        QString buff = qssFile.readAll();
        setStyleSheet(buff);
    }else{
        qDebug()<<"文件打开失败"<<endl;
    }
    qssFile.close();

    playlist =new QMediaPlaylist;
    playmusic = new QMediaPlayer;
    playmusic->setPlaylist(playlist);

    connect(playmusic,SIGNAL(positionChanged(qint64)),this,SLOT(positionChangedSlot(qint64)));
    connect(playmusic,SIGNAL(durationChanged(qint64)),this,SLOT(durationChangedSlot(qint64)));
    ui->horizontalSlider_2->setRange(0,100);//音量范围为0-100

}

music::~music()
{
    delete ui;
}

void music::parseJson(QByteArray byteArray)
{
    int id=-1;
    float songtime=-1;
    QString songname;
    QString username;
    QString fromname;
    playlist->clear();

    QStandardItemModel * pModel1 = new QStandardItemModel(10,4,ui->tableView_2);
    //设置数据模型的表头
    QStringList list1 = QStringList()<<"歌名"<<"作者"<<"专辑"<<"时长";
    //应用
    pModel1->setHorizontalHeaderLabels(list1);//设置数据的表头
    ui->tableView_2->setModel(pModel1);


    QJsonDocument doc = QJsonDocument::fromJson(byteArray);//直接从字节数组中获得一个JSON文档
    if(doc.isObject()){
        QJsonObject obj1 = doc.object();
        if(obj1.contains("result") == false){
            qDebug()<<"错误的JSON对象"<<endl;
            return;
        }
        QJsonValue var = obj1.value("result");
        QJsonObject resultObj = var.toObject();
        if(resultObj.contains("songs") == false){
            qDebug()<<"JSON对象没有歌曲"<<endl;
            return;
        }

        var = resultObj.value("songs");
        if(var.isArray()){
            QJsonArray songsArr = var.toArray();
            qDebug()<<"一共搜索到"<<songsArr.size()<<"首歌曲"<<endl;

            int row=0;
            for(int i=0;i<songsArr.size();i++){
                QJsonObject song=songsArr[i].toObject();

                if(song.contains("id")==true){
                    QJsonValue vid=song.value("id");
                    id=vid.toInt();
                }

                if(song.contains("name")==true){
                    QJsonValue vsongname=song.value("name");
                    songname=vsongname.toString();
                }

                if(song.contains("artists")==true){//检查大数组里面有没有作者
                    QJsonValue vusername=song.value("artists");
                    if(vusername.isArray()==true){//有的话是不是一个数组
                        QJsonArray  Vusername=vusername.toArray();
                        for(int j=0;j<Vusername.size();j++){//是的话遍历数组找里面的对象，对象里有没有名字，有的话提取出来
                            if(Vusername[j].isObject()==true){
                                QJsonObject Username=Vusername[j].toObject();
                                if(Username.contains("name")==true){
                                    QJsonValue name=Username.value("name");
                                    username+= name.toString();
                                    username+=" ";
                                }
                            }
                        }
                    }
                }

                if(song.contains("album")==true){                //先搜索大数组里有没有专辑
                    QJsonValue vsongfrom=song.value("album");
                    if(vsongfrom.isObject()==true){              //有的话专辑是不是对象
                        QJsonObject Vsongfrom=vsongfrom.toObject();
                        if(Vsongfrom.contains("name")){          //是的话对象里有没有名字
                            QJsonValue varAlbumName =  Vsongfrom.value("name");
                            fromname=varAlbumName.toString();
                        }
                    }
                }

                if(song.contains("duration")==true){
                    QJsonValue vid=song.value("duration");
                    songtime=vid.toInt()/1000/60.f;
                }
                qDebug()<<songname<<id<<endl;
                //把音乐添加进播放列表
                playlist->addMedia(QUrl(QString("http://music.163.com/song/media/outer/url?id=%1.mp3").arg(id)));

                QStandardItem *item = new QStandardItem(QString(songname));
                pModel1->setItem(row, 0, item);
                QStandardItem *item1 = new QStandardItem(QString(username));
                pModel1->setItem(row, 1, item1);
                QStandardItem *item2 = new QStandardItem(QString(fromname));
                pModel1->setItem(row, 2, item2);
                QString songtimeStr = QString::number(songtime, 'f', 2);
                QStandardItem *item3 = new QStandardItem(songtimeStr);
                pModel1->setItem(row, 3, item3);
                row++;

                username.clear();

            }//end of for(int i=0;i<songsArr.size();i++){
        }
    }
}

void music::replyFinished(QNetworkReply *reply)
{
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200)
    {
        qDebug()<<"访问服务器成功"<<endl;
        //qDebug()<<QString(reply->readAll())<<endl;
        parseJson(reply->readAll());
    }
}

void music::on_pushButton_2_clicked()
{
    QString str=ui->lineEdit->text();
    QString STR=QString(
"http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=%1&type=1&offset=0&total=true&limit=20").arg(str);

    manager->get(QNetworkRequest(QUrl(STR)));

}

void music::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    playlist->setCurrentIndex(index.row());
    playmusic->play();
    //playmusic->stop();//放完一首就停

    //双击切换播放图标
    ui->pushButton_4->setIcon(QIcon("d:/qtimage/bofanging.bmp"));
    ui->pushButton_4->setIconSize(QSize(40, 40));
    ui->pushButton_4->show();
}

void music::positionChangedSlot(qint64 position)
{
    ui->horizontalSlider->setValue(position);//时长变化时同时设置进度条变化
}

void music::durationChangedSlot(qint64 duration)
{
    ui->horizontalSlider->setRange(0,duration);//设置滑块的总范围为歌曲的时长
}

void music::on_horizontalSlider_sliderReleased()
{
    qint64 var = ui->horizontalSlider->value();//得到滑块当前值
    playmusic->setPosition(var);//设置滑块当前值做为音乐播放的当前时间
}

void music::on_verticalSlider_sliderReleased()//设置音量
{

}



void music::on_pushButton_3_clicked()//上一首
{
    playlist->previous();
    playmusic->play();
}
void music::on_pushButton_4_clicked()//暂停，播放
{
    if(play==true){
        playmusic->pause();
        play=false;
        //暂停切换暂停图标
        ui->pushButton_4->setIcon(QIcon("d:/qtimage/bofang.bmp"));
        ui->pushButton_4->setIconSize(QSize(40, 40));
        ui->pushButton_4->show();
        return;

    }
    if(play==false){
        playmusic->play();
        play=true;
        //播放切换播放图标
        ui->pushButton_4->setIcon(QIcon("d:/qtimage/bofanging.bmp"));
        ui->pushButton_4->setIconSize(QSize(40, 40));
        ui->pushButton_4->show();
        return;
    }
}
void music::on_pushButton_5_clicked()//下一首
{
    playlist->next();
    playmusic->play();
}




void music::on_horizontalSlider_2_sliderReleased()
{
    int volume = ui->horizontalSlider_2->value();//获取滑块当前值
    playmusic->setVolume(volume);//设置音量
}
