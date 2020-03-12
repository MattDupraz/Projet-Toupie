CONFIG += c++11

SOURCES += src/common/vect.cpp \
           src/common/matrix_3x3.cpp \
           src/common/top.cpp
HEADERS += src/common/vect.h \
           src/common/matrix_3x3.h \
           src/common/view.h \
           src/common/top.h

INCLUDEPATH = src/common

unix|macx {
	system(mkdir -p build)
	system(mkdir -p bin)
}

win32|win64 {
	system(md build)
	system(md bin)
}


DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

