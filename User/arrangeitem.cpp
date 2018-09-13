#include "arrangeitem.h"
#include "ui_arrangeitem.h"
#include <QPainter>
#include <qmath.h>
#include <QDate>
#include <QPushButton>
#include <head.h>
#include <QMessageBox>
#include "DataStruct.h"
void SetButtonStyle(QPushButton *button, QString imgsrc, int CutSec)
{
    int img_w=QPixmap(imgsrc).width();
    int img_h=QPixmap(imgsrc).height();
    int PicWidth = img_w/CutSec;
    button->setFixedSize(PicWidth,img_h);
    button->setStyleSheet(QString("QPushButton{border-width: 41px; border-image: url(%1)  0 0 0 %2 repeat  repeat;border-width: 0px; border-radius: 0px;}")
      .append("QPushButton::hover{border-image: url(%1) 0 0 0 %3  repeat  repeat;}")
      .append("QPushButton::pressed{border-image: url(%1) 0  0 0 %4 repeat  repeat;}")
      .append("QPushButton::checked{border-image: url(%1) 0  0 0 %4 repeat  repeat;}")
      .append("QPushButton::disabled{border-image: url(%1) 0  0 0 %5 repeat  repeat;}")
      .arg(imgsrc).arg(0).arg(PicWidth*1).arg(PicWidth*2).arg(PicWidth*3));
}
arrangeitem::arrangeitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::arrangeitem)
{
    ui->setupUi(this);
    SetButtonStyle(ui->pushButton,"../ihotel/19.png",2);
}

arrangeitem::~arrangeitem()
{
    delete ui;
}
void arrangeitem::setcontent(string roomnum, string roomtype, string starttime, string endtime, string f, string name, string pass)
{
    num=roomnum;
    start=starttime;
    end=endtime;
    room_type=roomtype;
    username=name;
    password=pass;
    flag=f;
    ui->roomnumlabel->setText(QString::fromStdString(roomnum));
    ui->daterangelabel->setText(QString::fromStdString(starttime)+"~"+QString::fromStdString(endtime)); 
    ui->roometypelabel->setText(QString::fromStdString(roomtype));
    int t=QString::fromStdString(flag).toInt();
    if(t==0)
    {
        ui->pushButton->setText("取消预约");
        ui->pushButton->setEnabled(true);
    }
    else
    {
        ui->pushButton->setText("已经入住");
        ui->pushButton->setEnabled(false);
    }
}
void arrangeitem::on_pushButton_clicked()
{
    //发包
    DataStruct message;
    message.kind=_cancel;//发送取消预约信息
    message.room_id=num;
    message.customer_id=password;
    message.name=username;
    message.now_time=QDate::currentDate().toString("yyyy-MM-dd").toStdString();
    message.start_time=start;
    message.end_time=end;

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

}
void arrangeitem::paintEvent(QPaintEvent *event)
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
    QString type=QString::fromStdString(room_type);
    if(QString::compare(type,"单人间")==0)
            pix.load("../ihotel/23.png");
    else if(QString::compare(type,"双人间")==0)
            pix.load("../ihotel/24.png");

    else if(QString::compare(type,"大床房")==0)
            pix.load("../ihotel/22.png");

     else if(QString::compare(type,"总统套房")==0)
            pix.load("../ihotel/21.png");

    painter.drawPixmap(10, 10, 236, 90, pix);
}
void arrangeitem::connectclient()
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
