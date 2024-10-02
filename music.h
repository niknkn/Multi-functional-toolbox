#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include<mainwindow.h>
namespace Ui {
class music;
}

class music : public QWidget
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = nullptr);
    ~music();
    void parseJson(QByteArray byteArray);

private slots:
    void replyFinished(QNetworkReply* reply);

    void on_pushButton_2_clicked();

    void on_tableView_2_doubleClicked(const QModelIndex &index);
    void positionChangedSlot(qint64 position);
    void durationChangedSlot(qint64 duration);

    void on_horizontalSlider_sliderReleased();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_verticalSlider_sliderReleased();

    void on_horizontalSlider_2_sliderReleased();

private:
    Ui::music *ui;
    QNetworkAccessManager *manager;
    QString str;
    QMediaPlaylist *playlist;
    QMediaPlayer *playmusic;
    bool play=true;


};

#endif // MUSIC_H
