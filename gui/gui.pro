#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T17:26:46
#
#-------------------------------------------------

! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

QT += core gui widgets


#TARGET = MindForge
#TEMPLATE = app


SOURCES += mmwidget.cpp \
    mmnode.cpp \
    optionsdialog.cpp \
    mainwindow.cpp \
    mmloader.cpp

HEADERS += \
    mmwidget.h \
    common.h \
    mmnode.h \
    optionsdialog.h \
    mainwindow.h \
    mmloader.h

FORMS += \
    optionsdialog.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc \
    resources3.qrc \
    resources2.qrc

DISTFILES += \
    Todo.txt
