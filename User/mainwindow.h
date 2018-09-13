#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <singleitem.h>
#include <arrangethread.h>
#include <chooseroom.h>
#include <QDate>
#include <QListWidgetItem>
#include<QPixmap>
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

private slots:
    void on_reserveButton_clicked();

    void on_arrangeButton_clicked();

    void on_extendButton_clicked();

    void on_loginButton_clicked();

    void on_checkButton_clicked();

    void doubleclicked1();

    void selectdate();

    void on_okButton_clicked();

    void on_switchButton_clicked();

    void on_makeextendButton_clicked();

    void on_actionMinimize_triggered();     //最小化窗口
    void on_actionClose_triggered();        //关闭窗口
    void on_actionMaximize_triggered();     //最大化窗口

protected:
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *);

public slots:

    void refreshHistory(QString S);

private:
    Ui::MainWindow *ui;
    arrangeThread *a_thread;
    int count;
    singleitem* si;
    QDate former;
    QDate later;
    ChooseRoom cr;
    bool islogged;
    string username;
    string password;
    QPoint mousePosition;
    bool isMousePressed;
};

#endif // MAINWINDOW_H
