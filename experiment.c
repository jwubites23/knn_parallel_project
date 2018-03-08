#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main(){
    
    int dims = 2;
    int k = 5;
    int n[10] = {25000, 50000, 75000, 100000, 125000, 150000, 175000, 200000, 225000, 250000};
    int m[3] = {50, 150, 250};
    
    char *filename = "exp20180103.csv";
    
    test_quickargsort();
    test_insertionargsort();
    test_mergeargsort();
    
    test_euclidean_distances();
    test_manhattan_distances();
    
    FILE * fp;
    fp = fopen(filename, "w+");
    fprintf(fp, "n,m,dims,k,time_dist,time_sort,serial_parallel,distance_function,sort_function\n");
    fclose(fp);
    
    for (int i=0; i<10; i++)
        for (int j=0; j<3; j++) {
            printf("i : %d, j: %d \n", i, j);
            knn_serial(n[i], m[j], dims, k, filename, "euclidean", "quicksort");
            knn_parallel(n[i], m[j], dims, k, filename, "euclidean", "quicksort");
        }
    
    
    return 0;
}