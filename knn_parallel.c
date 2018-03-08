#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <time.h>
#include <sys/time.h>
#define BILLION  1000000000L;

void knn_parallel(int n, int m, int dims, int k, char *filename, char *distance_function, char *sort_function) {
    srand(10811);
    
    // generate pseudo-random reference points
    double *ref_points[n];
    for (int i=0; i<n; i++)
        ref_points[i] = (double *)malloc(dims * sizeof(double));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<dims; j++)
            ref_points[i][j] = 1.1*rand()*5000/RAND_MAX;
    
    // generate pseudo-random query points
    double *query_points[m];
    for (int i=0; i<m; i++)
        query_points[i] = (double *)malloc(dims * sizeof(double));
    
    for(int i=0; i<m; i++)
        for(int j=0; j<dims; j++)
            query_points[i][j] = 1.1*rand()*5000/RAND_MAX;
    
    // generate pseudo-random reference point outcomes
    double *outcome_points;
    outcome_points = (double*)malloc(sizeof(double)*n);
    
    for(int i=0; i<n; i++)
        outcome_points[i] = 1.1*rand()*500/RAND_MAX;
    
    struct timespec start, mid, end;
    //start timer;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }

    
    // calculate all distances between reference points and query points
    double **distances = many_to_many_distances_omp(query_points, ref_points, m, n, dims, distance_function);
    
    // stop timer
    if( clock_gettime( CLOCK_REALTIME, &mid) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    double accum1=(mid.tv_sec-start.tv_sec)+(double)(mid.tv_nsec-start.tv_nsec)/BILLION;
    
    // calculate mean outcome of k nearest neighbours
    double* mean_outcome;
    mean_outcome = (double*)malloc(sizeof(double)*m);
    
    #pragma omp parallel for collapse(1)
    for (int i=0; i<m; i++){
        int* rank = quickargsort(distances[i], n, 2);    
        mean_outcome[i] = 0.0;
        for (int j=0; j<k; j++)
            mean_outcome[i] += outcome_points[rank[j]];
        
        mean_outcome[i] /= (double)k;
    }
    
    // stop timer
    if( clock_gettime( CLOCK_REALTIME, &end) == -1 ) {
        perror( "clock gettime" );
        exit( EXIT_FAILURE );
    }
    double accum2=(end.tv_sec-mid.tv_sec)+(double)(end.tv_nsec-mid.tv_nsec)/BILLION;
    
    FILE * fp;
    fp = fopen(filename, "a+");
    fprintf(fp, "%d,%d,%d,%d,%lf,%lf,%s,%s,%s\n", n, m, dims, k, accum1, accum2, "serial", distance_function, sort_function);
    fclose(fp);
    
}