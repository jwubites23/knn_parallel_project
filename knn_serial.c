#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main() {
    int dims = 2;
    int n = 4;
    int m = 2;
    int k = 3;
    srand(10810);
    
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
    
    // calculate all distances between reference points and query points
    double **distances = many_to_many_distances(query_points, ref_points, m, n, dims);
    
    // calculate mean outcome of k nearest neighbours
    double* mean_outcome;
    mean_outcome = (double*)malloc(sizeof(double)*m);
    
    int* ranks;
    ranks = (int*)malloc(sizeof(double)*n);
    
    for (int i=0; i<m; i++){
        mean_outcome[i] = 0.0;
        ranks = quickargsort(distances[i], n, 2);    
        for (int j=0; j<k; j++)
            mean_outcome[i] += outcome_points[ranks[j]];
        
        mean_outcome[i] /= (double)k;
    }
    
    for (int i = 0; i<m; i++)
        printf("mean outcomes %f \n", mean_outcome[i]);
    
    test_many_to_many_distances();
    test_quickargsort();
    
    return 0;
}