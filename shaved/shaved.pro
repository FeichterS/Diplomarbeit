#-------------------------------------------------
#
# Project created by QtCreator 2017-07-18T20:42:17
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = shaved
TEMPLATE = app


SOURCES += main.cpp\
        menue.cpp \
    config.cpp \
    database.cpp \
    messdaten.cpp \
    qcustomplot.cpp \
    network.cpp \
    plot.cpp \
    graph.cpp

HEADERS  += menue.h \
    config.h \
    database.h \
    messdaten.h \
    qcustomplot.h \
    network.h \
    plot.h \
    graph.h

FORMS    += menue.ui \
    config.ui \
    messdaten.ui \
    graph.ui



win32: LIBS += -L$$PWD/../../../../Downloads/mysql-connector-c-6.1.10-win32/lib/ -llibmysql

INCLUDEPATH += $$PWD/../../../../Downloads/mysql-connector-c-6.1.10-win32/include
DEPENDPATH += $$PWD/../../../../Downloads/mysql-connector-c-6.1.10-win32/include
