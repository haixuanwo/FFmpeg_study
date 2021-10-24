
SOURCE = \
	src/test.cpp

MAIN = main.cpp
UNIT_TEST_MAIN = unit_test_main.cpp

TARGET = main

INDCLUDE_DIR = include
LIB_DIR = lib
GXX = g++
GCC = gcc

 FLAGS = \
	-lavformat -lavcodec -lswscale -lavutil -lswresample \
	-lz -lm -lpthread -ldl -lrt -llzma -lbz2 -lva -lX11 -lva-drm -lva-x11

all:
	${GXX} ${SOURCE} ${MAIN} -I ${INDCLUDE_DIR} -L ${LIB_DIR} ${FLAGS} -o ${TARGET}

test:
	${GXX} ${SOURCE} ${UNIT_TEST_MAIN} -I ${INDCLUDE_DIR} -L ${LIB_DIR} ${FLAGS} -lgtest -o ${TARGET}

clean:
	rm -rf ${TARGET} *.o
