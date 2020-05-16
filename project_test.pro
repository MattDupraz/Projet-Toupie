! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

INCLUDEPATH += src/txt

TARGET = project_test

SOURCES += src/test/main_test.cpp \
           src/test/tests.cpp \
			  src/txt/view_text.cpp

HEADERS += src/test/tests.h \
	   src/test/top_test_sine.h \
	   src/test/top_test_fall.h \
           src/txt/view_text.h


