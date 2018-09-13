#ifndef EMPLOYEEQUERY_H
#define EMPLOYEEQUERY_H

#include <QDialog>

namespace Ui {
class employeequery;
}

class employeequery : public QDialog
{
    Q_OBJECT

public:
    explicit employeequery(QWidget *parent = 0);
    ~employeequery();

private slots:
    void on_pushButton_clicked();

private:
    Ui::employeequery *ui;
};

#endif // EMPLOYEEQUERY_H
