#ifndef USERINFO_H
#define USERINFO_H
#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QString>
extern QString old_r_id;
namespace Ui {
class userinfo;
}

class userinfo : public QDialog
{
    Q_OBJECT

public:
    explicit userinfo(QWidget *parent = 0);
    ~userinfo();

private:
    Ui::userinfo *ui;
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_deleteButton_2_clicked();
    void on_addButton_clicked();
    void on_modifyButton_3_clicked();
    void on_queryButton_clicked();
    void on_rpriceButton_clicked();
};

#endif // LOGINDIALOG_H
