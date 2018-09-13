#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <singleitem.h>
#include <chooseroom.h>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextCharFormat>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <qmath.h>
#include <QPixmap>
#include <QDebug>
#include <head.h>

//标题栏的长度
const static int pos_min_x = 0;
const static int pos_max_x = 679 - 60;
const static int pos_min_y = 0;
const static int pos_max_y = 30;

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

bool cmpDataString(string threeBitStr,char *twoBitStr)
{
    threeBitStr.erase(threeBitStr.find_last_not_of(" ")+1);
    if(0==QString::compare(QString::fromStdString(threeBitStr),QString::fromLocal8Bit(twoBitStr)))
    {
        return true;
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->nameline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->passwordline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->singlenameline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->singlepasswordline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->doublename1line->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->doublename2line->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->doublepass1line->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->doublepass2line->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->extendnameline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->extendpassline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->daysline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->checkoutnameline->setStyleSheet("background:transparent;border-width:1;border-style:outset");
    ui->checkoutpassline->setStyleSheet("background:transparent;border-width:1;border-style:outset");

    ui->daysline->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->passwordline->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->singlepasswordline->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->doublepass1line->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->doublepass2line->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->extendpassline->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    ui->checkoutpassline->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));

    QListWidgetItem *nitem = new QListWidgetItem(ui->listWidget);
    nitem->setSizeHint(QSize(0,110));
    si=new singleitem;
    ui->listWidget->setItemWidget(nitem,si);
    ui->listWidget->addItem(nitem);
    ui->listWidget->setStyleSheet("background-color:transparent");
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    QObject::connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doubleclicked1()));

    QObject::connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(doubleclicked2()));

    count=0;
    former=ui->calendarWidget->selectedDate();
    later=former.addDays(1);
    endd=QDate::currentDate().addDays(1);
    QObject::connect(ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(selectdate()));

    QObject::connect(ui->calendarWidget_2,SIGNAL(clicked(QDate)),this,SLOT(selectdate_2()));

    QBrush brush;
    QTextCharFormat cf;
    brush.setColor( Qt::green );
    cf = ui->calendarWidget->dateTextFormat( former );
    cf.setBackground( brush );
    ui->calendarWidget->setDateTextFormat( former, cf );

    cf = ui->calendarWidget_2->dateTextFormat( QDate::currentDate() );
    cf.setBackground( brush );
    ui->calendarWidget_2->setDateTextFormat( QDate::currentDate(), cf );

    brush.setColor( Qt::blue );
    cf = ui->calendarWidget->dateTextFormat( later );
    cf.setBackground( brush );
    ui->calendarWidget->setDateTextFormat( later, cf );

    cf = ui->calendarWidget_2->dateTextFormat( QDate::currentDate().addDays(1) );
    cf.setBackground( brush );
    ui->calendarWidget_2->setDateTextFormat( QDate::currentDate().addDays(1), cf );

    QDate pale;
    pale=QDate::currentDate().addDays(-QDate::currentDate().day()+1);

    brush.setColor( Qt::gray );
    for(;pale.daysTo(QDate::currentDate())>0;pale=pale.addDays(1))
    {
        cf = ui->calendarWidget->dateTextFormat( pale );
        cf.setBackground( brush );
        ui->calendarWidget->setDateTextFormat( pale, cf );

        cf = ui->calendarWidget_2->dateTextFormat( pale );
        cf.setBackground( brush );
        ui->calendarWidget_2->setDateTextFormat( pale, cf );
    }

    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

    setWindowTitle("IHOTEL");

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

    QGraphicsDropShadowEffect *a = new QGraphicsDropShadowEffect(this);
    a->setOffset(-5, 5);
    a->setColor(QColor(67,67,67));
    a->setBlurRadius(8);
    QGraphicsDropShadowEffect *b = new QGraphicsDropShadowEffect(this);
    b->setOffset(-5, 5);
    b->setColor(QColor(67,67,67));
    b->setBlurRadius(8);
    QGraphicsDropShadowEffect *c = new QGraphicsDropShadowEffect(this);
    c->setOffset(-5, 5);
    c->setColor(QColor(67,67,67));
    c->setBlurRadius(8);
    QGraphicsDropShadowEffect *d = new QGraphicsDropShadowEffect(this);
    d->setOffset(-5, 5);
    d->setColor(QColor(67,67,67));
    d->setBlurRadius(8);
    QGraphicsDropShadowEffect *e = new QGraphicsDropShadowEffect(this);
    e->setOffset(-5, 5);
    e->setColor(QColor(67,67,67));
    e->setBlurRadius(8);
    QGraphicsDropShadowEffect *f = new QGraphicsDropShadowEffect(this);
    f->setOffset(-5, 5);
    f->setColor(QColor(67,67,67));
    f->setBlurRadius(8);
    QGraphicsDropShadowEffect *g = new QGraphicsDropShadowEffect(this);
    g->setOffset(-5, 5);
    g->setColor(QColor(67,67,67));
    g->setBlurRadius(8);
    QGraphicsDropShadowEffect *h = new QGraphicsDropShadowEffect(this);
    h->setOffset(-5, 5);
    h->setColor(QColor(67,67,67));
    h->setBlurRadius(8);
    QGraphicsDropShadowEffect *i = new QGraphicsDropShadowEffect(this);
    i->setOffset(-5, 5);
    i->setColor(QColor(67,67,67));
    i->setBlurRadius(8);
    QGraphicsDropShadowEffect *j = new QGraphicsDropShadowEffect(this);
    j->setOffset(-5, 5);
    j->setColor(QColor(67,67,67));
    j->setBlurRadius(8);
    QGraphicsDropShadowEffect *k = new QGraphicsDropShadowEffect(this);
    k->setOffset(-5, 5);
    k->setColor(QColor(67,67,67));
    k->setBlurRadius(8);
    QGraphicsDropShadowEffect *l = new QGraphicsDropShadowEffect(this);
    l->setOffset(-5, 5);
    l->setColor(QColor(67,67,67));
    l->setBlurRadius(8);
    QGraphicsDropShadowEffect *m = new QGraphicsDropShadowEffect(this);
    m->setOffset(-5, 5);
    m->setColor(QColor(67,67,67));
    m->setBlurRadius(8);


    SetButtonStyle(ui->reserveButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->searchButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->checkoutButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->extendButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->loginButton,"../hotelmanagement/2.png",2);
    SetButtonStyle(ui->pushButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->login_searchButton,"../hotelmanagement/4.png",2);
    SetButtonStyle(ui->singlefinalButton,"../hotelmanagement/4.png",2);
    SetButtonStyle(ui->doublefinalButton,"../hotelmanagement/4.png",2);
    SetButtonStyle(ui->selectenddateButton,"../hotelmanagement/4.png",2);
    SetButtonStyle(ui->makeextendButton,"../hotelmanagement/4.png",2);
    SetButtonStyle(ui->setdateButton,"../hotelmanagement/4.png",2);
    SetButtonStyle(ui->checkoutButton_2,"../hotelmanagement/4.png",2);

    ui->reserveButton->setGraphicsEffect(a);
    ui->searchButton->setGraphicsEffect(b);
    ui->checkoutButton->setGraphicsEffect(c);
    ui->extendButton->setGraphicsEffect(d);
    ui->loginButton->setGraphicsEffect(e);
    ui->pushButton->setGraphicsEffect(f);
    ui->login_searchButton->setGraphicsEffect(g);
    ui->singlefinalButton->setGraphicsEffect(h);
    ui->doublefinalButton->setGraphicsEffect(i);
    ui->selectenddateButton->setGraphicsEffect(j);
    ui->makeextendButton->setGraphicsEffect(k);
    ui->setdateButton->setGraphicsEffect(l);
    ui->checkoutButton_2->setGraphicsEffect(m);
}

