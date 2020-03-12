! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

INCLUDEPATH += src/text

TARGET = project_test

SOURCES += src/test/main.cpp \
           src/test/tests.cpp \
           src/txt/view_text.cpp

HEADERS += src/test/tests.h \
           src/txt/view_text.h


