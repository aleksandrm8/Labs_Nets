#Необходимо разработать программу для отправки почтовых сообщений
#по протоколу POP3, с использованием,
#библиотеки Winsock2 под ОС Windows.

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pop3
TEMPLATE = app

SOURCES += main.cpp\
        pop3.cpp

HEADERS  += pop3.h \
    Client.h

FORMS    += pop3.ui