void MainWindow::doubleclicked1()
{
    ui->stackedWidget->setCurrentIndex(4);
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->nameline->setText("");
    ui->passwordline->setText("");
    SetButtonStyle(ui->reserveButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->searchButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->checkoutButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->extendButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->loginButton,"../hotelmanagement/2.png",2);
    ui->customerstack->setCurrentIndex(0);
}

void MainWindow::on_reserveButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    SetButtonStyle(ui->reserveButton,"../hotelmanagement/2.png",2);
    SetButtonStyle(ui->searchButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->checkoutButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->extendButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->loginButton,"../hotelmanagement/1.png",2);

}

void MainWindow::on_extendButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    SetButtonStyle(ui->reserveButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->searchButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->checkoutButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->extendButton,"../hotelmanagement/2.png",2);
    SetButtonStyle(ui->loginButton,"../hotelmanagement/1.png",2);
}

void MainWindow::on_searchButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    SetButtonStyle(ui->reserveButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->searchButton,"../hotelmanagement/2.png",2);
    SetButtonStyle(ui->checkoutButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->extendButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->loginButton,"../hotelmanagement/1.png",2);

    int tcount=0;
    //发包
    DataStruct message;
    message.kind=_room_query;
    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "正在查询，请等待服务器响应");
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }
    //收包
    DataStruct data;
    while(!clientConnector.getMessage(data)||data.kind!=_room_query)
    {
        tcount++;
        Sleep(1000);
        if(tcount>5)break;
    }

    if(tcount>5)
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        return;
    }

    roomResult=data.result;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clearContents();

    for(int i=0;i<roomResult.size();i++)
    {
        //增加一行
        ui->tableWidget->insertRow(i);
        //插入元素
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(roomResult[i][0])));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(roomResult[i][1])));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromStdString(roomResult[i][2])));
        if(QString::fromStdString(roomResult[i][3]).toInt()==1)
            ui->tableWidget->setItem(i,3,new QTableWidgetItem("有人"));
        else
            ui->tableWidget->setItem(i,3,new QTableWidgetItem("无人"));
    }
}

