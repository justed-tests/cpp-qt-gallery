#-------------------------------------------------
#
# Project created by QtCreator 2017-03-09T09:23:34
#
#-------------------------------------------------

QT       += sql
QT       -= gui

TARGET = gallery-core
TEMPLATE = lib

DEFINES += GALLERYCORE_LIBRARY

SOURCES += Album.cpp \
           Picture.cpp \
    DatabaseManager.cpp \
    AlbumDao.cpp

HEADERS += Album.h\
           gallery-core_global.h \
           Picture.h \
    DatabaseManager.h \
    AlbumDao.h
