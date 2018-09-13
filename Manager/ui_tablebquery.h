/********************************************************************************
** Form generated from reading UI file 'tablebquery.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEBQUERY_H
#define UI_TABLEBQUERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_tablebquery
{
public:
    QTextEdit *textEdit;
    QLabel *label;
    QRadioButton *upButton;
    QRadioButton *downButton_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QRadioButton *ridButton_3;
    QRadioButton *cidButton_4;
    QRadioButton *cnameButton_5;
    QRadioButton *startTButton_6;
    QRadioButton *endTButton_7;
    QCalendarWidget *calendarWidget;

    void setupUi(QDialog *tablebquery)
    {
        if (tablebquery->objectName().isEmpty())
            tablebquery->setObjectName(QStringLiteral("tablebquery"));
        tablebquery->resize(707, 300);
        textEdit = new QTextEdit(tablebquery);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(110, 90, 81, 31));
        label = new QLabel(tablebquery);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 100, 61, 16));
        upButton = new QRadioButton(tablebquery);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(90, 160, 61, 16));
        downButton_2 = new QRadioButton(tablebquery);
        downButton_2->setObjectName(QStringLiteral("downButton_2"));
        downButton_2->setGeometry(QRect(150, 160, 89, 16));
        pushButton = new QPushButton(tablebquery);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 220, 75, 23));
        label_2 = new QLabel(tablebquery);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 20, 54, 12));
        ridButton_3 = new QRadioButton(tablebquery);
        ridButton_3->setObjectName(QStringLiteral("ridButton_3"));
        ridButton_3->setGeometry(QRect(260, 50, 89, 16));
        cidButton_4 = new QRadioButton(tablebquery);
        cidButton_4->setObjectName(QStringLiteral("cidButton_4"));
        cidButton_4->setGeometry(QRect(260, 80, 89, 16));
        cnameButton_5 = new QRadioButton(tablebquery);
        cnameButton_5->setObjectName(QStringLiteral("cnameButton_5"));
        cnameButton_5->setGeometry(QRect(260, 110, 89, 16));
        startTButton_6 = new QRadioButton(tablebquery);
        startTButton_6->setObjectName(QStringLiteral("startTButton_6"));
        startTButton_6->setGeometry(QRect(260, 140, 89, 16));
        endTButton_7 = new QRadioButton(tablebquery);
        endTButton_7->setObjectName(QStringLiteral("endTButton_7"));
        endTButton_7->setGeometry(QRect(260, 170, 89, 16));
        calendarWidget = new QCalendarWidget(tablebquery);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(380, 20, 296, 236));
        calendarWidget->setFirstDayOfWeek(Qt::Sunday);
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        calendarWidget->setNavigationBarVisible(true);

        retranslateUi(tablebquery);

        QMetaObject::connectSlotsByName(tablebquery);
    } // setupUi

    void retranslateUi(QDialog *tablebquery)
    {
        tablebquery->setWindowTitle(QApplication::translate("tablebquery", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("tablebquery", "\345\205\263\351\224\256\345\255\227", Q_NULLPTR));
        upButton->setText(QApplication::translate("tablebquery", "\345\215\207\345\272\217", Q_NULLPTR));
        downButton_2->setText(QApplication::translate("tablebquery", "\351\231\215\345\272\217", Q_NULLPTR));
        pushButton->setText(QApplication::translate("tablebquery", "\346\237\245\350\257\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("tablebquery", "\346\216\222\345\272\217\346\226\271\345\274\217", Q_NULLPTR));
        ridButton_3->setText(QApplication::translate("tablebquery", "\346\210\277\351\227\264\345\217\267", Q_NULLPTR));
        cidButton_4->setText(QApplication::translate("tablebquery", "\351\241\276\345\256\242id", Q_NULLPTR));
        cnameButton_5->setText(QApplication::translate("tablebquery", "\351\241\276\345\256\242\345\220\215", Q_NULLPTR));
        startTButton_6->setText(QApplication::translate("tablebquery", "\345\274\200\345\247\213\346\227\266\351\227\264", Q_NULLPTR));
        endTButton_7->setText(QApplication::translate("tablebquery", "\347\273\223\346\235\237\346\227\266\351\227\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class tablebquery: public Ui_tablebquery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEBQUERY_H
