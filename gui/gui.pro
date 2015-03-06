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
    optionsdialog.cpp \
    mainwindow.cpp \
    mmtextedit.cpp

HEADERS += \
    mmwidget.h \
    optionsdialog.h \
    mainwindow.h \
    mmtextedit.h

FORMS += \
    optionsdialog.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc \
    resources3.qrc \
    resources2.qrc

DISTFILES += \
    Todo.txt
