
#  File name :- makefile
#  Licence:- GNU GPL v3
#  Project Name:-Machine Operating System

mos   : main.c card.o cpu.o linep.o mem.o mos.o
	gcc -Wall -g -o mos main.c card.o cpu.o linep.o mem.o mos.o

card.o:card.c
	gcc -Wall -c card.c

cpu.o :cpu.c
	gcc -Wall -c cpu.c

linep.o:linep.c
	gcc -Wall -c linep.c

mem.o :mem.c
	gcc -Wall -c mem.c

mos.o :mos.c
	gcc -Wall -c mos.c

clean:
	rm mos *.o *.h.gch valtzar
