#ifndef USERLOG_H
#define USERLOG_H

#include <QDialog>
#include <QPushButton>
namespace Ui {
class userlog;
}

class userlog : public QDialog
{
    Q_OBJECT

public:
    explicit userlog(QWidget *parent = 0);
    ~userlog();

private slots:

    void on_logaButton_clicked();

    void on_logbButton_clicked();

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::userlog *ui;
    QPushButton *logaButton;
    QPushButton *logbButton;

};

#endif // CHANGEDIALOG_H
