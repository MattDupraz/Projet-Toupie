CONFIG += c++11

SOURCES += src/common/vect.cpp
HEADERS += src/common/vect.h \
           src/common/view.h \
           src/common/top.h

INCLUDEPATH = src/common

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

