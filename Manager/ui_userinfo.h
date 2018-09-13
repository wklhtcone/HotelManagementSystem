/********************************************************************************
** Form generated from reading UI file 'userinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFO_H
#define UI_USERINFO_H

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

class Ui_userinfo
{
public:
    QLabel *label;
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *deleteButton_2;
    QPushButton *modifyButton_3;
    QPushButton *queryButton;
    QPushButton *rpriceButton;

    void setupUi(QDialog *userinfo)
    {
        if (userinfo->objectName().isEmpty())
            userinfo->setObjectName(QStringLiteral("userinfo"));
        userinfo->resize(605, 446);
        label = new QLabel(userinfo);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 81, 31));
        tableWidget = new QTableWidget(userinfo);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(50, 80, 451, 192));
        addButton = new QPushButton(userinfo);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setGeometry(QRect(60, 290, 75, 23));
        deleteButton_2 = new QPushButton(userinfo);
        deleteButton_2->setObjectName(QStringLiteral("deleteButton_2"));
        deleteButton_2->setGeometry(QRect(180, 290, 75, 23));
        deleteButton_2->setFlat(false);
        modifyButton_3 = new QPushButton(userinfo);
        modifyButton_3->setObjectName(QStringLiteral("modifyButton_3"));
        modifyButton_3->setGeometry(QRect(310, 290, 75, 23));
        queryButton = new QPushButton(userinfo);
        queryButton->setObjectName(QStringLiteral("queryButton"));
        queryButton->setGeometry(QRect(430, 290, 75, 23));
        rpriceButton = new QPushButton(userinfo);
        rpriceButton->setObjectName(QStringLiteral("rpriceButton"));
        rpriceButton->setGeometry(QRect(230, 340, 101, 23));

        retranslateUi(userinfo);

        QMetaObject::connectSlotsByName(userinfo);
    } // setupUi

    void retranslateUi(QDialog *userinfo)
    {
        userinfo->setWindowTitle(QApplication::translate("userinfo", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("userinfo", "\346\210\277\351\227\264\344\277\241\346\201\257", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("userinfo", "room_id", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("userinfo", "room_type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("userinfo", "unit_price", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("userinfo", "check_in?", Q_NULLPTR));
        addButton->setText(QApplication::translate("userinfo", "\345\242\236\345\212\240", Q_NULLPTR));
        deleteButton_2->setText(QApplication::translate("userinfo", "\345\210\240\351\231\244", Q_NULLPTR));
        modifyButton_3->setText(QApplication::translate("userinfo", "\344\277\256\346\224\271", Q_NULLPTR));
        queryButton->setText(QApplication::translate("userinfo", "\346\237\245\350\257\242", Q_NULLPTR));
        rpriceButton->setText(QApplication::translate("userinfo", "\344\277\256\346\224\271\346\210\277\351\227\264\345\215\225\344\273\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class userinfo: public Ui_userinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFO_H
