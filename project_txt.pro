! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

TARGET = project_txt

SOURCES += src/txt/view_text.cpp\
	   src/common/matrix_3x3.cpp

HEADERS += src/txt/view_text.h\
	   src/common/matrix_3x3.h

