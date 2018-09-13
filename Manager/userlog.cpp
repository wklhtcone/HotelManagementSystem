#include "userlog.h"
#include "ui_userlog.h"
#include <QPushButton>
#include <QPainter>
#include "logtablea.h"
#include "ui_logtablea.h"
#include "logtableb.h"
#include "ui_logtableb.h"
userlog::userlog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userlog)
{
    ui->setupUi(this);

}

userlog::~userlog()
{
    delete ui;

}
//背景图
void userlog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix5;
    pix5.load("../SubAD/123.jpg");
    painter.drawPixmap(10, 10, 680, 480, pix5);
}

void userlog::on_logaButton_clicked()
{
    logtablea logawindow;
    logawindow.exec();
}

void userlog::on_logbButton_clicked()
{
    logtableb logbwindow;
    logbwindow.exec();
}
