#include "chooseroom.h"
#include "ui_chooseroom.h"
#include <QListWidgetItem>
#include <choosethread.h>
#include <head.h>
#include <singleitem.h>
#include <roomtype.h>
#include <QMessageBox>
#include <QDebug>
#include <qmath.h>
#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>
#include <QDesktopWidget>

//标题栏的长度
const static int pos_min_x = 0;
const static int pos_max_x = 340 - 60;
const static int pos_min_y = 0;
const static int pos_max_y = 30;

ChooseRoom::ChooseRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseRoom)
{
    ui->setupUi(this);

    setWindowTitle("IHOTEL");

    QDesktopWidget* desktop = QApplication::desktop();
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

    c_Thread=new chooseThread(this);

    connect(c_Thread,SIGNAL(send(int)),this,SLOT(refreshNum(int)));

    connect(&rt,SIGNAL(send()),c_Thread,SLOT(stopImmediately()));
    connect(&stdr,SIGNAL(send()),c_Thread,SLOT(stopImmediately()));
    connect(&br,SIGNAL(send()),c_Thread,SLOT(stopImmediately()));
    connect(&lr,SIGNAL(send()),c_Thread,SLOT(stopImmediately()));

    connect(&rt,SIGNAL(open()),this,SLOT(openthread()));
    connect(&stdr,SIGNAL(open()),this,SLOT(openthread()));
    connect(&br,SIGNAL(open()),this,SLOT(openthread()));
    connect(&lr,SIGNAL(open()),this,SLOT(openthread()));

    ui->dateWidget->setStyleSheet("background-color:transparent");
    ui->dateWidget->setFrameShape(QListWidget::NoFrame);
    ui->roomWidget->setStyleSheet("background-color:transparent");
    ui->roomWidget->setFrameShape(QListWidget::NoFrame);

    //时间段
    QListWidgetItem *nitem = new QListWidgetItem(ui->dateWidget);
    nitem->setSizeHint(QSize(0,110));
    ui->dateWidget->setItemWidget(nitem,&si);
    ui->dateWidget->addItem(nitem);

    //单人间
    rt.setType(0);
    QListWidgetItem *ritem = new QListWidgetItem(ui->roomWidget);
    ritem->setSizeHint(QSize(0,110));
    ui->roomWidget->setItemWidget(ritem,&rt);
    ui->roomWidget->addItem(ritem);

    //双人间
    stdr.setType(1);
    QListWidgetItem *sitem = new QListWidgetItem(ui->roomWidget);
    sitem->setSizeHint(QSize(0,110));
    ui->roomWidget->setItemWidget(sitem,&stdr);
    ui->roomWidget->addItem(sitem);

    //大床房
    br.setType(2);
    QListWidgetItem *bitem = new QListWidgetItem(ui->roomWidget);
    bitem->setSizeHint(QSize(0,110));
    ui->roomWidget->setItemWidget(bitem,&br);
    ui->roomWidget->addItem(bitem);

    //总统套房
    lr.setType(3);
    QListWidgetItem *litem = new QListWidgetItem(ui->roomWidget);
    litem->setSizeHint(QSize(0,110));
    ui->roomWidget->setItemWidget(litem,&lr);
    ui->roomWidget->addItem(litem);
}

ChooseRoom::~ChooseRoom()
{
    qDebug() << "start destroy widget";
    c_Thread->stopImmediately();
    c_Thread->wait();
    delete ui;
    qDebug() << "end destroy widget";
}
void ChooseRoom::daterange(QDate come, QDate leave)
{
    start=come;
    end=leave;
    si.setcontent1(start,end);
    rt.setDate(start,end);
    stdr.setDate(start,end);
    br.setDate(start,end);
    lr.setDate(start,end);
    //设置时间
    c_Thread->setDate(start,end);
}

void ChooseRoom::refreshNum(int count)
{
    singleR=roomNums[0];
    standardR=roomNums[1];
    bedR=roomNums[2];
    LuxuryR=roomNums[3];
    rt.setNum(singleR);
    stdr.setNum(standardR);
    br.setNum(bedR);
    lr.setNum(LuxuryR);

    qDebug()<<count<<"refreshnum1";
    if(count>5)
    {
        qDebug()<<count<<"refreshnum2";
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提示", "网络连接失败", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes)
        {
            this->close();
        }
    }

}
void ChooseRoom::closeEvent(QCloseEvent *)
{
    c_Thread->stopImmediately();
}
void ChooseRoom::openthread()
{
    c_Thread->start();
}

void ChooseRoom::mousePressEvent(QMouseEvent *event)
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

void ChooseRoom::mouseMoveEvent(QMouseEvent *event)
{
    if ( isMousePressed==true )
    {
        QPoint movePot = event->globalPos() - mousePosition;
        move(movePot);
    }
}
void ChooseRoom::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed=false;
}

//最小化窗口函数
void ChooseRoom::on_actionMinimize_triggered()
{
    this->showMinimized();

}
//窗口关闭
void ChooseRoom::on_actionClose_triggered()
{
    this->close();
}
//最大化
void ChooseRoom::on_actionMaximize_triggered()
{

    this->showMaximized();
}
void ChooseRoom::paintEvent(QPaintEvent *)
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
    pix3.load("../ihotel/444.png");
    painter.drawPixmap(10, 10, 330, 580, pix3);
}
