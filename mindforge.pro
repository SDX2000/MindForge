#See http://stackoverflow.com/a/1417859/39648

TEMPLATE = subdirs

SUBDIRS = gui

CONFIG += ordered

#The app folder must be added last
SUBDIRS += app
