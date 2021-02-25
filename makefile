build:
	gcc -g -o binlib.o -c binlib.c 
	gcc main.c binlib.o -g

clean:
	rm a.out
