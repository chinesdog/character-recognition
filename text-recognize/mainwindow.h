#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkRequest>
#include<qnetwork.h>
#include<QtNetwork/QNetworkReply>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsPixmapItem>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // QString base64img;
    QByteArray base64img;
    QString client_id ;
    QString client_secret ;
    QString access_token;
    QString debug_str;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *photo;
    QNetworkAccessManager *manager;
    qreal ratio;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:


    void on_btn_select_img_clicked();

    void on_btn_clear_clicked();

    void on_btn_recognize_clicked();

    void replyFinished(QNetworkReply* reply);

    void on_btn_zoom_up_clicked();

    void on_btn_zoom_down_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
