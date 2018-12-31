#-------------------------------------------------
#
# Project created by QtCreator 2018-12-28T11:20:15
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mqtt_onenet1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    mqtt/include/qmqtt/qmqttDepends \
    mqtt/qmqtt.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lqmqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lqmqttd
else:unix: LIBS += -L$$PWD/lib/ -lqmqtt

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lqmqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lqmqttd
else:unix: LIBS += -L$$PWD/lib/ -lqmqtt

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
