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

SOURCES +=

HEADERS += \
    include/jsonassetfilelib.h \
    include/jsonassetfilecommon.h \
    include/jsonassetfilebuilder.h \
    include/jsonassetfilereader.h \
    include/jsonassetfileutils.h \
    include/rapidjson/*.h \
    include/rapidjson/error/*.h \
    include/rapidjson/internal/*.h \
    include/rapidjson/msinttypes/*.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
