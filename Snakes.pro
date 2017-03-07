QT += core
QT -= gui

CONFIG += c++11

TARGET = Snakes
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    snake.cpp \
    node.cpp \
    blockmap.cpp

HEADERS += \
    snake.h \
    node.h \
    blockmap.h
