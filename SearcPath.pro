TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    reference.cpp \
    autoreleasepool.cpp \
    searcpath.cpp \
    vertex.cpp \
    arc.cpp

HEADERS += \
    reference.h \
    autoreleasepool.h \
    searcpath.h \
    spdefine.h \
    vertex.h \
    arc.h
