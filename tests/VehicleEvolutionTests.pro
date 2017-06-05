QT       += core gui
CONFIG   += C++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VehicleEvolutionTests
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


DEFINES += UNIT_TEST

# Add boost test dynamic linking macro
DEFINES += BOOST_TEST_DYN_LINK


INCLUDEPATH += $$PWD/../libraries
LIBS += -L"$$PWD/../libraries/Build/Box2D"
LIBS += -lBox2D
LIBS += -lboost_unit_test_framework

SOURCES += testmain.cpp \
    ../model.cpp \
    ../view.cpp \
    ../controller.cpp \
    ../chromosome.cpp \
    ../wheel.cpp \
    ../evolutioncontroller.cpp \
    ../window.cpp \
    evolution_controller_tests.cpp \
    chromosome_tests.cpp
    

HEADERS  += \
    ../model.h \
    ../view.h \
    ../controller.h \
    ../chromosome.h \
    ../wheel.h \
    ../evolutioncontroller.h \
    ../window.h


DESTDIR = ../TestsBuild
OBJECTS_DIR = ../TestsBuild/.obj
MOC_DIR = ../TestsBuild/.moc
RCC_DIR = ../TestsBuild/.rcc
UI_DIR = ../TestsBuild/.ui

