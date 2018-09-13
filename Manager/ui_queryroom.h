/********************************************************************************
** Form generated from reading UI file 'queryroom.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYROOM_H
#define UI_QUERYROOM_H

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

class Ui_queryroom
{
public:
    QTextEdit *textEdit;
    QLabel *label;
    QPushButton *checkButton_4;
    QRadioButton *upButton;
    QRadioButton *downButton_2;
    QLabel *label_2;
    QRadioButton *orderidButton_3;
    QRadioButton *ordertypeButton_4;
    QRadioButton *orderpriceButton_5;

    void setupUi(QDialog *queryroom)
    {
        if (queryroom->objectName().isEmpty())
            queryroom->setObjectName(QStringLiteral("queryroom"));
        queryroom->resize(426, 366);
        textEdit = new QTextEdit(queryroom);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(100, 130, 121, 41));
        label = new QLabel(queryroom);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 140, 51, 21));
        checkButton_4 = new QPushButton(queryroom);
        checkButton_4->setObjectName(QStringLiteral("checkButton_4"));
        checkButton_4->setGeometry(QRect(170, 260, 75, 23));
        upButton = new QRadioButton(queryroom);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(100, 190, 51, 16));
        downButton_2 = new QRadioButton(queryroom);
        downButton_2->setObjectName(QStringLiteral("downButton_2"));
        downButton_2->setGeometry(QRect(170, 190, 51, 16));
        label_2 = new QLabel(queryroom);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(310, 80, 54, 12));
        orderidButton_3 = new QRadioButton(queryroom);
        orderidButton_3->setObjectName(QStringLiteral("orderidButton_3"));
        orderidButton_3->setGeometry(QRect(310, 110, 89, 16));
        ordertypeButton_4 = new QRadioButton(queryroom);
        ordertypeButton_4->setObjectName(QStringLiteral("ordertypeButton_4"));
        ordertypeButton_4->setGeometry(QRect(310, 140, 89, 16));
        orderpriceButton_5 = new QRadioButton(queryroom);
        orderpriceButton_5->setObjectName(QStringLiteral("orderpriceButton_5"));
        orderpriceButton_5->setGeometry(QRect(310, 170, 89, 16));

        retranslateUi(queryroom);

        QMetaObject::connectSlotsByName(queryroom);
    } // setupUi

    void retranslateUi(QDialog *queryroom)
    {
        queryroom->setWindowTitle(QApplication::translate("queryroom", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("queryroom", "\345\205\263\351\224\256\345\255\227", Q_NULLPTR));
        checkButton_4->setText(QApplication::translate("queryroom", "\346\237\245\350\257\242", Q_NULLPTR));
        upButton->setText(QApplication::translate("queryroom", "\345\215\207\345\272\217", Q_NULLPTR));
        downButton_2->setText(QApplication::translate("queryroom", "\351\231\215\345\272\217", Q_NULLPTR));
        label_2->setText(QApplication::translate("queryroom", "\346\216\222\345\272\217\346\226\271\345\274\217", Q_NULLPTR));
        orderidButton_3->setText(QApplication::translate("queryroom", "\346\210\277\351\227\264\345\217\267", Q_NULLPTR));
        ordertypeButton_4->setText(QApplication::translate("queryroom", "\346\210\277\351\227\264\347\261\273\345\236\213", Q_NULLPTR));
        orderpriceButton_5->setText(QApplication::translate("queryroom", "\346\210\277\351\227\264\344\273\267\346\240\274", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class queryroom: public Ui_queryroom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYROOM_H
