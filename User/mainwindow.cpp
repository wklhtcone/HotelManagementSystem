#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <singleitem.h>
#include <chooseroom.h>
#include <arrangeitem.h>
#include <arrangethread.h>
#include <head.h>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGraphicsDropShadowEffect>
#include <QTextCharFormat>
#include <QMessageBox>
#include <QDebug>
#include <DataStruct.h>
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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("IHOTEL");

    ui->daysEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));

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

    a_thread=new arrangeThread(this);

    connect(a_thread,SIGNAL(send(QString)),this,SLOT(refreshHistory(QString)));

    islogged=false;

    ui->pagestack->setCurrentIndex(0);

    ui->historyWidget->setStyleSheet("background-color:transparent");
    ui->historyWidget->setFrameShape(QListWidget::NoFrame);

    QListWidgetItem *nitem = new QListWidgetItem(ui->listWidget);
    nitem->setSizeHint(QSize(0,110));
    si=new singleitem;
    ui->listWidget->setItemWidget(nitem,si);
    ui->listWidget->addItem(nitem);
    ui->listWidget->setStyleSheet("background-color:transparent");
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    QObject::connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doubleclicked1()));

    count=0;
    former=ui->calendarWidget->selectedDate();
    later=former.addDays(1);
    QObject::connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(selectdate()));

    QBrush brush;
    QTextCharFormat cf;
    brush.setColor( Qt::green );
    cf = ui->calendarWidget->dateTextFormat( former );
    cf.setBackground( brush );
    ui->calendarWidget->setDateTextFormat( former, cf );

    brush.setColor( Qt::blue );
    cf = ui->calendarWidget->dateTextFormat( later );
    cf.setBackground( brush );
    ui->calendarWidget->setDateTextFormat( later, cf );

    QDate pale;
    pale=QDate::currentDate().addDays(-QDate::currentDate().day()+1);

    brush.setColor( Qt::gray );
    for(;pale.daysTo(QDate::currentDate())>0;pale=pale.addDays(1))
    {
        //qDebug()<<pale.toString("MM-dd");
        cf = ui->calendarWidget->dateTextFormat( pale );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( pale, cf );
    }

    SetButtonStyle(ui->okButton,"../ihotel/16.png",2);
    SetButtonStyle(ui->reserveButton,"../ihotel/11.png",2);
    SetButtonStyle(ui->arrangeButton,"../ihotel/8.png",2);
    SetButtonStyle(ui->extendButton,"../ihotel/9.png",2);
    SetButtonStyle(ui->loginButton,"../ihotel/10.png",2);
    SetButtonStyle(ui->switchButton,"../ihotel/15.png",2);
    SetButtonStyle(ui->makeextendButton,"../ihotel/15.png",2);
    SetButtonStyle(ui->checkButton,"../ihotel/15.png",2);

    QGraphicsDropShadowEffect *a = new QGraphicsDropShadowEffect(this);
    a->setOffset(-5, 5);
    a->setColor(Qt::gray);
    a->setBlurRadius(8);
    QGraphicsDropShadowEffect *b = new QGraphicsDropShadowEffect(this);
    b->setOffset(-5, 5);
    b->setColor(Qt::gray);
    b->setBlurRadius(8);
    QGraphicsDropShadowEffect *c = new QGraphicsDropShadowEffect(this);
    c->setOffset(-5, 5);
    c->setColor(Qt::gray);
    c->setBlurRadius(8);
    QGraphicsDropShadowEffect *d = new QGraphicsDropShadowEffect(this);
    d->setOffset(-5, 5);
    d->setColor(Qt::gray);
    d->setBlurRadius(8);
    QGraphicsDropShadowEffect *e = new QGraphicsDropShadowEffect(this);
    e->setOffset(-5, 5);
    e->setColor(Qt::gray);
    e->setBlurRadius(8);
    QGraphicsDropShadowEffect *f = new QGraphicsDropShadowEffect(this);
    f->setOffset(-5, 5);
    f->setColor(Qt::gray);
    f->setBlurRadius(8);
    QGraphicsDropShadowEffect *g = new QGraphicsDropShadowEffect(this);
    g->setOffset(-5, 5);
    g->setColor(Qt::gray);
    g->setBlurRadius(8);
    QGraphicsDropShadowEffect *h = new QGraphicsDropShadowEffect(this);
    h->setOffset(-5, 5);
    h->setColor(Qt::gray);
    h->setBlurRadius(8);

    ui->reserveButton->setGraphicsEffect(a);
    ui->arrangeButton->setGraphicsEffect(b);
    ui->extendButton->setGraphicsEffect(c);
    ui->loginButton->setGraphicsEffect(d);
    ui->switchButton->setGraphicsEffect(e);
    ui->makeextendButton->setGraphicsEffect(f);
    ui->checkButton->setGraphicsEffect(g);
    ui->okButton->setGraphicsEffect(h);
}

