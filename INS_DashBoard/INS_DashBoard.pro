#-------------------------------------------------
#
# Project created by QtCreator 2017-07-17T11:06:56
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 

TARGET = INS_DashBoard
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \ 
    AudioRecode/audiorecorder.cpp \
    AudioRecode/PTT.cpp \
    AudioRecode/qaudiolevel.cpp \
    db/db_mysql.cpp \
    UI/Dashboard.cpp \
    UI/DeviceManagment.cpp \
    UI/UI.cpp \
    DashBoard_main.cpp \
    DataStorage.cpp \
    main.cpp

HEADERS += \ 
    AudioRecode/audiorecorder.h \
    AudioRecode/PTT.h \
    AudioRecode/qaudiolevel.h \
    db/db_mysql.h \
    UI/Dashboard.h \
    UI/DeviceManagment.h \
    UI/UI.h \
    css3_code.h \
    DashBoard_main.h \
    DataStorage.h \
    define.h \
    resource.h \
    resource1.h

SUBDIRS += \
    INS_DashBoard.pro

DISTFILES += \

RESOURCES += \
    res/gui_img_icon.qrc

FORMS += \
    AudioRecode/audiorecorder.ui
