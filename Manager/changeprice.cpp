#include "changeprice.h"
#include "ui_changeprice.h"
#include "head.h"
#include <QMessageBox>
changeprice::changeprice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changeprice)
{
    ui->setupUi(this);
    QString new_p;
    new_p=ui->textEdit->toPlainText();
    float new_price=new_p.toFloat();
    if(ui->srButton->isChecked()==1)
    {
        single_room_price=new_price;
    }
    if(ui->brButton_2->isChecked()==1)
    {
        big_room_price=new_price;
    }
    if(ui->drButton_3->isChecked()==1)
    {
        double_room_price=new_price;
    }
    if(ui->prButton_4->isChecked()==1)
    {
        pres_room_price=new_price;
    }
}

changeprice::~changeprice()
{
    delete ui;
}

void changeprice::on_pushButton_clicked()
{
    QString new_p;
    new_p=ui->textEdit->toPlainText();
    QString new_type;
    float new_price=new_p.toFloat();
    if(ui->srButton->isChecked()==1)
    {
        single_room_price=new_price;
        new_type="单人间";
    }
    if(ui->brButton_2->isChecked()==1)
    {
        big_room_price=new_price;
        new_type="大床房";
    }
    if(ui->drButton_3->isChecked()==1)
    {
        double_room_price=new_price;
        new_type="双人间";
    }
    if(ui->prButton_4->isChecked()==1)
    {
        pres_room_price=new_price;
        new_type="总统套房";
    }
    if(alterRoomPrice(new_type,new_price))
    {
        QMessageBox::information(this, "结果", "修改成功",QMessageBox::Ok);
        this->close();
    }
    else
    {
        QMessageBox::information(this, "结果", "修改失败",QMessageBox::Ok);
    }
    queryRoom(room,"",_order_by_rid,_ascend);
}
