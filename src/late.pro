#-------------------------------------------------
#
# Project LATE created by Kiran Puranik
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = late
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    	dlgfind.cpp \
	dlgfilter.cpp \
    	dlgformat.cpp

HEADERS  += mainwindow.h \
    	ws_storage.h \
    	dlgfind.h \
    	dlgfilter.h \
    	dlgformat.h

FORMS    += mainwindow.ui \
    	dlgfind.ui \
    	dlgfilter.ui \
    	dlgformat.ui

RESOURCES += \
    	resources.qrc

