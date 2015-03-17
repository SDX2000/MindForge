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
    utils.cpp \
    exceptions.cpp \
    mmnodewidget.cpp
    
HEADERS += \
    utils.h \
    mmwidget.h \
    optionsdialog.h \
    mainwindow.h \
    mmtextedit.h \
    exceptions.h \
    mmnodewidget.h
    
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
