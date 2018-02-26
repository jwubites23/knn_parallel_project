CC=gcc

knn_serial: knn_serial.c
	$(CC) knn_serial.c -o knn_serial -lm
	
clean:
	rm knn_serial