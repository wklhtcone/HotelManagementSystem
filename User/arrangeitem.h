#ifndef ARRANGEITEM_H
#define ARRANGEITEM_H

#include <QWidget>
#include <string>
using namespace std;
namespace Ui {
class arrangeitem;
}

class arrangeitem : public QWidget
{
    Q_OBJECT

public:
    explicit arrangeitem(QWidget *parent = 0);
    ~arrangeitem();
    void setcontent(string roomnum, string roomtype, string starttime, string endtime, string f, string name, string pass);
    void connectclient();
private slots:
    void on_pushButton_clicked();
protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::arrangeitem *ui;
    string num;
    string start;
    string end;
    string username;
    string password;
    string flag;
    string room_type;
};

#endif // ARRANGEITEM_H
