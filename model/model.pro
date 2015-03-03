#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T14:40:52
#
#-------------------------------------------------

! include( ../staticlib.pri ) {
    error( "Couldn't find the common.pri file!" )
}

QT       -= core gui

CONFIG += staticlib

SOURCES += mmmodel.cpp

HEADERS += mmmodel.h
