/********************************************************************************
** Form generated from reading UI file 'changeprice.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPRICE_H
#define UI_CHANGEPRICE_H

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

class Ui_changeprice
{
public:
    QRadioButton *srButton;
    QRadioButton *brButton_2;
    QRadioButton *drButton_3;
    QRadioButton *prButton_4;
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *changeprice)
    {
        if (changeprice->objectName().isEmpty())
            changeprice->setObjectName(QStringLiteral("changeprice"));
        changeprice->resize(400, 300);
        srButton = new QRadioButton(changeprice);
        srButton->setObjectName(QStringLiteral("srButton"));
        srButton->setGeometry(QRect(50, 60, 89, 16));
        brButton_2 = new QRadioButton(changeprice);
        brButton_2->setObjectName(QStringLiteral("brButton_2"));
        brButton_2->setGeometry(QRect(50, 90, 89, 16));
        drButton_3 = new QRadioButton(changeprice);
        drButton_3->setObjectName(QStringLiteral("drButton_3"));
        drButton_3->setGeometry(QRect(50, 120, 89, 16));
        prButton_4 = new QRadioButton(changeprice);
        prButton_4->setObjectName(QStringLiteral("prButton_4"));
        prButton_4->setGeometry(QRect(50, 150, 89, 16));
        label = new QLabel(changeprice);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 60, 54, 12));
        textEdit = new QTextEdit(changeprice);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(170, 80, 81, 31));
        pushButton = new QPushButton(changeprice);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 200, 75, 23));

        retranslateUi(changeprice);

        QMetaObject::connectSlotsByName(changeprice);
    } // setupUi

    void retranslateUi(QDialog *changeprice)
    {
        changeprice->setWindowTitle(QApplication::translate("changeprice", "Dialog", Q_NULLPTR));
        srButton->setText(QApplication::translate("changeprice", "\345\215\225\344\272\272\351\227\264", Q_NULLPTR));
        brButton_2->setText(QApplication::translate("changeprice", "\345\244\247\345\272\212\346\210\277", Q_NULLPTR));
        drButton_3->setText(QApplication::translate("changeprice", "\345\217\214\344\272\272\351\227\264", Q_NULLPTR));
        prButton_4->setText(QApplication::translate("changeprice", "\346\200\273\347\273\237\345\245\227\346\210\277", Q_NULLPTR));
        label->setText(QApplication::translate("changeprice", "\346\226\260\344\273\267\346\240\274", Q_NULLPTR));
        pushButton->setText(QApplication::translate("changeprice", "\346\217\220\344\272\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class changeprice: public Ui_changeprice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPRICE_H
