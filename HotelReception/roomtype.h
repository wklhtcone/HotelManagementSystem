#ifndef ROOMTYPE_H
#define ROOMTYPE_H

#include <QWidget>
#include <QDate>
#include <reservepage.h>
namespace Ui {
class roomtype;
}

class roomtype : public QWidget
{
    Q_OBJECT

public:
    explicit roomtype(QWidget *parent = 0);
    ~roomtype();
    void setType(int t);
    void setDate(QDate starttime,QDate endtime);
    void setNum(int n);
    void connectclient();
    void setflag(bool f);
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_pushButton_clicked();
signals:
    void send();
    void open();
public slots:
    void openthread();
private:
    Ui::roomtype *ui;
    reservepage *rp;
    QDate start;
    QDate end;
    int type;
    int num;
    bool flag;
};

#endif // ROOMTYPE_H
