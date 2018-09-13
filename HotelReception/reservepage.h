#ifndef RESERVEPAGE_H
#define RESERVEPAGE_H

#include <QDialog>
#include <QDate>
#include<QPixmap>

namespace Ui {
class reservepage;
}

class reservepage : public QDialog
{
    Q_OBJECT

public:
    explicit reservepage(QWidget *parent = 0);
    ~reservepage();
    void settype(int t);
    void setmoney(int m);
    void setDate(QDate starttime,QDate endtime);
    void connectclient();
    void setflag(bool f);
signals:
    void send();
private slots:
    void on_pushButton_clicked();
    void on_actionMinimize_triggered();     //最小化窗口
    void on_actionClose_triggered();        //关闭窗口
    void on_actionMaximize_triggered();     //最大化窗口

protected:
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
private:
    Ui::reservepage *ui;
    int type;
    int money;
    QDate start;
    QDate end;
    QPoint mousePosition;
    bool isMousePressed;
    bool flag;
};

#endif // RESERVEPAGE_H
