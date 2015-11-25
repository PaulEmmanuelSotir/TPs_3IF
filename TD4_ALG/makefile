C_FLAGS = -Wall -O3

EXE: hash_table.o main.o
	gcc hash_table.o main.o -o EXE
main.o: main.c hash_table.h
	gcc $(C_FLAGS) -c main.c -o main.o
hash_table.o: hash_table.c hash_table.h
	gcc $(C_FLAGS) -c hash_table.c -o hash_table.o
