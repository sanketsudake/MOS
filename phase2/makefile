
#  File name :- makefile
#  Licence:- GNU GPL v3
#  Project Name:-Machine Operating System

valtzar: card.o cpu.o linep.o main.o mem.o mos.o pblock.o
	gcc -Wall -g -o valtzar card.o cpu.o linep.o main.o mem.o mos.o pblock.o

card.o:card.c
	gcc -Wall -g -c card.c

cpu.o :cpu.c
	gcc -Wall -g -c cpu.c

linep.o:linep.c
	gcc -Wall -g -c linep.c

main.o:main.c
	gcc -Wall -g -c main.c

mem.o :mem.c
	gcc -Wall -g -c mem.c

mos.o :mos.c
	gcc -Wall -g -c mos.c

pblock.o:pblock.c
	gcc -Wall -g -c pblock.c

clean:
	rm mos *.o *.h.gch

rmback:
	rm *~
