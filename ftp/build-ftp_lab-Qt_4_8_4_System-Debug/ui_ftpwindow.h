/********************************************************************************
** Form generated from reading UI file 'ftpwindow.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTPWINDOW_H
#define UI_FTPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_FtpWindow
{
public:

    void setupUi(QDialog *FtpWindow)
    {
        if (FtpWindow->objectName().isEmpty())
            FtpWindow->setObjectName(QString::fromUtf8("FtpWindow"));
        FtpWindow->resize(400, 300);

        retranslateUi(FtpWindow);

        QMetaObject::connectSlotsByName(FtpWindow);
    } // setupUi

    void retranslateUi(QDialog *FtpWindow)
    {
        FtpWindow->setWindowTitle(QApplication::translate("FtpWindow", "FtpWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FtpWindow: public Ui_FtpWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTPWINDOW_H
