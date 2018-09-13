/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *userinfoButton;
    QPushButton *userlogButton;
    QPushButton *employeeButton;
    QLabel *currentTimeLabel;
    QLabel *label;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        userinfoButton = new QPushButton(centralWidget);
        userinfoButton->setObjectName(QStringLiteral("userinfoButton"));
        userinfoButton->setGeometry(QRect(140, 310, 93, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\271\346\255\243\345\247\232\344\275\223"));
        font.setPointSize(12);
        userinfoButton->setFont(font);
        userlogButton = new QPushButton(centralWidget);
        userlogButton->setObjectName(QStringLiteral("userlogButton"));
        userlogButton->setGeometry(QRect(270, 310, 93, 31));
        userlogButton->setFont(font);
        employeeButton = new QPushButton(centralWidget);
        employeeButton->setObjectName(QStringLiteral("employeeButton"));
        employeeButton->setGeometry(QRect(400, 310, 93, 31));
        employeeButton->setFont(font);
        currentTimeLabel = new QLabel(centralWidget);
        currentTimeLabel->setObjectName(QStringLiteral("currentTimeLabel"));
        currentTimeLabel->setGeometry(QRect(320, 10, 251, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(18);
        currentTimeLabel->setFont(font1);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 10, 90, 30));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        userinfoButton->setText(QApplication::translate("MainWindow", "\346\210\277\351\227\264\344\277\241\346\201\257", Q_NULLPTR));
        userlogButton->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\346\227\245\345\277\227", Q_NULLPTR));
        employeeButton->setText(QApplication::translate("MainWindow", "\345\221\230\345\267\245\344\277\241\346\201\257", Q_NULLPTR));
        currentTimeLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\273\217\347\220\206\346\250\241\345\274\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
