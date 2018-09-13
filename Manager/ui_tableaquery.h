/********************************************************************************
** Form generated from reading UI file 'tableaquery.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEAQUERY_H
#define UI_TABLEAQUERY_H

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

class Ui_tableaquery
{
public:
    QTextEdit *textEdit;
    QLabel *label;
    QRadioButton *upButton;
    QRadioButton *downButton_2;
    QPushButton *pushButton;
    QLabel *label_2;
    QRadioButton *ridButton;
    QRadioButton *cidButton_2;
    QRadioButton *cnameButton_3;
    QRadioButton *startTButton_4;
    QRadioButton *endTButton_5;
    QRadioButton *nowTButton_6;
    QCalendarWidget *calendarWidget;

    void setupUi(QDialog *tableaquery)
    {
        if (tableaquery->objectName().isEmpty())
            tableaquery->setObjectName(QStringLiteral("tableaquery"));
        tableaquery->resize(716, 300);
        textEdit = new QTextEdit(tableaquery);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(120, 90, 91, 41));
        label = new QLabel(tableaquery);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 100, 51, 21));
        upButton = new QRadioButton(tableaquery);
        upButton->setObjectName(QStringLiteral("upButton"));
        upButton->setGeometry(QRect(120, 170, 51, 16));
        downButton_2 = new QRadioButton(tableaquery);
        downButton_2->setObjectName(QStringLiteral("downButton_2"));
        downButton_2->setGeometry(QRect(180, 170, 89, 16));
        pushButton = new QPushButton(tableaquery);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 230, 75, 23));
        label_2 = new QLabel(tableaquery);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 30, 91, 16));
        ridButton = new QRadioButton(tableaquery);
        ridButton->setObjectName(QStringLiteral("ridButton"));
        ridButton->setGeometry(QRect(270, 60, 89, 16));
        cidButton_2 = new QRadioButton(tableaquery);
        cidButton_2->setObjectName(QStringLiteral("cidButton_2"));
        cidButton_2->setGeometry(QRect(270, 90, 89, 16));
        cnameButton_3 = new QRadioButton(tableaquery);
        cnameButton_3->setObjectName(QStringLiteral("cnameButton_3"));
        cnameButton_3->setGeometry(QRect(270, 120, 89, 16));
        startTButton_4 = new QRadioButton(tableaquery);
        startTButton_4->setObjectName(QStringLiteral("startTButton_4"));
        startTButton_4->setGeometry(QRect(270, 150, 89, 16));
        endTButton_5 = new QRadioButton(tableaquery);
        endTButton_5->setObjectName(QStringLiteral("endTButton_5"));
        endTButton_5->setGeometry(QRect(270, 180, 89, 16));
        nowTButton_6 = new QRadioButton(tableaquery);
        nowTButton_6->setObjectName(QStringLiteral("nowTButton_6"));
        nowTButton_6->setGeometry(QRect(270, 210, 89, 16));
        calendarWidget = new QCalendarWidget(tableaquery);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->setGeometry(QRect(400, 20, 296, 236));
        calendarWidget->setFirstDayOfWeek(Qt::Sunday);
        calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        calendarWidget->setNavigationBarVisible(true);

        retranslateUi(tableaquery);

        QMetaObject::connectSlotsByName(tableaquery);
    } // setupUi

    void retranslateUi(QDialog *tableaquery)
    {
        tableaquery->setWindowTitle(QApplication::translate("tableaquery", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("tableaquery", "\345\205\263\351\224\256\345\255\227", Q_NULLPTR));
        upButton->setText(QApplication::translate("tableaquery", "\345\215\207\345\272\217", Q_NULLPTR));
        downButton_2->setText(QApplication::translate("tableaquery", "\351\231\215\345\272\217", Q_NULLPTR));
        pushButton->setText(QApplication::translate("tableaquery", "\346\237\245\350\257\242", Q_NULLPTR));
        label_2->setText(QApplication::translate("tableaquery", "\346\216\222\345\272\217\346\226\271\345\274\217", Q_NULLPTR));
        ridButton->setText(QApplication::translate("tableaquery", "\346\210\277\351\227\264\345\217\267", Q_NULLPTR));
        cidButton_2->setText(QApplication::translate("tableaquery", "\351\241\276\345\256\242id", Q_NULLPTR));
        cnameButton_3->setText(QApplication::translate("tableaquery", "\351\241\276\345\256\242\345\220\215", Q_NULLPTR));
        startTButton_4->setText(QApplication::translate("tableaquery", "\345\274\200\345\247\213\346\227\266\351\227\264", Q_NULLPTR));
        endTButton_5->setText(QApplication::translate("tableaquery", "\347\273\223\346\235\237\346\227\266\351\227\264", Q_NULLPTR));
        nowTButton_6->setText(QApplication::translate("tableaquery", "\347\216\260\345\234\250\346\227\266\351\227\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class tableaquery: public Ui_tableaquery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEAQUERY_H