void MainWindow::on_login_searchButton_clicked()
{
    int tcount;
    //发包
    DataStruct message;
    message.kind=_check_in_query;//发送请求入住
    message.customer_id=ui->passwordline->text().toStdString();
    message.name=ui->nameline->text().toStdString();
    if(!clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }

    //收包：是否有预约，房间号，房间类型
    QMessageBox::about(NULL, "", "正在查询，请等待服务器响应");
    tcount=0;
    DataStruct data;
    while(!clientConnector.getMessage(data)||data.kind!=_check_in_query)
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
    //显示
    if(data.isSucceed)
    {
        //如果有预约：
        roomtypetemp=data.room_type;
        starttimetemp=data.start_time;
        endtimetemp=data.end_time;
        roomid=data.room_id;

        roomtypetemp.erase(roomtypetemp.find_last_not_of(" ")+1);
        QString tmp=QString::fromStdString(roomtypetemp);

        if(QString::compare(tmp,"单人间")==0||QString::compare(tmp,"总统套房")==0)
        {
            ui->customerstack->setCurrentIndex(1);
            if(QString::compare(tmp,"单人间")==0)
                ui->roomtypeinfolabel->setText("最近预约：单人间");
            else
                ui->roomtypeinfolabel->setText("最近预约：总统套房");
            ui->singlenameline->setText(ui->nameline->text());
            ui->singlepasswordline->setText(ui->passwordline->text());
            ui->singledatelabel->setText(QString::fromStdString(data.start_time)+"~"+QString::fromStdString(data.end_time));
        }
        else
        {
            ui->customerstack->setCurrentIndex(2);
            if(QString::compare(tmp,"双人间")==0)
                ui->roomtyeinfo2label->setText("最近预约：双人间");
            else
                ui->roomtyeinfo2label->setText("最近预约：大床房");
            ui->doublename1line->setText(ui->nameline->text());
            ui->doublepass1line->setText(ui->passwordline->text());
            ui->doublename2line->setText("");
            ui->doublepass2line->setText("");
            ui->doubledatelabel->setText(QString::fromStdString(data.start_time)+"~"+QString::fromStdString(data.end_time));
        }
    }
    else
    {
        //如果无预约选择离店日期
        ui->customerstack->setCurrentIndex(3);
        QMessageBox::about(NULL, "", "您没有预约，如果您想要直接登记入住，请选择离店日期");
    }

}

