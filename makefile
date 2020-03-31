CFLAGS= -O3 -Wall -ansi

amazeme: main.o funcs.o structs.o file.o
	gcc $(CFLAGS) -o amazeme main.o funcs.o structs.o file.o

main.o: main.c funcs.h structs.h file.h
	gcc $(CFLAGS) -c main.c

file.o: file.c file.h
	gcc $(CFLAGS) -c file.c

structs.o: structs.c structs.h
	gcc $(CFLAGS) -c structs.c

funcs.o: funcs.c funcs.h
	gcc $(CFLAGS) -c funcs.c

clean:
	rm -f *.o *.~ amazeme *.gch
