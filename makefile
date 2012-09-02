# /******************************************/
# /* Author:-Sanket Sudake                  */
# /* Licence:- GNU GPL v3                   */
# /* Project Name:-Machine Operating System */
# /* ****************************************/

#valtzar is final executable
valtzar: main.c card.c cpu.c linep.c mem.c mos.c
	gcc -Wall -g -o valtzar main.c card.c cpu.c linep.c mem.c mos.c

clean:
	rm valtzar *.o *.h.gch
