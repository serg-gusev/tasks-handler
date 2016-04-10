#-------------------------------------------------
#
# Project created by QtCreator 2016-04-03T23:03:33
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = tasks-handler
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    node.cpp \
    edge.cpp \
    scene.cpp \
    graph.cpp

HEADERS  += mainwindow.h \
    node.h \
    edge.h \
    scene.h \
    graph.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
