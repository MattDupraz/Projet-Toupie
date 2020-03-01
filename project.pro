QT += core gui opengl widgets
CONFIG += c++11

win32:LIBS += -lopengl32

SOURCES += src/main.cpp src/gl_widget.cpp
HEADERS += src/gl_widget.h src/vertex_shader.h
RESOURCES += res/resources.qrc

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

