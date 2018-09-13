#ifndef ADD_H
#define ADD_H
#include <QPushButton>
#include <QRadioButton>
#include <QDialog>
#include <QTextEdit>
#include <QButtonGroup>
namespace Ui {
class add;
}

class add : public QDialog
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = 0);
    ~add();

private slots:
    void on_pushButton_clicked();

    void on_singleButton_clicked();

    void on_bigButton_clicked();

    void on_doubleButton_clicked();

    void on_presButton_clicked();

private:
    Ui::add *ui;
    QPushButton *pushButton;
    QTextEdit *roomEdit;
    QRadioButton *singleButton;
    QRadioButton *bigButton;
    QRadioButton *doubleButton;
    QRadioButton *presButton;
};

#endif // ADD_H
