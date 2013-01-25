debug: debug_quicksort.o
	gcc -o QuickSort quicksort.o -lpthread
	
debug_quicksort.o: quicksort.c
	gcc -c -g -Wall -O0 -Wa,-a,-ad quicksort.c > quicksort.lst
	
release: release_quicksort.o
	gcc -o QuickSort quicksort.o -lpthread
	
release_quicksort.o: quicksort.c
	gcc -c -Wall -O3 -Wa,-a,-ad quicksort.c > quicksort.lst
		
clean:
	rm *.o *.lst QuickSort
