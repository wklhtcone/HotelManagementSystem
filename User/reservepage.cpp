#include "reservepage.h"
#include "ui_reservepage.h"
#include <QDate>
#include <QMessageBox>
#include <windows.h>
#include <head.h>
#include <DataStruct.h>
#include <arrangeitem.h>
#include <QDebug>
#include <qmath.h>
#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>
#include <QDesktopWidget>
extern void SetButtonStyle(QPushButton *button, QString imgsrc, int CutSec);

//标题栏的长度
const static int pos_min_x = 0;
const static int pos_max_x = 340 - 60;
const static int pos_min_y = 0;
const static int pos_max_y = 30;
reservepage::reservepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservepage)
{
    ui->setupUi(this);
    SetButtonStyle(ui->pushButton,"../ihotel/19.png",2);
    setWindowTitle("IHOTEL");

    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->lineEdit_4->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->lineEdit_6->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);

    this->setWindowFlags(Qt::FramelessWindowHint);//去掉窗口标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);

    int width = this->width();//获取界面的宽度
    QToolButton *minButton = new QToolButton(this);   //最小按钮
    QToolButton *closeButton= new QToolButton(this);  //关闭按钮
    QToolButton *maxButton = new QToolButton(this);   //最大按钮

    connect(minButton, SIGNAL(clicked()), this, SLOT(on_actionMinimize_triggered()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(on_actionClose_triggered()));
    connect(maxButton, SIGNAL(clicked()), this, SLOT(on_actionMaximize_triggered()));

    //获取最小化、关闭按钮图标
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

    //设置最小化、关闭按钮图标
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    maxButton->setIcon(maxPix);
    //设置最小化、关闭按钮在界面的位置
    minButton->setGeometry(width-70,10,20,20);
    closeButton->setGeometry(width-30,10,20,20);
    maxButton->setGeometry(width-50, 10, 20, 20);

    //设置鼠标移至按钮上的提示信息
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    maxButton->setToolTip(tr("最大化"));

    //设置最小化、关闭等按钮的样式
    minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");
    maxButton->setStyleSheet("background-color:transparent;");
}

reservepage::~reservepage()
{
    delete ui;
}

void reservepage::settype(int t)
{
    type=t;
}
void reservepage::setmoney(int m)
{
    money=m;
    qDebug()<<"money"<<money;
    switch (type)
    {
        case 0:
            ui->roomtypelabel->setText("单人间");
            ui->stackedWidget->setCurrentIndex(0);
            //放图片
            break;
        case 1:
            ui->roomtypelabel->setText("双人间");
            ui->stackedWidget->setCurrentIndex(1);
            //放图片
            break;
        case 2:
            ui->roomtypelabel->setText("大床房");
            ui->stackedWidget->setCurrentIndex(1);
            //放图片
            break;
        case 3:
            ui->roomtypelabel->setText("总统套房");
            ui->stackedWidget->setCurrentIndex(0);
            //放图片
            break;
        default:
            break;
    }
    QString temp="入住"+start.toString("MM-dd")+"/离店"+end.toString("MM-dd");
    ui->datelabel->setText(temp);
    int t=start.daysTo(end);
    ui->dayslabel->setText(QString::number(t,10)+"晚");

    ui->moneylabel->setText("待支付金额 "+QString::number(money,10));
}
void reservepage::setDate(QDate starttime, QDate endtime)
{
    start=starttime;
    end=endtime;
}
void reservepage::on_pushButton_clicked()
{
    //发包
    //转型
    int count=0;
    DataStruct message;
    message.kind=_reservation;
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
    if(type==0||type==3)//单人房的情况
    {
        message.customer_id=ui->lineEdit_2->text().toStdString();
        message.name=ui->lineEdit->text().toStdString();
    }
    else
    {//多人房的情况
        temp=ui->lineEdit_4->text()+","+ui->lineEdit_6->text();
        message.customer_id=temp.toStdString();
        temp=ui->lineEdit_3->text()+","+ui->lineEdit_5->text();
        message.name=temp.toStdString();
    }
    message.start_time=start.toString("yyyy-MM-dd").toStdString();
    message.end_time=end.toString("yyyy-MM-dd").toStdString();

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
    while(clientConnector.getMessage(data)==0||data.kind!=_reservation)
    {
        count++;
        Sleep(1000);
        if(count>5) break;
    }

    if(count>5)
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        return;
    }

    //判断是否成功
    if(data.isSucceed==0)
    {
        //提示失败
        QMessageBox::about(NULL, "", "预约失败");
    }
    else
    {

        QMessageBox::about(NULL, "", "预约成功！");
    }

    this->close();
}
void reservepage::closeEvent(QCloseEvent *)
{
    emit send();
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
}
void reservepage::mousePressEvent(QMouseEvent *event)
{
        mousePosition = event->pos();
        //只对标题栏范围内的鼠标事件进行处理
        if (mousePosition.x()<=pos_min_x)
            return;
        if ( mousePosition.x()>=pos_max_x)
            return;
        if (mousePosition.y()<=pos_min_y )
            return;
        if (mousePosition.y()>=pos_max_y)
            return;
        isMousePressed = true;
}

void reservepage::mouseMoveEvent(QMouseEvent *event)
{
    if ( isMousePressed==true )
    {
        QPoint movePot = event->globalPos() - mousePosition;
        move(movePot);
    }
}
void reservepage::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed=false;
}

//最小化窗口函数
void reservepage::on_actionMinimize_triggered()
{
    this->showMinimized();

}
//窗口关闭
void reservepage::on_actionClose_triggered()
{
    this->close();
}
//最大化
void reservepage::on_actionMaximize_triggered()
{

    this->showMaximized();
}
void reservepage::paintEvent(QPaintEvent *)
{
    //绘制窗口阴影
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
    //加载背景图
    QPixmap pix3;
    pix3.load("../ihotel/555.png");
    painter.drawPixmap(10, 10, 330, 500, pix3);
}
void reservepage::connectclient()
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
