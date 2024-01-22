#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QBuffer>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonValue>
#include<QJsonObject>
#include<QJsonArray>
#include <QtCore5Compat/QTextCodec>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene;
    photo=new QGraphicsPixmapItem;
    ui->graphicsView->setScene(scene);
    scene->addItem(photo);
    manager=new QNetworkAccessManager;
    ratio=1;
    client_id="js0iVRjVZxKW3dN17E9zSofN";
    client_secret="b3aUQDdGj24ieMM0umnCKcUaR5O1ihC1";
    access_token="24.8a6dfb166aba905ebf204b875b1ec67b.2592000.1708355340.282335-47381960";
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));



    // debug_str="abss\nafaf\nfafa\raavava\nafa";
    // ui->textEdit->setText(debug_str);
}

MainWindow::~MainWindow()
{
    delete ui;
}








void MainWindow::on_btn_select_img_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "C:\\Users\\Rdemi\\Pictures", tr("Image Files (*.png *.jpg *.bmp)"));

    photo->setPixmap(QPixmap(fileName));
    // photo->setScale()
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QImage qi(fileName);
    QImage qp(fileName);
    qp.save(&buffer, "png");
    base64img = buffer.data().toBase64();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    /*对图片urlencode*/
    base64img = codec->fromUnicode(base64img).toPercentEncoding();



}


void MainWindow::on_btn_clear_clicked()
{

    ui->textEdit->clear();
}


void MainWindow::on_btn_recognize_clicked()
{
    QString str_url="https://aip.baidubce.com/rest/2.0/ocr/v1/general_basic?";
    QUrlQuery query1;
    query1.addQueryItem("access_token",access_token);
    QUrl url(str_url);
    url.setQuery(query1);

    QUrlQuery query2;
    query2.addQueryItem("image",base64img);
    query2.addQueryItem("detect_direction","false");
    query2.addQueryItem("detect_language","false");
    query2.addQueryItem("paragraph","false");
    query2.addQueryItem("probability","false");

    QNetworkRequest request;
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    manager->post(request,query2.query().toUtf8());

    // debug_str=debug_str.replace("\n","");
    // debug_str=debug_str.replace("\r","");
    // ui->textEdit->setText(debug_str);

}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QString text=reply->readAll();

    qDebug()<<text;
    QJsonDocument doc=QJsonDocument::fromJson(text.toUtf8());
    QJsonObject obj=doc.object();
    QJsonValue arrval=obj.value("words_result");
    ui->textEdit->append("识别的句子有");
    for(int i=0;i<arrval.toArray().size();i++){
        QString str =arrval[i].toObject().value("words").toString();
        ui->textEdit->append(str);
        ui->textEdit->append("\n");

    }

    // qDebug()<<val[0].toObject().value("words").toString();


}


void MainWindow::on_btn_zoom_up_clicked()
{
    ratio+=0.1;
    photo->setScale(ratio);
}


void MainWindow::on_btn_zoom_down_clicked()
{
    ratio-=0.1;
    photo->setScale(ratio);
}

