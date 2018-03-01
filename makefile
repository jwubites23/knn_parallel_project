CC=gcc
OMPFLAG=-fopenmp

all: knn_parallel knn_serial

knn_parallel: knn_parallel.o qsort.o distance.o
	$(CC) $(OMPFLAG) -o knn_parallel knn_parallel.o qsort.o distance.o -lm

knn_serial: knn_serial.o qsort.o distance.o
	$(CC) $(OMPFLAG) -o knn_serial knn_serial.o qsort.o distance.o -lm

knn_parallel.o: knn_parallel.c functions.h
	$(CC) $(OMPFLAG) -c knn_parallel.c -lm

knn_serial.o: knn_serial.c functions.h
	$(CC) $(OMPFLAG) -c knn_serial.c -lm
	
qsort.o: qsort.c
	$(CC) $(OMPFLAG) -c qsort.c

distance.o: distance.c
	$(CC) $(OMPFLAG) -c distance.c -lm

clean:
	rm knn_serial knn_parallel knn_parallel.o knn_serial.o qsort.o distance.o 