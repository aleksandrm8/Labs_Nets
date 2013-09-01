/********************************************************************************
** Form generated from reading UI file 'pop3.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POP3_H
#define UI_POP3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pop3
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QTextEdit *textEdit_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Pop3)
    {
        if (Pop3->objectName().isEmpty())
            Pop3->setObjectName(QStringLiteral("Pop3"));
        Pop3->resize(397, 187);
        centralWidget = new QWidget(Pop3);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(310, 40, 75, 31));
        pushButton->setStyleSheet(QStringLiteral(""));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 40, 291, 41));
        textEdit->setStyleSheet(QLatin1String("height:20px;\n"
"border-radius:10px;\n"
"padding:0 10px 0 10px;\n"
"border:1px solid #666;\n"
"background:#eee;\n"
"color:#333;"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 378, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setStyleSheet(QLatin1String("height:20px;\n"
"border-radius:10px;\n"
"padding:0 10px 0 10px;\n"
"border:1px solid #666;\n"
"background:#eee;\n"
"color:#333;"));

        horizontalLayout->addWidget(lineEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setStyleSheet(QLatin1String("height:20px;\n"
"border-radius:10px;\n"
"padding:0 10px 0 10px;\n"
"border:1px solid #666;\n"
"background:#eee;\n"
"color:#333;"));

        horizontalLayout->addWidget(lineEdit_2);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(310, 80, 75, 31));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(10, 90, 291, 41));
        textEdit_2->setStyleSheet(QLatin1String("height:20px;\n"
"border-radius:10px;\n"
"padding:0 10px 0 10px;\n"
"border:1px solid #666;\n"
"background:#eee;\n"
"color:#333;"));
        Pop3->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Pop3);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 397, 21));
        Pop3->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Pop3);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Pop3->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Pop3);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Pop3->setStatusBar(statusBar);

        retranslateUi(Pop3);

        QMetaObject::connectSlotsByName(Pop3);
    } // setupUi

    void retranslateUi(QMainWindow *Pop3)
    {
        Pop3->setWindowTitle(QApplication::translate("Pop3", "Pop3", 0));
        pushButton->setText(QApplication::translate("Pop3", "Connect", 0));
        label->setText(QApplication::translate("Pop3", "Host:", 0));
        lineEdit->setText(QApplication::translate("Pop3", "pop.yandex.ru", 0));
        label_2->setText(QApplication::translate("Pop3", "Port:", 0));
        lineEdit_2->setText(QApplication::translate("Pop3", "110", 0));
        pushButton_2->setText(QApplication::translate("Pop3", "Authorize", 0));
    } // retranslateUi

};

namespace Ui {
    class Pop3: public Ui_Pop3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POP3_H
