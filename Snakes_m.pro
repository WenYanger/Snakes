QT += core
QT -= gui

CONFIG += c++11

TARGET = Snakes_m
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    node.cpp \
    blockmap.cpp \
    snake.cpp

HEADERS += \
    node.h \
    blockmap.h \
    snake.h
