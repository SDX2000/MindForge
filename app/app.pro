TEMPLATE = app

QT += core gui widgets

INCLUDEPATH += . ..
WARNINGS += -Wall

SOURCES += \
    main.cpp \
    mmwidget.cpp \
    optionsdialog.cpp \
    mainwindow.cpp \
    mmtextedit.cpp \
    mmnode.cpp \
    utils.cpp \
    exceptions.cpp
    
HEADERS += \
    utils.h \
    mmwidget.h \
    optionsdialog.h \
    mainwindow.h \
    mmtextedit.h \
    mmnode.h \
    exceptions.h
    
FORMS += \
    optionsdialog.ui \
    mainwindow.ui
    
RESOURCES += \
    resources.qrc \
    resources3.qrc \
    resources2.qrc

# Will build the final executable in the main project directory.
TARGET = MindForge

# DEPENDENCY_LIBRARIES = gui model
# include(../dependencies.pri)
