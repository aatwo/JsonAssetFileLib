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

unix|win32: {

    Debug: {

        LIBS += -L$$PWD/../libs/debug/ -lJsonAssetFileLib
    }

    Release {

        LIBS += -L$$PWD/../libs/release/ -lJsonAssetFileLib
    }
}

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
