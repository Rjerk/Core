CC = g++
CFLAGS = -Wall -O -std=c++11

PROGS = tcpservselect01

all: ${PROGS}

tcpservselect01: tcpservselect01.o unp.o
	${CC} ${CFLAGS} unp.o tcpservselect01.o -o $@

tcpservselect01.o: tcpservselect01.cpp
	${CC} ${CFLAGS} -c tcpservselect01.cpp

unp.o: unp.cpp
	${CC} ${CFLAGS} -c unp.cpp

.PHONY: clean

clean:
	rm -f ${PROGS} *.o
