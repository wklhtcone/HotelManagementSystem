#ifndef LOGTABLEB_H
#define LOGTABLEB_H

#include <QDialog>

namespace Ui {
class logtableb;
}

class logtableb : public QDialog
{
    Q_OBJECT

public:
    explicit logtableb(QWidget *parent = 0);
    ~logtableb();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_bqueButton_clicked();

private:
    Ui::logtableb *ui;
};

#endif // LOGTABLEB_H
