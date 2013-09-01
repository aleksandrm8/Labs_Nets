#Вариант №2
#1. Описание задачи
#Реализация простейшего FTP клиента, с использованием не блокирующих сокетов, протоколов TCP и FTP.

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ftp_lab
TEMPLATE = app


SOURCES += main.cpp\
        ftpwindow.cpp

HEADERS  += ftpwindow.h

FORMS    += ftpwindow.ui
