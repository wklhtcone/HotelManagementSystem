#include "roomtype.h"
#include "ui_roomtype.h"
#include <reservepage.h>
#include <QPainter>
#include <head.h>
#include<qmath.h>
#include <QMessageBox>
#include "DataStruct.h"
#include <QDebug>
extern void SetButtonStyle(QPushButton *button, QString imgsrc, int CutSec);

roomtype::roomtype(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::roomtype)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    SetButtonStyle(ui->pushButton,"../hotelmanagement/20.png",2);

    rp =new reservepage;

    connect(rp,SIGNAL(send()),this,SLOT(openthread()));
}

roomtype::~roomtype()
{
    delete ui;
}

void roomtype::setType(int t)
{
    type=t;
    switch (type)
    {
        case 0:
            ui->typelabel->setText("单人间");
            //放图片
            break;
        case 1:
            ui->typelabel->setText("双人间");
            //放图片
            break;
        case 2:
            ui->typelabel->setText("大床房");
            //放图片
            break;
        case 3:
            ui->typelabel->setText("总统套房");
            //放图片
            break;
        default:
            break;
    }
}
void roomtype::setNum(int n)
{
    num=n;
    ui->numlabel->setText(QString::number(num,10));
    if(num==0)
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton->setText("满房");
        //设置按钮图片
    }
    else
    {
        ui->pushButton->setEnabled(true);
        if(flag)
            ui->pushButton->setText("预订");
        else
            ui->pushButton->setText("入住");
        //设置按钮图片
    }

    switch (type)
    {
        case 0:
            ui->moneylabel->setText(QString::number(roomPrices[0],10));
            break;
        case 1:
            ui->moneylabel->setText(QString::number(roomPrices[2],10));
            break;
        case 2:
            ui->moneylabel->setText(QString::number(roomPrices[1],10));
            break;
        case 3:
            ui->moneylabel->setText(QString::number(roomPrices[3],10));
            break;
        default:
            break;
    }
}
void roomtype::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
    QPixmap pix;
    switch (type)
    {
        case 0:
            pix.load("../hotelmanagement/23.png");

            break;
        case 1:
            pix.load("../hotelmanagement/24.png");

            break;
        case 2:
            pix.load("../hotelmanagement/22.png");

            break;
        case 3:
            pix.load("../hotelmanagement/21.png");

            break;
        default:
            break;
    }
    painter.drawPixmap(10, 10, 272, 90, pix);
}

void roomtype::on_pushButton_clicked()
{
    int count=0;
    emit send();
    Sleep(10);
    rp->settype(type);
    rp->setDate(start,end);
    rp->setflag(flag);
    //发包
    DataStruct message;
    message.kind=_cost_query;
    message.start_time=start.toString("yyyy-MM-dd").toStdString();
    message.end_time=end.toString("yyyy-MM-dd").toStdString();
    QString temp;
    switch (type)
    {
        case 0:
            temp="单人间";
            message.room_type=temp.toStdString();
            break;
        case 1:
            temp="双人间";
            message.room_type=temp.toStdString();
            break;
        case 2:
            temp="大床房";
            message.room_type=temp.toStdString();
            break;
        case 3:
            temp="总统套房";
            message.room_type=temp.toStdString();
            break;
        default:
            break;
    }
    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "发送成功，请等待服务器响应");
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }

    //收包
    DataStruct data;
    while(clientConnector.getMessage(data)==0||data.kind!=_cost_query)
    {
        count++;
        Sleep(1000);
        if(count>5) break;
    }

    if(count>5)
    {
        QMessageBox::about(NULL, "", "超时，请重试");
        return;
    }

    //写入金额
    qDebug()<<QString::fromStdString(data.price)<< "package price";

    rp->setmoney(QString::fromStdString(data.price).toInt());
    rp->exec();

}

void roomtype::setDate(QDate starttime, QDate endtime)
{
    start=starttime;
    end=endtime;
}
void roomtype::openthread()
{
    emit open();
}
void roomtype::setflag(bool f)
{
    flag=f;
    if(flag)
        ui->pushButton->setText("预订");
    else
        ui->pushButton->setText("入住");
}

void roomtype::connectclient()
{
    while(!clientConnector.startClient())
    {
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提示", "网络连接失败，请重试", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::No)
        {
            break;
        }
    }
}
