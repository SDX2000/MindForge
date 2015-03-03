TEMPLATE = app

QT += core gui widgets

INCLUDEPATH += . ..
WARNINGS += -Wall

SOURCES += main.cpp

LIBS += -L../gui/debug -lgui

# Will build the final executable in the main project directory.
TARGET = ../MindForge
