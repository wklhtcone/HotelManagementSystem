#include "logtableb.h"
#include "ui_logtableb.h"
#include <QTableWidget>
#include <QPainter>
#include <tablebquery.h>
#include <ui_tablebquery.h>
#include "head.h"
logtableb::logtableb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logtableb)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
}

logtableb::~logtableb()
{
    delete ui;
}
//背景图
void logtableb::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix7;
    pix7.load("../SubAD/789.jpg");
    painter.drawPixmap(10, 10, 680, 480, pix7);
}

void logtableb::on_bqueButton_clicked()
{
    tablebquery bquewindow;
    bquewindow.exec();
    ui->tableWidget->clearContents();
    int RowCont;//打印
    for(RowCont=0;RowCont<check_log.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(check_log[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(check_log[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(check_log[RowCont][2])));
        ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem(QString::fromStdString(check_log[RowCont][3])));
        ui->tableWidget->setItem(RowCont,4,new QTableWidgetItem(QString::fromStdString(check_log[RowCont][4])));

    }
}
