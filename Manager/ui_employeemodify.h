/********************************************************************************
** Form generated from reading UI file 'employeemodify.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEMODIFY_H
#define UI_EMPLOYEEMODIFY_H

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

class Ui_employeemodify
{
public:
    QTextEdit *nidEdit;
    QTextEdit *npwdEdit_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *submitButton;
    QRadioButton *epButton;
    QRadioButton *mgButton_2;

    void setupUi(QDialog *employeemodify)
    {
        if (employeemodify->objectName().isEmpty())
            employeemodify->setObjectName(QStringLiteral("employeemodify"));
        employeemodify->resize(400, 300);
        nidEdit = new QTextEdit(employeemodify);
        nidEdit->setObjectName(QStringLiteral("nidEdit"));
        nidEdit->setGeometry(QRect(100, 50, 101, 31));
        npwdEdit_3 = new QTextEdit(employeemodify);
        npwdEdit_3->setObjectName(QStringLiteral("npwdEdit_3"));
        npwdEdit_3->setGeometry(QRect(100, 170, 101, 31));
        label = new QLabel(employeemodify);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 60, 41, 16));
        label_2 = new QLabel(employeemodify);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 120, 31, 16));
        label_3 = new QLabel(employeemodify);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 180, 31, 16));
        submitButton = new QPushButton(employeemodify);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setGeometry(QRect(160, 230, 75, 23));
        epButton = new QRadioButton(employeemodify);
        epButton->setObjectName(QStringLiteral("epButton"));
        epButton->setGeometry(QRect(100, 120, 51, 16));
        mgButton_2 = new QRadioButton(employeemodify);
        mgButton_2->setObjectName(QStringLiteral("mgButton_2"));
        mgButton_2->setGeometry(QRect(170, 120, 51, 16));

        retranslateUi(employeemodify);

        QMetaObject::connectSlotsByName(employeemodify);
    } // setupUi

    void retranslateUi(QDialog *employeemodify)
    {
        employeemodify->setWindowTitle(QApplication::translate("employeemodify", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("employeemodify", "\345\221\230\345\267\245\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("employeemodify", "\347\261\273\345\236\213", Q_NULLPTR));
        label_3->setText(QApplication::translate("employeemodify", "\345\257\206\347\240\201", Q_NULLPTR));
        submitButton->setText(QApplication::translate("employeemodify", "\346\217\220\344\272\244", Q_NULLPTR));
        epButton->setText(QApplication::translate("employeemodify", "\345\221\230\345\267\245", Q_NULLPTR));
        mgButton_2->setText(QApplication::translate("employeemodify", "\347\273\217\347\220\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class employeemodify: public Ui_employeemodify {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEMODIFY_H
