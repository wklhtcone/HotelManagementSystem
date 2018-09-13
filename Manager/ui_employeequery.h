/********************************************************************************
** Form generated from reading UI file 'employeequery.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEQUERY_H
#define UI_EMPLOYEEQUERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_employeequery
{
public:
    QTextEdit *textEdit;
    QLabel *label;
    QRadioButton *upButton;
    QRadioButton *downButton_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QRadioButton *orderidButton;
    QRadioButton *ordertypeButton_2;

    void setupUi(QDialog *employeequery)
    {
        if (employeequery->objectName().isEmpty())
            employeequery->setObjectName(QStringLiteral("employeequery"));
        employeequery->resize(400, 300);
        textEdit = new QTextEdit(employeequery);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(120, 90, 101, 41));
        label = new QLabel(employeequery);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 100, 71, 21));
        upButton = new QRadioButton(employeequery);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(110, 180, 61, 16));
        downButton_2 = new QRadioButton(employeequery);
        downButton_2->setObjectName(QStringLiteral("downButton_2"));
        downButton_2->setGeometry(QRect(190, 180, 89, 16));
        pushButton = new QPushButton(employeequery);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 220, 75, 23));
        label_2 = new QLabel(employeequery);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(300, 30, 54, 12));
        orderidButton = new QRadioButton(employeequery);
        orderidButton->setObjectName(QStringLiteral("orderidButton"));
        orderidButton->setGeometry(QRect(290, 80, 89, 16));
        ordertypeButton_2 = new QRadioButton(employeequery);
        ordertypeButton_2->setObjectName(QStringLiteral("ordertypeButton_2"));
        ordertypeButton_2->setGeometry(QRect(290, 120, 89, 16));

        retranslateUi(employeequery);

        QMetaObject::connectSlotsByName(employeequery);
    } // setupUi

    void retranslateUi(QDialog *employeequery)
    {
        employeequery->setWindowTitle(QApplication::translate("employeequery", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("employeequery", "\345\205\263\351\224\256\345\255\227", Q_NULLPTR));
        upButton->setText(QApplication::translate("employeequery", "\345\215\207\345\272\217", Q_NULLPTR));
        downButton_2->setText(QApplication::translate("employeequery", "\351\231\215\345\272\217", Q_NULLPTR));
        pushButton->setText(QApplication::translate("employeequery", "\346\237\245\350\257\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("employeequery", "\346\216\222\345\272\217\346\226\271\345\274\217", Q_NULLPTR));
        orderidButton->setText(QApplication::translate("employeequery", "\345\221\230\345\267\245\345\217\267", Q_NULLPTR));
        ordertypeButton_2->setText(QApplication::translate("employeequery", "\345\221\230\345\267\245\347\261\273\345\236\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class employeequery: public Ui_employeequery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEQUERY_H
