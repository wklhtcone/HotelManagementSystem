#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <logindialog.h>
//#include <QString>
using namespace std;
#include <head.h>
SQL_ODBC sql;
vector<vector<string>>room;
vector<vector<string>>employeelist;
vector<vector<string>>res_log;
vector<vector<string>>check_log;
float single_room_price;
float big_room_price;
float double_room_price;
float pres_room_price;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    sql.initSQL("Hotel","127.0.0.1,1433","");

    LoginDialog x;

    if (x.exec() == QDialog::Accepted)
    {
       w.show();
       return a.exec();
    }
    else return 0;

}
