#include "modify.h"
#include "ui_modify.h"
#include <QMessageBox>
#include <QDebug>
#include "userinfo.h"
#include "managerfunc.h"
#include "head.h"
modify::modify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify)
{
    ui->setupUi(this);
}

modify::~modify()
{
    delete ui;
}

void modify::on_submitButton_clicked()
{
    QString n_id;
    n_id=ui->newroomEdit->toPlainText();
    QString n_type;
    float newprice;

    if(ui->singleButton->isChecked()==1)
    {
        n_type="单人间";
        newprice=single_room_price;
    }
    else if(ui->bigButton_2->isChecked()==1)
    {
        n_type="大床房";
        newprice=big_room_price;
    }
    else if(ui->doubleButton_3->isChecked()==1)
    {
        n_type="双人间";
        newprice=double_room_price;
    }
    else if(ui->presButton_4->isChecked()==1)
    {
        n_type="总统套房";
        newprice=pres_room_price;
    }
    else
    {
        n_type="单人间";
        newprice=single_room_price;
    }
    qDebug()<<n_id;
    qDebug()<<n_type;
    qDebug()<<newprice;
    if(alterRoom(old_r_id,n_id,n_type,newprice))
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

void modify::on_singleButton_clicked()
{
    if(ui->singleButton->isChecked()==1)
    {
        QString newdata1 = QString("%1").arg(single_room_price);
        ui->label_4->setText(newdata1);
    }
}

void modify::on_bigButton_2_clicked()
{
    if(ui->bigButton_2->isChecked()==1)
    {
        QString newdata2 = QString("%1").arg(big_room_price);
        ui->label_4->setText(newdata2);
    }
}

void modify::on_doubleButton_3_clicked()
{
    if(ui->doubleButton_3->isChecked()==1)
    {
        QString newdata3 = QString("%1").arg(double_room_price);
        ui->label_4->setText(newdata3);
    }
}

void modify::on_presButton_4_clicked()
{
    if(ui->presButton_4->isChecked()==1)
    {
        QString newdata4 = QString("%1").arg(pres_room_price);
        ui->label_4->setText(newdata4);
    }

}
