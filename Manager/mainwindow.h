#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVector>
#include <QMainWindow>
#include<QPixmap>
#include<QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_actionMinimize_triggered();     //最小化窗口
    void on_actionClose_triggered();        //关闭窗口
    void on_actionMaximize_triggered();     //最大化窗口

    void on_userinfoButton_clicked();
    void on_userlogButton_clicked();
    void on_employeeButton_clicked();

protected:
    //改写QWidget的函数，自己重新实现拖动操作
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;

    void login();

    void off();

    void change();
    QPushButton *userinfoButton;
    QPushButton *userlogButton;
    QPushButton *employeeButton;
    QPoint mousePosition;

    bool isMousePressed;
};

#endif // MAINWINDOW_H
