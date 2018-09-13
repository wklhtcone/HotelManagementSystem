#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userinfo.h"
#include "userlog.h"
#include "employee.h"
#include <qmath.h>
#include <QToolButton>
#include <QMouseEvent>
#include <QToolBar>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include <QPushButton>
#include "head.h"

//标题栏的长度
const static int pos_min_x = 0;
const static int pos_max_x = 630 - 60;
const static int pos_min_y = 0;
const static int pos_max_y = 30;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("经理模式");

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


    //定时器
    QTimer *CurrentTime = new QTimer(this);
    CurrentTime->start(0);
    //更新时间
    connect(CurrentTime,&QTimer::timeout,[=](){
    QDateTime current_time = QDateTime::currentDateTime();
    QString StrCurrentTime = current_time.toString("yyyy-MM-dd hh:mm:ss");
    ui->currentTimeLabel->setText(StrCurrentTime);
    });

    //阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(8);
    QGraphicsDropShadowEffect *q = new QGraphicsDropShadowEffect(this);
    q->setOffset(-5, 5);
    q->setColor(Qt::black);
    q->setBlurRadius(8);
    QGraphicsDropShadowEffect *bodyShadow = new QGraphicsDropShadowEffect(this);
    bodyShadow->setBlurRadius(8);
    bodyShadow->setOffset(-5, 5);
    bodyShadow->setColor(QColor(138, 255, 177, 255));
    QGraphicsDropShadowEffect *a = new QGraphicsDropShadowEffect(this);
    a->setOffset(-5, 5);
    a->setColor(Qt::black);
    a->setBlurRadius(8);
    QGraphicsDropShadowEffect *b = new QGraphicsDropShadowEffect(this);
    b->setOffset(-5, 5);
    b->setColor(Qt::black);
    b->setBlurRadius(8);
    QGraphicsDropShadowEffect *c = new QGraphicsDropShadowEffect(this);
    c->setOffset(-5, 5);
    c->setColor(Qt::black);
    c->setBlurRadius(8);
    QGraphicsDropShadowEffect *d = new QGraphicsDropShadowEffect(this);
    d->setOffset(-5, 5);
    d->setColor(Qt::black);
    d->setBlurRadius(8);
    QGraphicsDropShadowEffect *e = new QGraphicsDropShadowEffect(this);
    e->setOffset(-5, 5);
    e->setColor(Qt::black);
    e->setBlurRadius(8);
    QGraphicsDropShadowEffect *f = new QGraphicsDropShadowEffect(this);
    f->setOffset(-5, 5);
    f->setColor(Qt::black);
    f->setBlurRadius(8);
    QGraphicsDropShadowEffect *g = new QGraphicsDropShadowEffect(this);
    g->setOffset(-5, 5);
    g->setColor(Qt::black);
    g->setBlurRadius(8);
    QGraphicsDropShadowEffect *h = new QGraphicsDropShadowEffect(this);
    h->setOffset(-5, 5);
    h->setColor(Qt::black);
    h->setBlurRadius(8);
    QGraphicsDropShadowEffect *i = new QGraphicsDropShadowEffect(this);
    i->setOffset(-5, 5);
    i->setColor(Qt::black);
    i->setBlurRadius(8);
    QGraphicsDropShadowEffect *j = new QGraphicsDropShadowEffect(this);
    j->setOffset(-5, 5);
    j->setColor(Qt::black);
    j->setBlurRadius(8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
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
    pix3.load("../SubAD/123.jpg");
    painter.drawPixmap(10, 10, 620, 460, pix3);

    //阴影
    QGraphicsDropShadowEffect *qShadow = new QGraphicsDropShadowEffect();
    qShadow->setBlurRadius(8);
    qShadow->setOffset(-5, 5);
    qShadow->setColor(Qt::black);
}

//自己实现的窗口拖动操作
void MainWindow::mousePressEvent(QMouseEvent *event)
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

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ( isMousePressed==true )
    {
        QPoint movePot = event->globalPos() - mousePosition;
        move(movePot);
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed=false;
}

//最小化窗口函数
void MainWindow::on_actionMinimize_triggered()
{
    this->showMinimized();

}
//窗口关闭
void MainWindow::on_actionClose_triggered()
{
    this->close();
}
//最大化
void MainWindow::on_actionMaximize_triggered()
{

    this->showMaximized();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    this->close();
}

void MainWindow::on_userinfoButton_clicked()
{
    queryRoom(room,"",_order_by_rid,_ascend);
    userinfo uinfowindow;
    uinfowindow.exec();


}

void MainWindow::on_userlogButton_clicked()
{
    userlog ulogwindow;
    ulogwindow.exec();
}

void MainWindow::on_employeeButton_clicked()
{
    queryEmployee(employeelist,"",_order_by_rid,_ascend);
    employee epewindow;
    epewindow.exec();
}
