#ifndef CHOOSEROOM_H
#define CHOOSEROOM_H

#include <QDialog>
#include <QDate>
#include <singleitem.h>
#include <choosethread.h>
#include <roomtype.h>
#include<QPixmap>
namespace Ui {
class ChooseRoom;
}

class ChooseRoom : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseRoom(QWidget *parent = 0);
    ~ChooseRoom();    
    chooseThread *c_Thread;
    void daterange(QDate come,QDate leave);
    void setflag(bool flag);

public slots:
    void refreshNum(int count);
    void openthread();
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
    Ui::ChooseRoom *ui;
    QDate start;
    QDate end;
    int singleR;
    int standardR;
    int bedR;
    int LuxuryR;
    singleitem si;
    roomtype rt;
    roomtype stdr;
    roomtype br;
    roomtype lr;
    QPoint mousePosition;
    bool isMousePressed;
    bool type;
};

#endif // CHOOSEROOM_H
