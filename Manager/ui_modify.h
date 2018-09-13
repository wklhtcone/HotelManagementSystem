/********************************************************************************
** Form generated from reading UI file 'modify.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFY_H
#define UI_MODIFY_H

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

class Ui_modify
{
public:
    QTextEdit *newroomEdit;
    QPushButton *submitButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QRadioButton *singleButton;
    QRadioButton *bigButton_2;
    QRadioButton *doubleButton_3;
    QRadioButton *presButton_4;
    QLabel *label_4;

    void setupUi(QDialog *modify)
    {
        if (modify->objectName().isEmpty())
            modify->setObjectName(QStringLiteral("modify"));
        modify->resize(400, 300);
        newroomEdit = new QTextEdit(modify);
        newroomEdit->setObjectName(QStringLiteral("newroomEdit"));
        newroomEdit->setGeometry(QRect(100, 60, 91, 21));
        submitButton = new QPushButton(modify);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setGeometry(QRect(160, 230, 75, 23));
        label = new QLabel(modify);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 60, 61, 21));
        label_2 = new QLabel(modify);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(240, 20, 61, 21));
        label_3 = new QLabel(modify);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 120, 61, 21));
        singleButton = new QRadioButton(modify);
        singleButton->setObjectName(QStringLiteral("singleButton"));
        singleButton->setGeometry(QRect(230, 60, 89, 16));
        bigButton_2 = new QRadioButton(modify);
        bigButton_2->setObjectName(QStringLiteral("bigButton_2"));
        bigButton_2->setGeometry(QRect(230, 90, 89, 16));
        doubleButton_3 = new QRadioButton(modify);
        doubleButton_3->setObjectName(QStringLiteral("doubleButton_3"));
        doubleButton_3->setGeometry(QRect(230, 120, 89, 16));
        presButton_4 = new QRadioButton(modify);
        presButton_4->setObjectName(QStringLiteral("presButton_4"));
        presButton_4->setGeometry(QRect(230, 150, 89, 16));
        label_4 = new QLabel(modify);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(120, 120, 51, 21));

        retranslateUi(modify);

        QMetaObject::connectSlotsByName(modify);
    } // setupUi

    void retranslateUi(QDialog *modify)
    {
        modify->setWindowTitle(QApplication::translate("modify", "Dialog", Q_NULLPTR));
        submitButton->setText(QApplication::translate("modify", "\346\217\220\344\272\244", Q_NULLPTR));
        label->setText(QApplication::translate("modify", "\346\210\277\351\227\264\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("modify", "\346\210\277\351\227\264\347\261\273\345\236\213", Q_NULLPTR));
        label_3->setText(QApplication::translate("modify", "\346\210\277\351\227\264\344\273\267\346\240\274", Q_NULLPTR));
        singleButton->setText(QApplication::translate("modify", "\345\215\225\344\272\272\351\227\264", Q_NULLPTR));
        bigButton_2->setText(QApplication::translate("modify", "\345\244\247\345\272\212\346\210\277", Q_NULLPTR));
        doubleButton_3->setText(QApplication::translate("modify", "\345\217\214\344\272\272\351\227\264", Q_NULLPTR));
        presButton_4->setText(QApplication::translate("modify", "\346\200\273\347\273\237\345\245\227\346\210\277", Q_NULLPTR));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class modify: public Ui_modify {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFY_H
