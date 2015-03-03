#See http://stackoverflow.com/a/1417859/39648

TEMPLATE = subdirs

SUBDIRS = gui

CONFIG += ordered

#build must be added last
SUBDIRS += build
