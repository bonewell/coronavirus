QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    tst_createregularpolygon.cpp \
    ../main/polygonfactory.cpp \
    ../main/regularpolygon.cpp

HEADERS += \
    ../main/regularpolygon.h \
    ../main/regularpolygon.h