void MainWindow::on_singlefinalButton_clicked()
{
    int tcount=0;
    //发包
    DataStruct message;
    message.kind=_check_in_reserverd;//发送预约入户包
    message.room_id=roomid;
    message.customer_id=ui->singlepasswordline->text().toStdString();
    message.name=ui->singlenameline->text().toStdString();
    message.room_type=roomtypetemp;
    message.start_time=starttimetemp;
    message.end_time=endtimetemp;
    message.now_time=QDate::currentDate().toString("yyyy-MM-dd").toStdString();
    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "提交成功，请等待服务器响应");
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }

    //收包
    tcount=0;
    DataStruct data;
    while(!clientConnector.getMessage(data)||data.kind!=_check_in_reserverd)
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

    if(data.isSucceed)
       //收到入住成功
        QMessageBox::about(NULL, "", "入住成功，您的房间号为："+QString::fromStdString(roomid));
    else
        QMessageBox::about(NULL, "", "入住失败");

    ui->singlenameline->setText("");
    ui->singlepasswordline->setText("");
    ui->nameline->setText("");
    ui->passwordline->setText("");
    ui->customerstack->setCurrentIndex(0);
}

void MainWindow::on_doublefinalButton_clicked()
{
    int tcount=0;
    QString tmp;
    //发包
    DataStruct message;
    message.kind=_check_in_reserverd;
    message.room_id=roomid;
    tmp=ui->doublepass1line->text()+","+ui->doublepass2line->text();
    message.customer_id=tmp.toStdString();
    tmp=ui->doublename1line->text()+","+ui->doublename2line->text();
    message.name=tmp.toStdString();
    message.room_type=roomtypetemp;
    message.start_time=starttimetemp;
    message.end_time=endtimetemp;

    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "提交成功，请等待服务器响应");
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }

    //收包 
    tcount=0;
    DataStruct data;
    while(!clientConnector.getMessage(data)||data.kind!=_check_in_reserverd)
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

    if(data.isSucceed)
       //收到入住成功
        QMessageBox::about(NULL, "", "入住成功，您的房间号为："+QString::fromStdString(roomid));
    else
        QMessageBox::about(NULL, "", "入住失败");

    ui->doublename1line->setText("");
    ui->doublename2line->setText("");
    ui->doublepass1line->setText("");
    ui->doublepass2line->setText("");
    ui->nameline->setText("");
    ui->passwordline->setText("");
    ui->customerstack->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()
{

    //发包（日期）
    DataStruct message;
    message.kind=_time_query;
    message.start_time=former.toString("yyyy-MM-dd").toStdString();
    message.end_time=later.toString("yyyy-MM-dd").toStdString();
    if(!clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }

    //开线程监听房间剩余量
    cr.c_Thread->start();
    cr.setflag(true);
    cr.daterange(former,later);
    cr.exec();
    //关线程
}

void MainWindow::on_makeextendButton_clicked()
{
    int tcount;
    int t=ui->daysline->text().toInt();
    //发包
    DataStruct message;
    message.kind=_stay_over_info;
    message.customer_id=ui->extendpassline->text().toStdString();
    message.name=ui->extendnameline->text().toStdString();
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
    tcount=0;
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
            message_1.customer_id=ui->extendpassline->text().toStdString();
            message_1.name=ui->extendnameline->text().toStdString();
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

    ui->extendnameline->setText("");
    ui->extendpassline->setText("");
    ui->daysline->setText("");
}

