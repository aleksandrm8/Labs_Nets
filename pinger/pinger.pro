#-------------------------------------------------
#
# Project created by QtCreator 2013-05-07T09:35:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pinger
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    pinger.cpp

HEADERS  += dialog.h \
    pinger.h

FORMS    += dialog.ui


#http://tangentsoft.net/wskfaq/examples/rawping.html

#Необходимо разработать программу для определения времени двойного оборота пакета до
#тестируемого узла и обратно (аналог утилиты Ping), используя RAW socket (ICMP_ECHO и ICMP_ECHOREPLY).
