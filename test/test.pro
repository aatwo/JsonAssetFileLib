TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    buildertest.cpp \
    readertest.cpp \
    common.cpp

HEADERS += \
    buildertest.h \
    readertest.h \
    common.h


INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
