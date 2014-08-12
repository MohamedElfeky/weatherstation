#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T21:54:24
#
#-------------------------------------------------

QT       += core gui\
         declarative \
         network
#\
#         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = airmar_weather
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp \
    hostname.cpp \
    weatherdata.cpp

HEADERS  += mainwindow.h \
    parser.h \
    hostname.h \
    weatherdata.h #\
#    /usr/include/qwt-qt4/qwt_compass.h \
#    /usr/include/qwt-qt4/qwt_dial.h

LIBS += /usr/lib/libqwt-qt4.so
INCLUDEPATH += /usr/include/qwt-qt4/

FORMS    += mainwindow.ui \
    hostname.ui

OTHER_FILES += \
    Compass.qml
