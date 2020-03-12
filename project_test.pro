! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

TARGET = project_test

SOURCES += src/test/main_test.cpp \
           src/test/tests.cpp

HEADERS += src/test/tests.h

