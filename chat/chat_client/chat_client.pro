QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat_client
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    client.cpp

HEADERS  += dialog.h \
    client.h

FORMS    += dialog.ui

TRANSLATIONS += chat_client_ru.ts
