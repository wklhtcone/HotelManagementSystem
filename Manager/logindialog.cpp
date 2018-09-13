#include "logindialog.h"
#include "ui_logindialog.h"
#include <head.h>
#include <QMessageBox>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    if(loginCheck(ui->usernameline->text(),ui->passwordline->text()))
        accept();
    else
    {
        QMessageBox::about(NULL, "", "用户名或密码错误");
        ui->usernameline->setText("");
        ui->passwordline->setText("");
    }
}

