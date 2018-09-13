#ifndef SINGLEITEM_H
#define SINGLEITEM_H
#include <QPixmap>
#include <QWidget>
#include<QString>
#include <QDate>
namespace Ui {
class singleitem;
}

class singleitem : public QWidget
{
    Q_OBJECT

public:
    explicit singleitem(QWidget *parent = 0);
    void setcontent1(QDate start,QDate end);
    ~singleitem();
    QDate startdate;
    QDate enddate;

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::singleitem *ui;
};

#endif // SINGLEITEM_H
