#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T14:40:52
#
#-------------------------------------------------

! include( ../staticlib.pri ) {
    error( "Couldn't find the common.pri file!" )
}

QT = core gui widgets

CONFIG += staticlib

SOURCES += \
    mmnode.cpp \
    mmloader.cpp

HEADERS += \
    mmnode.h \
    mmloader.h
