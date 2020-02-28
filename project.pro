SOURCES = src/programme_test.cc

CONFIG += c++11

win32:LIBS += -lopengl32

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
