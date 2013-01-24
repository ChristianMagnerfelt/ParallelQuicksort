debug: quicksort.c
	gcc -g -Wall -O0 -o QuickSort quicksort.c -lpthread
release: quicksort.c
	gcc -Wall -O2 -o QuickSort quicksort.c -lpthread
clean:
	rm QuickSort
