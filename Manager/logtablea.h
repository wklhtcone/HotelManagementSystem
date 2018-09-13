#ifndef LOGTABLEA_H
#define LOGTABLEA_H

#include <QDialog>

namespace Ui {
class logtablea;
}

class logtablea : public QDialog
{
    Q_OBJECT

public:
    explicit logtablea(QWidget *parent = 0);
    ~logtablea();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_aqueButton_clicked();

private:
    Ui::logtablea *ui;
};

#endif // LOGTABLEA_H
