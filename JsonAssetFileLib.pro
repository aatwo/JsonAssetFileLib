#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T17:35:07
#
#-------------------------------------------------

QT -= core gui

TARGET = JsonAssetFileLib
TEMPLATE = lib

DEFINES += JSONASSETFILELIB_LIBRARY

INCLUDEPATH += \
    include

SOURCES += \
    src/jsonassetfilebuilder.cpp \
    src/jsonassetfilereader.cpp \
    src/jsonassetfileutils.cpp

HEADERS += \
    include/jsonassetfilelib.h \
    include/jsonassetfilecommon.h \
    include/jsonassetfilebuilder.h \
    include/jsonassetfilereader.h \
    include/jsonassetfileutils.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