MainWindow::~MainWindow()
{
    qDebug() << "start destroy widget";
    a_thread->stopImmediately();
    a_thread->wait();
    delete ui;
    qDebug() << "end destroy widget";
}

void MainWindow::on_reserveButton_clicked()
{
    ui->pagestack->setCurrentIndex(0);
    //关线程
    if(a_thread->isRunning())
    {
        a_thread->stopImmediately();
        qDebug()<<"关线程";
    }
    //转换按钮图片
    SetButtonStyle(ui->reserveButton,"../ihotel/11.png",2);
    SetButtonStyle(ui->arrangeButton,"../ihotel/8.png",2);
    SetButtonStyle(ui->extendButton,"../ihotel/9.png",2);
    SetButtonStyle(ui->loginButton,"../ihotel/10.png",2);
}

void MainWindow::doubleclicked1()
{
    ui->pagestack->setCurrentIndex(4);
}

void MainWindow::selectdate()
{
    QBrush brush;
    QTextCharFormat cf;
    QDate pale;

    if(ui->calendarWidget->selectedDate().daysTo(QDate::currentDate())>0)
        return;

    count++;
    int t=former.daysTo(ui->calendarWidget->selectedDate());
    if(count%2==1)
    {
        //清除画图
        brush.setColor( Qt::white );
        cf = ui->calendarWidget->dateTextFormat( former );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( former, cf );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );

        former=ui->calendarWidget->selectedDate();
        later=former;

    }
    else if(count%2==0&&t>0)
    {
        later=ui->calendarWidget->selectedDate();
    }
    else if(count%2==0&&t<=0)
    {
        //清除画图
        brush.setColor( Qt::white );
        cf = ui->calendarWidget->dateTextFormat( former );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( former, cf );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );

        former=ui->calendarWidget->selectedDate();
        later=former;
    }

    //画former和later
    brush.setColor( Qt::green );
    cf = ui->calendarWidget->dateTextFormat( former );
    cf.setBackground( brush );
    ui->calendarWidget->setDateTextFormat( former, cf );

    if(former.daysTo(later)!=0)
    {
        brush.setColor( Qt::yellow );
        pale=former.addDays(1);
        for(;pale.daysTo(later)>0;pale=pale.addDays(1))
        {
            cf = ui->calendarWidget->dateTextFormat( pale );
            cf.setBackground( brush );
            ui->calendarWidget->setDateTextFormat( pale, cf );
        }

        brush.setColor( Qt::blue );
        cf = ui->calendarWidget->dateTextFormat( later );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( later, cf );
    }

}

void MainWindow::on_arrangeButton_clicked()
{
    ui->pagestack->setCurrentIndex(1);
    //转换按钮图片
    SetButtonStyle(ui->reserveButton,"../ihotel/6.png",2);
    SetButtonStyle(ui->arrangeButton,"../ihotel/12.png",2);
    SetButtonStyle(ui->extendButton,"../ihotel/9.png",2);
    SetButtonStyle(ui->loginButton,"../ihotel/10.png",2);

    if(islogged==false)
    {
        ui->historylabel->setText("您未登录");
    }
    else
    {
        //开线程刷新列表
        a_thread->start();
        a_thread->setID(username,password);
        QMessageBox::about(NULL, "", "正在获取您的行程...");
        ui->historylabel->setText("您的行程");
    }
}

void MainWindow::on_extendButton_clicked()
{
    ui->pagestack->setCurrentIndex(2);
    //转换按钮图片
    SetButtonStyle(ui->reserveButton,"../ihotel/6.png",2);
    SetButtonStyle(ui->arrangeButton,"../ihotel/8.png",2);
    SetButtonStyle(ui->extendButton,"../ihotel/13.png",2);
    SetButtonStyle(ui->loginButton,"../ihotel/10.png",2);

    //关线程
    if(a_thread->isRunning())
    {
        a_thread->stopImmediately();
        qDebug()<<"关线程";
    }

    if(islogged==false)
    {
        ui->ischeckedlabel->setText("您未登录");
        ui->daysEdit->setReadOnly(true);
        ui->makeextendButton->setEnabled(false);
    }
    else
    {
        ui->ischeckedlabel->setText("续住服务");
        ui->daysEdit->setReadOnly(false);
        ui->makeextendButton->setEnabled(true);
    }
}

