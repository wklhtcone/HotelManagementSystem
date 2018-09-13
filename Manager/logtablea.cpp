#include "logtablea.h"
#include "ui_logtablea.h"
#include <QTableWidget>
#include <QPainter>
#include <tableaquery.h>
#include <ui_tableaquery.h>
#include "head.h"
logtablea::logtablea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logtablea)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
}

logtablea::~logtablea()
{
    delete ui;
}
//背景图
void logtablea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix6;
    pix6.load("../SubAD/789.jpg");
    painter.drawPixmap(10, 10, 680, 480, pix6);
}

void logtablea::on_aqueButton_clicked()
{
    tableaquery aquewindow;
    aquewindow.exec();
    ui->tableWidget->clearContents();
    int RowCont;//打印
    for(RowCont=0;RowCont<res_log.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(res_log[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(res_log[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(res_log[RowCont][2])));
        ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem(QString::fromStdString(res_log[RowCont][3])));
        ui->tableWidget->setItem(RowCont,4,new QTableWidgetItem(QString::fromStdString(res_log[RowCont][4])));
        if(res_log[RowCont][5]=="0")
        {
            ui->tableWidget->setItem(RowCont,5,new QTableWidgetItem("取消预约操作"));
        }
        else
        {
            ui->tableWidget->setItem(RowCont,5,new QTableWidgetItem("预约操作"));
        }
        ui->tableWidget->setItem(RowCont,6,new QTableWidgetItem(QString::fromStdString(res_log[RowCont][6])));
    }
}
