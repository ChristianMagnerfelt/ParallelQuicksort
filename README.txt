/*	description: quicksort using recursive parallism in pthreads
	
	author: Christian Magnerfelt
	
	email: magnerf@kth.se
	
	date: 2012.02.04
   
	features: 	Uses pthreads to calculate the partition of the quicksort algorithm. The maximum amount of workers are limited 
				by maxWorkers which can be supplied by a command line argument. If the argument is 0 only the main thread will run.
				The number of "real" workers are fixed by depth which mean they are of a power of two. This guarantes that all threads perform roughly 
				the same amount of work.
				
				Summary of the algorithm:
				
				1 do parallelquicksort
				2 current depth less than max depth?
				
					Yes ->	a	partition array
							b 	create a thread to work on the right partition
							c	go to 1 using the left partition
							d	join threads and return
							
					No -> 	a	do normal quicksort on each partition
							b 	return
					
				The test values are simply one big array with random values which are lated checked with a simple for loop 
				if they are sorted.
				
				There is a possiblity of false sharing along the borders of each partition however the sort cutoff should be set big enough to avoid it.
             
	usage under Linux:
		./Quicksort {array size } {number of workers}
		
	building the executable:
		make debug 
		make release
		
		see makefile for more information about flags
		
	Swithing version
		The ealier tested version only fixed the workers by a given number which is used for comparision.
		To switch to this version you need to have git installed.
		The pervious version is located on the main branch which can be reached with the command:
			git checkout master
		To return to the dixed by depth version use the command:
			git checkout depth
	
*/
