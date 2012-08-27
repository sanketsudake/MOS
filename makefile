#valtzar is final executable
valtzar	:main.c card.c cpu.c linep.c mem.c mos.c
	gcc -Wall -g -o valtzar main.c card.c cpu.c linep.c mem.c mos.c

# card.o	:card.c
# 	gcc -c card.c

# cpu.o  	:cpu.c
# 	gcc -c cpu.c

# linep.o	:linep.c
# 	gcc -c linep.c

# mem.o	:mem.c
# 	gcc -c mem.c

# mos.o	: mos.c
# 	gcc -c mos.c

clean	:
	rm -r *.o *.h.gch *.gcno *.gcda *.gcov
