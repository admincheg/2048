CPP=g++
CPP_OPTS=-Wall
LD_OPTS=-lpanel -lncursesw
SOURCES=src/console.cpp \
				src/game.cpp \
				src/main.cpp
PROGRAM=2048

all:
	${CPP} ${CPP_OPTS} ${LD_OPTS} ${SOURCES} -o ${PROGRAM}

clean:
	rm -f ${PROGRAM}
