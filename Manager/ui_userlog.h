/********************************************************************************
** Form generated from reading UI file 'userlog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLOG_H
#define UI_USERLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_userlog
{
public:
    QLabel *label;
    QPushButton *logaButton;
    QPushButton *logbButton;

    void setupUi(QDialog *userlog)
    {
        if (userlog->objectName().isEmpty())
            userlog->setObjectName(QStringLiteral("userlog"));
        userlog->resize(400, 300);
        label = new QLabel(userlog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 91, 51));
        logaButton = new QPushButton(userlog);
        logaButton->setObjectName(QStringLiteral("logaButton"));
        logaButton->setGeometry(QRect(130, 90, 111, 28));
        logbButton = new QPushButton(userlog);
        logbButton->setObjectName(QStringLiteral("logbButton"));
        logbButton->setGeometry(QRect(130, 150, 111, 31));

        retranslateUi(userlog);

        QMetaObject::connectSlotsByName(userlog);
    } // setupUi

    void retranslateUi(QDialog *userlog)
    {
        userlog->setWindowTitle(QApplication::translate("userlog", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("userlog", "\347\224\250\346\210\267\346\227\245\345\277\227", Q_NULLPTR));
        logaButton->setText(QApplication::translate("userlog", "reservation log", Q_NULLPTR));
        logbButton->setText(QApplication::translate("userlog", "check_in log", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class userlog: public Ui_userlog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLOG_H
