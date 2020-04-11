! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

INCLUDEPATH += src/text

TARGET = project_test

SOURCES += src/test/main_test.cpp \
           src/test/tests.cpp \
           src/test/view_test.cpp

HEADERS += src/test/tests.h \
           src/test/view_test.h\
	   src/test/top_test.h


