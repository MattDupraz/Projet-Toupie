! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

INCLUDEPATH += src/text

TARGET = project_test

<<<<<<< HEAD
SOURCES += src/test/main.cpp \
           src/test/tests.cpp \
           src/txt/view_text.cpp

HEADERS += src/test/tests.h \
           src/txt/view_text.h
=======
SOURCES += src/test/main_test.cpp \
           src/test/tests.cpp
>>>>>>> d2edfc9aefacfd99711608d0c8a550a47bdd95dd


