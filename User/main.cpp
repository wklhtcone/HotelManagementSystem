#include "mainwindow.h"
#include <QApplication>
#include <QDate>
#include <vector>
#include "ClientConnector.h"
using namespace std;

vector<vector<string>> history;
int roomNums[4];
int roomPrices[4];
ClientConnector clientConnector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;    
    w.show();
    w.connectclient();
    return a.exec();

}