void MainWindow::on_setdateButton_clicked()
{
    si->setcontent1(former,later);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_selectenddateButton_clicked()
{

    //发包（日期）
    DataStruct message;
    message.kind=_time_query;
    message.start_time=former.toString("yyyy-MM-dd").toStdString();
    message.end_time=later.toString("yyyy-MM-dd").toStdString();
    if(!clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }

    //开线程监听房间剩余量
    cr.c_Thread->start();
    cr.setflag(false);
    cr.daterange(QDate::currentDate(),endd);
    cr.exec();
    ui->customerstack->setCurrentIndex(0);
    ui->nameline->setText("");
    ui->passwordline->setText("");
    //关线程
}
 void MainWindow::selectdate_2()
 {
     QBrush brush;
     QTextCharFormat cf;
     QDate pale;

     if(ui->calendarWidget_2->selectedDate().daysTo(QDate::currentDate())>=0)
         return;

     //清除enddate底色
     brush.setColor( Qt::white );
     cf = ui->calendarWidget_2->dateTextFormat( endd );
     cf.setBackground( brush );
     ui->calendarWidget_2->setDateTextFormat( endd, cf );

     pale=QDate::currentDate().addDays(1);
     for(;pale.daysTo(endd)>0;pale=pale.addDays(1))
     {
         cf = ui->calendarWidget_2->dateTextFormat( pale );
         cf.setBackground( brush );
         ui->calendarWidget_2->setDateTextFormat( pale, cf );
     }

     endd=ui->calendarWidget_2->selectedDate();

     //画endd
     brush.setColor( Qt::yellow );
     pale=QDate::currentDate().addDays(1);
     for(;pale.daysTo(endd)>0;pale=pale.addDays(1))
     {
         cf = ui->calendarWidget_2->dateTextFormat( pale );
         cf.setBackground( brush );
         ui->calendarWidget_2->setDateTextFormat( pale, cf );
     }
     brush.setColor( Qt::blue );
     cf = ui->calendarWidget_2->dateTextFormat( endd );
     cf.setBackground( brush );
     ui->calendarWidget_2->setDateTextFormat( endd, cf );
 }

void MainWindow::on_checkoutButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    SetButtonStyle(ui->reserveButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->searchButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->checkoutButton,"../hotelmanagement/2.png",2);
    SetButtonStyle(ui->extendButton,"../hotelmanagement/1.png",2);
    SetButtonStyle(ui->loginButton,"../hotelmanagement/1.png",2);
}

void MainWindow::on_checkoutButton_2_clicked()
{
    int tcount=0;
    //发包
    DataStruct message;
    message.kind=_check_out;
    message.customer_id=ui->checkoutpassline->text().toStdString();
    message.name=ui->checkoutnameline->text().toStdString();
    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "正在查询，请等待服务器响应");
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }

    //收包：是否已入住
    DataStruct data;
    while(!clientConnector.getMessage(data)||data.kind!=_check_out)
    {
        tcount++;
        Sleep(1000);
        if(tcount>5)break;
    }

    if(tcount>5)
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        return;
    }

    //显示
    if(data.isSucceed)
    {
        QMessageBox::about(NULL, "", "退房成功！");
    }
    else
    {
        QMessageBox::about(NULL, "", "您没有并没有入住本店");
    }
    ui->checkoutpassline->setText("");
    ui->checkoutnameline->setText("");
}
void MainWindow::doubleclicked2()
{
    qDebug()<<ui->tableWidget->currentRow();
    int tcount=0;

    //发包
    DataStruct message;
    message.kind=_room_info_query;
    message.room_id=roomResult[ui->tableWidget->currentRow()][0];
    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "请等待服务器响应");
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }
    //收包
    DataStruct data;
    while(!clientConnector.getMessage(data)||data.kind!=_room_info_query)
    {
        tcount++;
        Sleep(1000);
        if(tcount>5)break;
    }

    if(tcount>5)
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        return;
    }

    roomInfo=data.result;

    QMessageBox::about(NULL, "", "正在查询该房间信息");
    ui->stackedWidget->setCurrentIndex(5);

    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->clearContents();

    for(int i=0;i<roomInfo.size();i++)
    {
        //增加一行
        ui->tableWidget_2->insertRow(i);
        //插入元素
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(QString::fromStdString(roomInfo[i][0])));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::fromStdString(roomInfo[i][1])));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::fromStdString(roomInfo[i][2])));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString::fromStdString(roomInfo[i][3])));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::fromStdString(roomInfo[i][4])));
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
    pix3.load("../hotelmanagement/1111.png");
    painter.drawPixmap(10, 10, 669, 480, pix3);
}
