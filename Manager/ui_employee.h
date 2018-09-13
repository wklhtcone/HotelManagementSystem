/********************************************************************************
** Form generated from reading UI file 'employee.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEE_H
#define UI_EMPLOYEE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_employee
{
public:
    QLabel *label;
    QTableWidget *tableWidget;
    QPushButton *eaddButton;
    QPushButton *edelButton_2;
    QPushButton *emodButton_3;
    QPushButton *equeButton_4;

    void setupUi(QDialog *employee)
    {
        if (employee->objectName().isEmpty())
            employee->setObjectName(QStringLiteral("employee"));
        employee->resize(632, 456);
        label = new QLabel(employee);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 91, 51));
        tableWidget = new QTableWidget(employee);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(70, 80, 371, 192));
        eaddButton = new QPushButton(employee);
        eaddButton->setObjectName(QStringLiteral("eaddButton"));
        eaddButton->setGeometry(QRect(70, 300, 75, 23));
        edelButton_2 = new QPushButton(employee);
        edelButton_2->setObjectName(QStringLiteral("edelButton_2"));
        edelButton_2->setGeometry(QRect(170, 300, 75, 23));
        emodButton_3 = new QPushButton(employee);
        emodButton_3->setObjectName(QStringLiteral("emodButton_3"));
        emodButton_3->setGeometry(QRect(270, 300, 75, 23));
        equeButton_4 = new QPushButton(employee);
        equeButton_4->setObjectName(QStringLiteral("equeButton_4"));
        equeButton_4->setGeometry(QRect(370, 300, 75, 23));

        retranslateUi(employee);

        QMetaObject::connectSlotsByName(employee);
    } // setupUi

    void retranslateUi(QDialog *employee)
    {
        employee->setWindowTitle(QApplication::translate("employee", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("employee", "\345\221\230\345\267\245\344\277\241\346\201\257", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("employee", "employee_id", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("employee", "employee_type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("employee", "password", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("employee", "\346\226\260\345\273\272\350\241\214", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        eaddButton->setText(QApplication::translate("employee", "\345\242\236\345\212\240", Q_NULLPTR));
        edelButton_2->setText(QApplication::translate("employee", "\345\210\240\351\231\244", Q_NULLPTR));
        emodButton_3->setText(QApplication::translate("employee", "\344\277\256\346\224\271", Q_NULLPTR));
        equeButton_4->setText(QApplication::translate("employee", "\346\237\245\350\257\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class employee: public Ui_employee {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEE_H
