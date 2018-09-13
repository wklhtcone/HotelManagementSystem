/********************************************************************************
** Form generated from reading UI file 'employeeadd.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEADD_H
#define UI_EMPLOYEEADD_H

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

class Ui_employeeadd
{
public:
    QTextEdit *eidEdit;
    QTextEdit *epwdEdit_2;
    QLabel *label;
    QLabel *label_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *confirmButton;

    void setupUi(QDialog *employeeadd)
    {
        if (employeeadd->objectName().isEmpty())
            employeeadd->setObjectName(QStringLiteral("employeeadd"));
        employeeadd->resize(409, 320);
        eidEdit = new QTextEdit(employeeadd);
        eidEdit->setObjectName(QStringLiteral("eidEdit"));
        eidEdit->setGeometry(QRect(100, 100, 101, 31));
        epwdEdit_2 = new QTextEdit(employeeadd);
        epwdEdit_2->setObjectName(QStringLiteral("epwdEdit_2"));
        epwdEdit_2->setGeometry(QRect(100, 160, 101, 31));
        label = new QLabel(employeeadd);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 110, 54, 12));
        label_2 = new QLabel(employeeadd);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 170, 54, 12));
        radioButton = new QRadioButton(employeeadd);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(170, 220, 89, 16));
        radioButton_2 = new QRadioButton(employeeadd);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(40, 220, 89, 16));
        confirmButton = new QPushButton(employeeadd);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(170, 260, 75, 23));

        retranslateUi(employeeadd);

        QMetaObject::connectSlotsByName(employeeadd);
    } // setupUi

    void retranslateUi(QDialog *employeeadd)
    {
        employeeadd->setWindowTitle(QApplication::translate("employeeadd", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("employeeadd", "\345\221\230\345\267\245\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("employeeadd", "\345\257\206\347\240\201", Q_NULLPTR));
        radioButton->setText(QApplication::translate("employeeadd", "\345\221\230\345\267\245", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("employeeadd", "\347\273\217\347\220\206", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("employeeadd", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class employeeadd: public Ui_employeeadd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEADD_H
