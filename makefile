build:
	gcc -o bmath.o -c bmath.c 
	gcc main.c bmath.o

clean:
	rm a.out
