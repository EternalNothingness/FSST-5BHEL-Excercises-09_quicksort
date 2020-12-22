quicksort : quicksort.o
	gcc quicksort.o -o quicksort

quicksort.o : quicksort.c
	gcc -c quicksort.c -o quicksort.o -g

clean :
	rm -f quicksort.o
