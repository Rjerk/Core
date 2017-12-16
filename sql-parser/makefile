CC = cc -g
LEX = flex
YACC = bison
CFLAGS = -DYYDEBUG=1

PROGRAMS = sql

all: ${PROGRAMS}

sql: sql.tab.o sql.o
	${CC} -o $@ sql.tab.o sql.o

sql.tab.c sql.tab.h: sql.y
	${YACC} -vd sql.y

sql.c: sql.l
	${LEX} -o $*.c $<

sql.o: sql.c sql.tab.h

.SUFFIXE: .pgm .l .y .c

clean:
	rm -rf sql *.o *.output *.tab.* *.c
