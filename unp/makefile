CC = g++
CFLAGS = -Wall -O -std=c++11

PROGS = tcpservselect01 tcpservpoll01

all: ${PROGS}

tcpservselect01: tcpservselect01.o unp.o
	${CC} ${CFLAGS} unp.o tcpservselect01.o -o $@

tcpservpoll01: tcpservpoll01.o unp.o
	${CC} ${CFLAGS} unp.o tcpservpoll01.o -o $@

tcpservpoll01.o: tcpservpoll01.cpp
	${CC} ${CFLAGS} -c tcpservpoll01.cpp

tcpservselect01.o: tcpservselect01.cpp
	${CC} ${CFLAGS} -c tcpservselect01.cpp

unp.o: unp.cpp
	${CC} ${CFLAGS} -c unp.cpp

.PHONY: clean

clean:
	rm -f ${PROGS} *.o
