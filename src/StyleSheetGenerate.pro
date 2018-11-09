#-------------------------------------------------
#
# Project created by QtCreator 2018-11-08T14:24:55
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StyleSheetGenerate
TEMPLATE = app

include(./Path.pri)

SOURCES += main.cpp\
        MainWindow.cpp \
    XmlRW.cpp \
    DataModel/WidgetNameModel.cpp

HEADERS  += MainWindow.h \
    XmlRW.h \
    DataModel/WidgetNameModel.h

FORMS    += MainWindow.ui
