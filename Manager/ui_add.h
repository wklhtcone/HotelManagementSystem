/********************************************************************************
** Form generated from reading UI file 'add.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_H
#define UI_ADD_H

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

class Ui_add
{
public:
    QRadioButton *doubleButton;
    QRadioButton *presButton;
    QRadioButton *bigButton;
    QRadioButton *singleButton;
    QTextEdit *roomEdit;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *add)
    {
        if (add->objectName().isEmpty())
            add->setObjectName(QStringLiteral("add"));
        add->resize(483, 381);
        doubleButton = new QRadioButton(add);
        doubleButton->setObjectName(QStringLiteral("doubleButton"));
        doubleButton->setGeometry(QRect(290, 200, 91, 21));
        presButton = new QRadioButton(add);
        presButton->setObjectName(QStringLiteral("presButton"));
        presButton->setGeometry(QRect(290, 230, 101, 21));
        bigButton = new QRadioButton(add);
        bigButton->setObjectName(QStringLiteral("bigButton"));
        bigButton->setGeometry(QRect(290, 170, 91, 21));
        singleButton = new QRadioButton(add);
        singleButton->setObjectName(QStringLiteral("singleButton"));
        singleButton->setGeometry(QRect(290, 140, 91, 21));
        roomEdit = new QTextEdit(add);
        roomEdit->setObjectName(QStringLiteral("roomEdit"));
        roomEdit->setGeometry(QRect(150, 160, 81, 31));
        label = new QLabel(add);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 71, 31));
        label_2 = new QLabel(add);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 160, 61, 31));
        pushButton = new QPushButton(add);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(200, 290, 75, 23));
        label_3 = new QLabel(add);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 210, 71, 21));
        label_4 = new QLabel(add);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 212, 54, 20));

        retranslateUi(add);

        QMetaObject::connectSlotsByName(add);
    } // setupUi

    void retranslateUi(QDialog *add)
    {
        add->setWindowTitle(QApplication::translate("add", "Dialog", Q_NULLPTR));
        doubleButton->setText(QApplication::translate("add", "\345\217\214\344\272\272\351\227\264", Q_NULLPTR));
        presButton->setText(QApplication::translate("add", "\346\200\273\347\273\237\345\245\227\346\210\277", Q_NULLPTR));
        bigButton->setText(QApplication::translate("add", "\345\244\247\345\272\212\346\210\277", Q_NULLPTR));
        singleButton->setText(QApplication::translate("add", "\345\215\225\344\272\272\351\227\264", Q_NULLPTR));
        label->setText(QApplication::translate("add", "\346\267\273\345\212\240\346\210\277\351\227\264", Q_NULLPTR));
        label_2->setText(QApplication::translate("add", "room_id", Q_NULLPTR));
        pushButton->setText(QApplication::translate("add", "\347\241\256\350\256\244", Q_NULLPTR));
        label_3->setText(QApplication::translate("add", "unit_price", Q_NULLPTR));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class add: public Ui_add {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_H
