! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

TARGET = project_qt

win32:LIBS += -lopengl32
QT += core gui opengl widgets

SOURCES += src/qt/main_qt.cpp \
           src/qt/gl_widget.cpp \
           src/qt/view_opengl.cpp
HEADERS += src/qt/gl_widget.h \
           src/qt/view_opengl.h \
           src/qt/vertex_shader.h

RESOURCES += res/resources.qrc
