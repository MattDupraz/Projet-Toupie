! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

TARGET = project_txt

SOURCES += src/txt/view_text.cpp

HEADERS += src/txt/view_text.h
