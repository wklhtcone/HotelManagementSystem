#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <singleitem.h>
#include <chooseroom.h>
#include <QDate>
#include <QListWidgetItem>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectclient();

protected:
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *);

private slots:
    void doubleclicked1();

    void doubleclicked2();

    void selectdate();

    void selectdate_2();

    void on_loginButton_clicked();

    void on_reserveButton_clicked();

    void on_extendButton_clicked();

    void on_searchButton_clicked();

    void on_login_searchButton_clicked();

    void on_singlefinalButton_clicked();

    void on_doublefinalButton_clicked();

    void on_pushButton_clicked();

    void on_makeextendButton_clicked();

    void on_setdateButton_clicked();

    void on_selectenddateButton_clicked();

    void on_checkoutButton_clicked();

    void on_checkoutButton_2_clicked();

    void on_actionMinimize_triggered();     //最小化窗口
    void on_actionClose_triggered();        //关闭窗口
    void on_actionMaximize_triggered();     //最大化窗口

private:
    Ui::MainWindow *ui;
    int count;
    singleitem* si;
    QDate former;
    QDate later;
    QDate endd;
    ChooseRoom cr;
    string roomtypetemp;
    string starttimetemp;
    string endtimetemp;
    string roomid;
    vector<vector<string>> roomlist;
    QPoint mousePosition;
    bool isMousePressed;
};

#endif // MAINWINDOW_H
