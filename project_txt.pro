! include("common.pri") {
	error("Couldn't find the common.pri file!")
}

TARGET = project_txt

QMAKE_CXXFLAGS += -DVER_TEXT

INCLUDEPATH += src/txt

SOURCES += src/main.cpp\
	   src/txt/view_text.cpp\	
		src/txt/view_file.cpp

HEADERS += src/txt/view_text.h
		src/txt/view_file.h

