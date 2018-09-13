#include "mainwindow.h"
#include <QApplication>
#include <head.h>
#include <logindialog.h>
#include <QDebug>

int roomNums[4];
int roomPrices[4];
ClientConnector clientConnector;
vector<vector<string>> roomResult;
vector<vector<string>> roomInfo;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog x;
    if (x.exec() == QDialog::Accepted)
    {
       w.show();
       return a.exec();
    }
    else return 0;
}
