#include "add.h"
#include "ui_add.h"
#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>
#include "head.h"
#include <managerfunc.h>
#include <QLabel>
add::add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
    roomEdit = new QTextEdit;
    pushButton = new QPushButton;
    singleButton = new QRadioButton;
    bigButton = new QRadioButton;
    doubleButton = new QRadioButton;
    presButton = new QRadioButton;
}

add::~add()
{
    delete ui;
}

void add::on_pushButton_clicked()
{
   QString r_id;
   r_id=ui->roomEdit->toPlainText();
   QString r_type;
   float price;
   if(ui->singleButton->isChecked()==1)
   {
       r_type="单人间";
       price=single_room_price;
   }
   else if(ui->bigButton->isChecked()==1)
   {
       r_type="大床房";
       price=big_room_price;
   }
   else if(ui->doubleButton->isChecked()==1)
   {
       r_type="双人间";
       price=double_room_price;
   }
   else if(ui->presButton->isChecked()==1)
   {
       r_type="总统套房";
       price=pres_room_price;
   }
   else
   {
       r_type="单人间";
       price=single_room_price;
   }
   qDebug()<<r_type;
   qDebug()<<r_id;
   qDebug()<<price;
   if(addNewRoom(r_id,r_type,price))
   {
       QMessageBox::information(this, "结果", "添加成功",QMessageBox::Ok);
       this->close();
   }
   else
   {
       QMessageBox::information(this, "结果", "添加失败",QMessageBox::Ok);
   }
   queryRoom(room,"",_order_by_rid,_ascend);
}



void add::on_singleButton_clicked()
{
    if(ui->singleButton->isChecked()==1)
    {
        QString data1 = QString("%1").arg(single_room_price);
        ui->label_4->setText(data1);
    }
}

void add::on_bigButton_clicked()
{
    if(ui->bigButton->isChecked()==1)
    {
        QString data2 = QString("%1").arg(big_room_price);
        ui->label_4->setText(data2);
    }
}

void add::on_doubleButton_clicked()
{
    if(ui->doubleButton->isChecked()==1)
    {
        QString data3 = QString("%1").arg(double_room_price);
        ui->label_4->setText(data3);
    }
}

void add::on_presButton_clicked()
{
    if(ui->presButton->isChecked()==1)
    {
        QString data4 = QString("%1").arg(pres_room_price);
        ui->label_4->setText(data4);
    }
}
