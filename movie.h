#ifndef MOVIE_H
#define MOVIE_H

#include <QWidget>
#include <mainwindow.h>
namespace Ui {
class movie;
}

class movie : public QWidget
{
    Q_OBJECT

public:
    explicit movie(QWidget *parent = nullptr);
    ~movie();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_2_sliderReleased();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::movie *ui;
    QMediaPlayer *playmovie;
    QVideoWidget *videoWidget;
    qint64 movietime;
};

#endif // MOVIE_H
