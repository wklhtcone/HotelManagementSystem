#include "singleitem.h"
#include "ui_singleitem.h"
#include<QPainter>
#include <QDate>
#include <head.h>
#include<qmath.h>
singleitem::singleitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singleitem)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setcontent1(QDate::currentDate(),QDate::currentDate().addDays(1));
}

void singleitem::paintEvent(QPaintEvent *event)
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
    pix.load("../hotelmanagement/18.png");
    painter.drawPixmap(90, 37, 80, 40, pix);
}
singleitem::~singleitem()
{
    delete ui;
}

void singleitem::setcontent1(QDate start, QDate end)
{
    startdate=start;
    enddate=end;
    ui->starttimeLabel->setText(startdate.toString("MM-dd"));
    ui->endtimeLabel->setText(enddate.toString("MM-dd"));
    int t=startdate.daysTo(enddate);
    ui->lengthLabel->setText(QString::number(t,10)+"晚");
    //repaint();
}
