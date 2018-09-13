#include "logindialog.h"
#include "ui_logindialog.h"
#include <head.h>
#include <QMessageBox>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("IHOTEL");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    int tcount;
    clientConnector.startClient();

    string username=ui->usernameline->text().toStdString();
    string password=ui->passwordline->text().toStdString();

    //发包
    DataStruct message;
    message.kind=_register;
    message.name=username;
    message.customer_id=password;
    if(clientConnector.sendMessage(message))
    {
        QMessageBox::about(NULL, "", "请等待服务器响应");
    }
    else
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        connectclient();
        return;
    }
    //收包
    tcount=0;
    DataStruct data;
    while(!clientConnector.getMessage(data)||data.kind!=_register)
    {
        tcount++;
        Sleep(1000);
        if(tcount>5)break;
    }

    if(tcount>5)
    {
        QMessageBox::about(NULL, "", "网络连接失败");
        return;
    }

    if(data.isSucceed)
        accept();
    else
    {
        QMessageBox::about(NULL, "", "用户名或密码错误");
        ui->usernameline->setText("");
        ui->passwordline->setText("");
    }

}
void LoginDialog::connectclient()
{

    while(!clientConnector.startClient())
    {
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提示", "网络连接失败，请重试", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::No)
        {
            break;
        }
    }
}
