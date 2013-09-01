QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat_server
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    server.cpp

HEADERS  += dialog.h \
    server.h

FORMS    += dialog.ui
