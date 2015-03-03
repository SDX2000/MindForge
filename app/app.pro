TEMPLATE = app

QT += core gui widgets

INCLUDEPATH += . ..
WARNINGS += -Wall

SOURCES += main.cpp

# Will build the final executable in the main project directory.
TARGET = MindForge

DEPENDENCY_LIBRARIES = gui

include(../dependencies.pri)
