! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

TARGET = project_txt

SOURCES += main_txt.cpp\
	   src/txt/view_text.cpp

HEADERS += src/txt/view_text.h

