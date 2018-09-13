#ifndef EMPLOYEEMODIFY_H
#define EMPLOYEEMODIFY_H
#include <QRadioButton>
#include <QDialog>

namespace Ui {
class employeemodify;
}

class employeemodify : public QDialog
{
    Q_OBJECT

public:
    explicit employeemodify(QWidget *parent = 0);
    ~employeemodify();

private slots:
    void on_submitButton_clicked();
private:
    Ui::employeemodify *ui;
};

#endif // EMPLOYEEMODIFY_H
