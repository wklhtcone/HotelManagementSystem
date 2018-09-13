#include "queryroom.h"
#include "ui_queryroom.h"
#include <QTableWidget>
#include <managerfunc.h>
#include <QMessageBox>
#include "head.h"
#include <QButtonGroup>
queryroom::queryroom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryroom)
{
    ui->setupUi(this);
    QButtonGroup *operatingModeGroup = new QButtonGroup(this);
    operatingModeGroup->addButton(ui->upButton);
    operatingModeGroup->addButton(ui->downButton_2);
    QButtonGroup *operatingModeGroup1 = new QButtonGroup(this);
    operatingModeGroup1->addButton(ui->orderidButton_3);
    operatingModeGroup1->addButton(ui->ordertypeButton_4);
    operatingModeGroup1->addButton(ui->orderpriceButton_5);
}

queryroom::~queryroom()
{
    delete ui;
}

void queryroom::on_checkButton_4_clicked()
{
    QString keyword;
    keyword=ui->textEdit->toPlainText();
    QueryKeyCode updown;
    QueryKeyCode orderby;
    if(ui->upButton->isChecked()==1)
    {
        updown=_ascend;
    }
    if(ui->downButton_2->isChecked()==1)
    {
        updown=_descend;
    }
    if(ui->orderidButton_3->isChecked()==1)
    {
        orderby=_order_by_rid;
    }
    if(ui->ordertypeButton_4->isChecked()==1)
    {
        orderby=_order_by_rtype;
    }
    if(ui->orderpriceButton_5->isChecked()==1)
    {
        orderby=_order_by_rprice;
    }
    if(queryRoom(room,keyword,orderby,updown))
    {
        QMessageBox::information(this, "结果", "查询成功",QMessageBox::Ok);
        this->close();
    }
    else
    {
        QMessageBox::information(this, "结果", "查询失败",QMessageBox::Ok);
    }
    queryRoom(room,keyword,orderby,updown);
}
