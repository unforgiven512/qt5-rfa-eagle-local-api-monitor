#-------------------------------------------------
#
# Project created by QtCreator 2022-05-02T07:34:53
#
#-------------------------------------------------

QT += core gui network widgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rfa-eagle-200-local-api-monitor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += USE_RFA_DEFAULT_CREDS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
	main.cpp \
	mainwindow.cpp \
	authenticationdialog.cpp \
	rfadevicelist.cpp \
	rfadevicequery.cpp \
	rfadevicedetails.cpp

HEADERS += \
	mainwindow.h \
	rfa-default-creds.h \
	authenticationdialog.h \
	rfadevicelist.h \
	rfadevicequery.h \
	rfadevicedetails.h

FORMS += \
	mainwindow.ui \
	authenticationdialog.ui

DISTFILES += \
    rfa-rabbitmq-publish.py
