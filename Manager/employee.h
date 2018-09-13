#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QDialog>
#include <QString>
extern QString old_e_id;
namespace Ui {
class employee;
}

class employee : public QDialog
{
    Q_OBJECT

public:
    explicit employee(QWidget *parent = 0);
    ~employee();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_eaddButton_clicked();

    void on_edelButton_2_clicked();

    void on_emodButton_3_clicked();

    void on_equeButton_4_clicked();

private:
    Ui::employee *ui;
};

#endif // EMPLOYEE_H
