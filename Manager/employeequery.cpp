#include "employeequery.h"
#include "ui_employeequery.h"
#include "managerfunc.h"
#include <QMessageBox>
#include "head.h"
employeequery::employeequery(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employeequery)
{
    ui->setupUi(this);
    QButtonGroup *operatingModeGroup = new QButtonGroup(this);
    operatingModeGroup->addButton(ui->upButton);
    operatingModeGroup->addButton(ui->downButton_2);
    QButtonGroup *operatingModeGroup1 = new QButtonGroup(this);
    operatingModeGroup1->addButton(ui->orderidButton);
    operatingModeGroup1->addButton(ui->ordertypeButton_2);
}

employeequery::~employeequery()
{
    delete ui;
}

void employeequery::on_pushButton_clicked()
{
    QString keyworde;
    keyworde=ui->textEdit->toPlainText();
    QueryKeyCode updown1;
    QueryKeyCode orderby1;
    if(ui->upButton->isChecked()==1)
    {
        updown1=_ascend;
    }
    if(ui->downButton_2->isChecked()==1)
    {
        updown1=_descend;
    }
    if(ui->orderidButton->isChecked()==1)
    {
        orderby1=_order_by_eid;
    }
    if(ui->ordertypeButton_2->isChecked()==1)
    {
        orderby1=_order_by_etype;
    }
    if(queryEmployee(employeelist,keyworde,orderby1,updown1))
    {
        QMessageBox::information(this, "结果", "查询成功",QMessageBox::Ok);
        this->close();
    }
    else
    {
        QMessageBox::information(this, "结果", "查询失败",QMessageBox::Ok);
    }
    queryEmployee(employeelist,keyworde,orderby1,updown1);
}
