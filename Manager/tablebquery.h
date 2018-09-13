#ifndef TABLEBQUERY_H
#define TABLEBQUERY_H

#include <QDialog>
#include <QTextCharFormat>
#include <QDate>

namespace Ui {
class tablebquery;
}

class tablebquery : public QDialog
{
    Q_OBJECT

public:
    explicit tablebquery(QWidget *parent = 0);
    ~tablebquery();

private slots:
    void on_pushButton_clicked();
    void selectdate();
private:
    Ui::tablebquery *ui;
    int tcount=0;
    QDate former;
    QDate later;
};

#endif // TABLEBQUERY_H
