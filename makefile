FLAG= -std=c99

build:
	gcc $(FLAG) -o bmath.o -c bmath.c 
	gcc $(FLAG) main.c bmath.o

clean:
	rm a.out
