OBJ = mersenne_twister.o aes.o von_neumann.o file_attente.o lois_distributions.o random_generation.o

simu: main.c $(OBJ)
	gcc -Wall -std=c99 -pedantic -o simul -lm main.c $(OBJ)

.PHONY: all clean rebuild

# Ces 2 lignes définissent la méthode de création d'un .o
.SUFFIXES: .o

.c.o:; gcc -Wall -std=c99 -pedantic -c -o $@ -lm $<
aes.o: aes.h aes.c
mersenne_twister.o: mersenne_twister.h mersenne_twister.c
von_neumann.o: von_neumann.h von_neumann.c
file_attente.o: file_attente.h file_attente.c lois_distributions.h
lois_distributions.o: lois_distributions.h lois_distributions.c random_generation.h
random_generation.o: random_generation.h random_generation.c von_neumann.h mersenne_twister.h

clean:
	rm *.o simu

rebuild: clean all

