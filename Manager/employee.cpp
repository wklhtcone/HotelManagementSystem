#include "employee.h"
#include "ui_employee.h"
#include "employeeadd.h"
#include "ui_employeeadd.h"
#include "employeequery.h"
#include "ui_employeequery.h"
#include "employeemodify.h"
#include "ui_employeemodify.h"
#include <QTableWidget>
#include <QPainter>
#include <QDebug>
#include "managerfunc.h"
#include <QMessageBox>
#include "head.h"
QString old_e_id;
employee::employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employee)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);//隐藏行
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //禁止修改
    int RowCont;//打印
    for(RowCont=0;RowCont<employeelist.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][2])));
    }
}

employee::~employee()
{
    delete ui;
}
void employee::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix8;
    pix8.load("../SubAD/789.jpg");
    painter.drawPixmap(10, 10, 680, 480, pix8);
}

void employee::on_eaddButton_clicked()
{
   employeeadd eaddwindow;
   eaddwindow.exec();
   ui->tableWidget->clearContents();
   int RowCont;//打印
   for(RowCont=0;RowCont<employeelist.size();RowCont++)
   {
       ui->tableWidget->insertRow(RowCont);//增加一行
       ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][0])));
       ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][1])));
       ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][2])));
   }
   queryEmployee(employeelist,"",_order_by_eid,_ascend);
}

void employee::on_edelButton_2_clicked()
{
    QTableWidgetItem * item = ui->tableWidget->currentItem();
    if(item==Q_NULLPTR)return;
    int row2=ui->tableWidget->currentItem()->row();//获取行号
    item=ui->tableWidget->item(row2,0);
    QString e_id1=item->text();
    qDebug()<<e_id1;
    ui->tableWidget->removeRow(item->row());
    if(deleteEmployee(e_id1))
    {
        QMessageBox::information(this, "结果", "删除成功",QMessageBox::Ok);
        this->close();
    }
    else
    {
        QMessageBox::information(this, "结果", "删除失败",QMessageBox::Ok);
    }
}


void employee::on_emodButton_3_clicked()
{
    QTableWidgetItem * item = ui->tableWidget->currentItem();
    if(item==Q_NULLPTR)return;
    int row3=ui->tableWidget->currentItem()->row();
    item=ui->tableWidget->item(row3,0);
    old_e_id=item->text();
    qDebug()<<old_e_id;
    employeemodify emodifywindow;
    emodifywindow.exec();
    ui->tableWidget->clearContents();
    queryEmployee(employeelist,"",_order_by_eid,_ascend);
    int RowCont;//打印
    for(RowCont=0;RowCont<employeelist.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][2])));
    }
    queryEmployee(employeelist,"",_order_by_eid,_ascend);
}

void employee::on_equeButton_4_clicked()
{
    employeequery equewindow;
    equewindow.exec();
    ui->tableWidget->clearContents();
    int RowCont;//打印
    for(RowCont=0;RowCont<employeelist.size();RowCont++)
    {
        ui->tableWidget->insertRow(RowCont);//增加一行
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][0])));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][1])));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem(QString::fromStdString(employeelist[RowCont][2])));
    }
}
