build:
	gcc $(FLAG) -o binlib.o -c binlib.c 
	gcc $(FLAG) main.c binlib.o

clean:
	rm a.out
