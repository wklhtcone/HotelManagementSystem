#ifndef MODIFY_H
#define MODIFY_H

#include <QDialog>

namespace Ui {
class modify;
}

class modify : public QDialog
{
    Q_OBJECT

public:
    explicit modify(QWidget *parent = 0);
    ~modify();

private slots:
    void on_submitButton_clicked();

    void on_singleButton_clicked();

    void on_bigButton_2_clicked();

    void on_doubleButton_3_clicked();

    void on_presButton_4_clicked();

private:
    Ui::modify *ui;
};

#endif // MODIFY_H
