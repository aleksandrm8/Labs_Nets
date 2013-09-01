/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label1;
    QLabel *label2;
    QPushButton *exitButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(216, 112);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label1 = new QLabel(Dialog);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(label1);

        label2 = new QLabel(Dialog);
        label2->setObjectName(QString::fromUtf8("label2"));

        verticalLayout->addWidget(label2);

        exitButton = new QPushButton(Dialog);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        verticalLayout->addWidget(exitButton);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("Dialog", "Undefined status of sender", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("Dialog", "Undefined status of reciver", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("Dialog", "Exit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