void MainWindow::on_loginButton_clicked()
{
    ui->pagestack->setCurrentIndex(3);
    //转换按钮图片
    SetButtonStyle(ui->reserveButton,"../ihotel/6.png",2);
    SetButtonStyle(ui->arrangeButton,"../ihotel/8.png",2);
    SetButtonStyle(ui->extendButton,"../ihotel/9.png",2);
    SetButtonStyle(ui->loginButton,"../ihotel/14.png",2);

    //关线程
    if(a_thread->isRunning())
    {
        a_thread->stopImmediately();
        qDebug()<<"关线程";
    }

    if(islogged==false)
    {
        ui->statelabel->setText("未登录");
        ui->switchButton->setText("登录");
        ui->lineEdit->setText("");
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit_2->setText("");
        ui->lineEdit_2->setReadOnly(false);
    }
    else
    {
        ui->statelabel->setText("您已登录");
        ui->switchButton->setText("切换账号");
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
    }
}

void MainWindow::on_checkButton_clicked()
{
    si->setcontent1(former,later);
    ui->pagestack->setCurrentIndex(0);
    //转换按钮图片
    SetButtonStyle(ui->reserveButton,"../ihotel/11.png",2);
    SetButtonStyle(ui->arrangeButton,"../ihotel/8.png",2);
    SetButtonStyle(ui->extendButton,"../ihotel/9.png",2);
    SetButtonStyle(ui->loginButton,"../ihotel/10.png",2);
}

void MainWindow::on_okButton_clicked()
{
    cr.daterange(former,later);
    //开线程监听房间剩余量
    cr.c_Thread->start();
    //发包（日期）
    DataStruct message;
    message.kind=_time_query;
    message.start_time=former.toString("yyyy-MM-dd").toStdString();
    message.end_time=later.toString("yyyy-MM-dd").toStdString();

    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "正在获取房间信息");
        cr.exec();
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
    }
}

void MainWindow::on_switchButton_clicked()
{
    if(islogged==true)
    {
        ui->statelabel->setText("未登录");
        ui->switchButton->setText("登录");
        ui->lineEdit->setText("");
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit_2->setText("");
        ui->lineEdit_2->setReadOnly(false);
        islogged=false;
    }
    else
    {
        username=ui->lineEdit->text().toStdString();
        password=ui->lineEdit_2->text().toStdString();
        ui->statelabel->setText("您已登录");
        ui->switchButton->setText("切换账号");
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
        islogged=true;
    }
}

void MainWindow::on_makeextendButton_clicked()
{   
    int tcount=0;
    int t=ui->daysEdit->text().toInt();
    //发包
    DataStruct message;
    message.kind=_stay_over_info;
    message.customer_id=password;
    message.name=username;
    message.day=t;

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
    while(!clientConnector.getMessage(data)||data.kind!=_stay_over_info)
    {
        tcount++;
        Sleep(1000);
        if(tcount>5)break;
    }

    if(tcount>5)
    {
        QMessageBox::about(NULL, "", "超时，请重试");
        return;
    }

    //判断
    //提示是否续住成功
    //如果成功
    if(data.isSucceed)
    {
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提示", "您确定要续住到"+QString::fromStdString(data.end_time)+"吗?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes)
        {
            //发包
            DataStruct message_1;
            message_1.kind=_stay_over;
            message_1.customer_id=password;
            message_1.name=username;
            message_1.day=t;
            if(!clientConnector.sendMessage(message_1))
            {
                QMessageBox::about(NULL, "", "网络连接失败");
                connectclient();
                return;
            }

            //收包
            tcount=0;
            DataStruct data_1;
            while(!clientConnector.getMessage(data_1)||data_1.kind!=_stay_over)
            {
                tcount++;
                Sleep(1000);
                if(tcount>5)break;
            }

            if(tcount>5)
            {
                QMessageBox::about(NULL, "", "超时，请重试");
                return;
            }

            if(data_1.isSucceed)
            {
                QMessageBox::about(NULL, "", "续住成功，花费"+QString::fromStdString(data.price)+",您的房间号为"+QString::fromStdString(data_1.room_id));
            }
            else
            {
                QMessageBox::about(NULL, "", "续住失败");
            }
        }
    }
    else
        QMessageBox::about(NULL, "", "请先登记入住");
}

void MainWindow::refreshHistory(QString S)
{
    //清空
    int counter =ui->historyWidget->count();
    for(int index=0;index<counter;index++)
    {
        QListWidgetItem *item = ui->historyWidget->takeItem(0);
        delete item;
    }
    //刷新
    for(int i=0;i<history.size();i++)
    {
        QListWidgetItem *nitem = new QListWidgetItem(ui->historyWidget);
        nitem->setSizeHint(QSize(0,110));
        arrangeitem *ai=new arrangeitem;
        ai->setcontent(history[i][0],history[i][1],history[i][2],history[i][3],history[i][4],username,password);
        ui->historyWidget->setItemWidget(nitem,ai);
        ui->historyWidget->addItem(nitem);
    }
}
void MainWindow::connectclient()
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
    pix3.load("../ihotel/555.png");
    painter.drawPixmap(10, 10, 330, 500, pix3);
}
