#-------------------------------------------------
#
# Project created by QtCreator 2020-01-10T11:29:50
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TomChat
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/tcp.cpp

HEADERS += \
    src/mainwindow.h \
    src/tcp.h

FORMS += \
    ui/mainwindow.ui

LIBS += -lpthread libwsock32 libws2_32

CONFIG += C++11

RESOURCES += \
    image/image.qrc

DISTFILES += \
    image/1.png
