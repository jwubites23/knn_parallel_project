#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <string.h>
#include <unistd.h>

int main(){
    
    int dims = 2;
    int k = 5;
    int n[5] = {10000, 15000, 20000, 25000, 30000};
    int m[5] = {50, 150, 250, 350, 450};
    int insertion_sort_scale_down = 20L; //scale down size on n for insertion sort due to long run times
    
    char *sort_funcs[3];
    sort_funcs[0] = "insertion";
    sort_funcs[1] = "quick";
    sort_funcs[2] = "merge";
    
    char *distance_funcs[2];
    distance_funcs[0] = "euclidean";
    distance_funcs[1] = "manhattan";
    
    char *filename = "exp20180308.csv";
    
    test_quickargsort();
    test_insertionargsort();
    test_mergeargsort();
    
    test_euclidean_distances();
    test_manhattan_distances();
    
    if (access(filename, F_OK) == -1) {
        FILE * fp;
        fp = fopen(filename, "w+");
        fprintf(fp, "n,m,dims,k,time_dist,time_sort,serial_parallel,distance_function,sort_function\n");
        fclose(fp);
    }
    
    //cycle through all sort functions, distance functions, values of n, values of m 
    for (int g=0; g<3; g++)
        for (int h=0; h<2; h++)
            for (int i=0; i<5; i++)
                for (int j=0; j<5; j++) {
                    if (strcmp(sort_funcs[g], "insertion") == 0L){
                        printf("distance: %s, sort: %s, n : %d, m: %d", distance_funcs[h], sort_funcs[g], n[i]/insertion_sort_scale_down, m[j]);
                        knn_serial(n[i]/insertion_sort_scale_down, m[j], dims, k, filename, distance_funcs[h], sort_funcs[g]);
                        knn_parallel(n[i]/insertion_sort_scale_down, m[j], dims, k, filename, distance_funcs[h], sort_funcs[g]);    
                    } else {
                        printf("distance: %s, sort: %s, n : %d, m: %d", distance_funcs[h], sort_funcs[g], n[i], m[j]);
                        knn_serial(n[i], m[j], dims, k, filename, distance_funcs[h], sort_funcs[g]);
                        knn_parallel(n[i], m[j], dims, k, filename, distance_funcs[h], sort_funcs[g]);    
                    }
                    printf(" - finished \n");
                }
    
    return 0;
}