#-------------------------------------------------
#
# Project created by QtCreator 2017-03-10T10:58:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desktop-gallery
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    AlbumListWidget.cpp \
    ThumbnailProxyModel.cpp

HEADERS  += MainWindow.h \
    AlbumListWidget.h \
    ThumbnailProxyModel.h

FORMS    += MainWindow.ui \
    AlbumListWidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/release/ -lgallery-core 
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/debug/ -lgallery-core  
else:unix: LIBS += -L$$OUT_PWD/../gallery-core/ -lgallery-core  

INCLUDEPATH += $$PWD/../gallery-core   
DEPENDPATH += $$PWD/../gallery-core

RESOURCES += \
    resource.qrc
