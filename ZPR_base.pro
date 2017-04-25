#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T23:11:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VehicleEvolution
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/libraries
LIBS += -L"$$PWD/libraries/Build/Box2D"
LIBS += -lBox2D

SOURCES += main.cpp \
    model.cpp \
    view.cpp \
    controller.cpp \
    qb2draw.cpp

HEADERS  += \
    model.h \
    view.h \
    controller.h \
    qb2draw.h

FORMS    +=

DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc
RCC_DIR = build/.rcc
UI_DIR = build/.ui
