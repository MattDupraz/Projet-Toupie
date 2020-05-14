CONFIG += c++14

SOURCES += src/common/vect.cpp \
           src/common/matrix_3x3.cpp \
           src/common/top.cpp \
           src/common/top_non_rolling.cpp \
           src/common/top_simple_cone.cpp \
           src/common/top_chinese.cpp \
           src/common/top_general.cpp \
           src/common/top_gyroscope.cpp \
           src/common/math_utils.cpp \
           src/common/integrator_euler_cromer.cpp \
           src/common/integrator_newmark.cpp \
           src/common/integrator_runge_kutta.cpp \
           src/common/system.cpp \
           src/common/constants.cpp
HEADERS += src/common/vect.h \
           src/common/matrix_3x3.h \
           src/common/view.h \
           src/common/top.h \
           src/common/top_non_rolling.h \
           src/common/top_simple_cone.h \
           src/common/top_chinese.h \
           src/common/top_general.h \
           src/common/top_gyroscope.h \
           src/common/math_utils.h \
           src/common/integrator.h \
           src/common/integrator_euler_cromer.h \
           src/common/integrator_newmark.h \
           src/common/integrator_runge_kutta.h \
           src/common/constants.h \
           src/common/system.h

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

