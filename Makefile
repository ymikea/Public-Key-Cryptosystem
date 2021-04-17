.SUFFIXES:.c.o.h
CC=gcc
CFLAGS=-g -Wall -Werror  #-std=c99 -pedantic
EXEC=wsu-pub-crypt
OBJS=wsu-pub-crypt.o 
CFILE=wsu-pub-crypt.c Miller_Expon.c
DSYM=wsu-pub-crypt.dSYM

default:all

all:
	${CC} ${CFILE} ${CFLAGS} -o ${EXEC}

${EXEC}: ${OBJS}
	        ${CC} ${CFILE} ${CFLAGS} -o ${EXEC}
%.c%.o:
	        ${CC} ${CFLAGS} -c $<

run: ${EXEC}
	    ./${EXEC}

clean:
	        rm -r -f ${EXEC} ${OBJS} ${DSYM}
cleanscr:
	        clear

valgrind: clean ${EXEC}
		valgrind -s ./${EXEC}

gdb: clean ${EXEC}
		gdb ${EXEC}

wsu-pub-crypt.o: wsu-pub-crypt.c Miller_Expon.c
