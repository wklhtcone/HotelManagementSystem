#ifndef TABLEAQUERY_H
#define TABLEAQUERY_H

#include <QDialog>
#include <QTextCharFormat>
#include <QDate>

namespace Ui {
class tableaquery;
}

class tableaquery : public QDialog
{
    Q_OBJECT

public:
    explicit tableaquery(QWidget *parent = 0);
    ~tableaquery();

private slots:
    void on_pushButton_clicked();
    void selectdate();
private:
    Ui::tableaquery *ui;
    int tcount=0;
    QDate former;
    QDate later;
};

#endif // TABLEAQUERY_H
