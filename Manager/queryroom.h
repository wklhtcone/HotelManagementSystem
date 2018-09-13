#ifndef QUERYROOM_H
#define QUERYROOM_H

#include <QDialog>

namespace Ui {
class queryroom;
}

class queryroom : public QDialog
{
    Q_OBJECT

public:
    explicit queryroom(QWidget *parent = 0);
    ~queryroom();
   // void setRow(int n);

private slots:
    void on_checkButton_4_clicked();

private:
    Ui::queryroom *ui;
};

#endif // QUERYROOM_H
