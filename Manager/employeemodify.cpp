#include "employeemodify.h"
#include "ui_employeemodify.h"
#include <QDebug>
#include <QMessageBox>
#include "managerfunc.h"
#include "employee.h"
#include <QRadioButton>
employeemodify::employeemodify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::employeemodify)
{
    ui->setupUi(this);
}

employeemodify::~employeemodify()
{
    delete ui;
}

void employeemodify::on_submitButton_clicked()
{
    QString en_id;
    en_id=ui->nidEdit->toPlainText();
    QString en_type;
    QString en_pwd;
    en_pwd=ui->npwdEdit_3->toPlainText();
    qDebug()<<en_id;
    qDebug()<<en_type;
    qDebug()<<en_pwd;
    if(ui->epButton->isChecked()==1)
    {
        en_type="员工";
    }
    else if(ui->epButton->isChecked()==1)
    {
        en_type="经理";
    }
    else
    {
        en_type="员工";
    }
    if(alterEmployee(old_e_id,en_id,en_type,en_pwd))
    {
        QMessageBox::information(this, "结果", "修改成功",QMessageBox::Ok);
        this->close();
    }
    else
    {
        QMessageBox::information(this, "结果", "修改失败",QMessageBox::Ok);
    }
}
