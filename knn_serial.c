#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

int main() {
    int dims = 2;
    int n = 100;
    int m = 10;
    int k = 3;
    srand(10810);
    
    // generate pseudo-random reference points
    double *ref_points[n];
    for (int i=0; i<n; i++)
        ref_points[i] = (double *)malloc(dims * sizeof(double));
    
    for(int i=0; i<n; i++)
        for(int j=0; j<dims; j++)
            ref_points[i][j] = rand()*5000/RAND_MAX;
    
    // generate pseudo-random query points
    double *query_points[m];
    for (int i=0; i<m; i++)
        query_points[i] = (double *)malloc(dims * sizeof(double));
    
    for(int i=0; i<m; i++)
        for(int j=0; j<dims; j++)
            query_points[i][j] = rand()*5000/RAND_MAX;
    
    // generate pseudo-random reference point outcomes
    double *outcome_points;
    outcome_points = (double*)malloc(sizeof(double)*n);
    
    for(int i=0; i<n; i++)
        outcome_points[i] = rand()*500/RAND_MAX;
    
    
    // calculate all distances between reference points and query points
    double **distances = many_to_many_distances(query_points, ref_points, m, n, dims);
    
    double *foo = distances[0];
    q_sort(0, n-1, &foo[0], 10);
    
    return 0;
}
