#ifndef EMPLOYEEADD_H
#define EMPLOYEEADD_H

#include <QDialog>

namespace Ui {
class employeeadd;
}

class employeeadd : public QDialog
{
    Q_OBJECT

public:
    explicit employeeadd(QWidget *parent = 0);
    ~employeeadd();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::employeeadd *ui;
};

#endif // EMPLOYEEADD_H
