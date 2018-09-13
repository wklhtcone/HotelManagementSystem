#include "employeeadd.h"
#include "ui_employeeadd.h"
#include <QDebug>
#include <QMessageBox>
#include <managerfunc.h>
#include "head.h"
employeeadd::employeeadd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employeeadd)
{
    ui->setupUi(this);
}

employeeadd::~employeeadd()
{
    delete ui;
}

void employeeadd::on_confirmButton_clicked()
{
        QString e_id;QString e_pwd;
        e_id=ui->eidEdit->toPlainText();
        e_pwd=ui->epwdEdit_2->toPlainText();
        QString e_type;
        if(ui->radioButton->isChecked()==1)
        {
            e_type="员工";
        }
        else if(ui->radioButton_2->isChecked()==1)
        {
            e_type="经理";
        }
        else
        {
            e_type="员工";
        }
        qDebug()<<e_id;
        qDebug()<<e_pwd;
        qDebug()<<e_type;
        if(addNewEmployee(e_id,e_type,e_pwd))
        {
            QMessageBox::information(this, "结果", "添加成功",QMessageBox::Ok);
            this->close();
        }
        else
        {
            QMessageBox::information(this, "结果", "添加失败",QMessageBox::Ok);
        }
        queryEmployee(employeelist,"",_order_by_eid,_ascend);
}
