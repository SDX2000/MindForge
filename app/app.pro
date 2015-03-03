TEMPLATE = app

QT += core gui widgets

INCLUDEPATH += . ..
WARNINGS += -Wall

SOURCES += main.cpp

debug {
    LIBS += -L../gui/debug
}

release {
    LIBS += -L../gui/release
}

LIBS += -lgui

# Will build the final executable in the main project directory.
TARGET = ../MindForge
