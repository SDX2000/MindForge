#-------------------------------------------------
#
# Project created by QtCreator 2015-02-08T17:26:46
#
#-------------------------------------------------

! include( ../staticlib.pri ) {
    error( "Couldn't find the common.pri file!" )
}

QT += core gui widgets


SOURCES += mmwidget.cpp \
    mmnode.cpp \
    optionsdialog.cpp \
    mainwindow.cpp

HEADERS += \
    mmwidget.h \
    common.h \
    mmnode.h \
    optionsdialog.h \
    mainwindow.h

FORMS += \
    optionsdialog.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc \
    resources3.qrc \
    resources2.qrc

DISTFILES += \
    Todo.txt
