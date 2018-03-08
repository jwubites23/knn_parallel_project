CC=gcc
OMPFLAG=-fopenmp

experiment: experiment.c knn_serial.o knn_parallel.o qsort.o distance.o functions.h
	$(CC) $(OMPFLAG) experiment.c knn_parallel.o knn_serial.o qsort.o distance.o -lm -o experiment 

knn_parallel.o: knn_parallel.c
	$(CC) $(OMPFLAG) -c knn_parallel.c
	
knn_serial.o: knn_serial.c
	$(CC) $(OMPFLAG) -c knn_serial.c
	
qsort.o: qsort.c
	$(CC) $(OMPFLAG) -c qsort.c

distance.o: distance.c
	$(CC) $(OMPFLAG) -c distance.c -lm

clean:
	rm experiment knn_parallel.o knn_serial.o qsort.o distance.o