CC=gcc

knn_serial: knn_serial.o qsort.o distance.o
	$(CC) -o knn_serial knn_serial.o qsort.o distance.o -lm

knn_serial.o: knn_serial.c functions.h
	$(CC) -c knn_serial.c -lm
	
qsort.o: qsort.c
	$(CC) -c qsort.c

distance.o: distance.c
	$(CC) -c distance.c -lm

clean:
	rm knn_serial knn_serial.o qsort.o distance.o 