#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T14:23:41
#
#-------------------------------------------------

! include( ../staticlib.pri ) {
    error( "Couldn't find the common.pri file!" )
}

QT       -= core gui

CONFIG += staticlib

SOURCES += \
    lz4.c \
    lz4frame.c \
    lz4hc.c \
    xxhash.c

HEADERS += \
    lz4.h \
    lz4frame.h \
    lz4frame_static.h \
    lz4hc.h \
    xxhash.h
