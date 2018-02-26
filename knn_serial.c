#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double euclidean_distance(double *pointA, double *pointB, int dims) {
    double distance = 0.0;
    for (int i=0; i<dims; i++)
        distance += pow(pointA[i] - pointB[i],2);
    return sqrt(distance);
}

double *one_to_many_distances(double *one_point, double **many_points, int many_length, int dims) {
    
    double *distances;
    distances = malloc(sizeof(double)*many_length);
        
    for (int i=0; i<many_length; i++)
        distances[i] = euclidean_distance(one_point, many_points[i], dims);
    
    return distances;
}

double **many_to_many_distances(double **points_A, double **points_B, int length_A, int length_B, int dims) {
    
    double ** distances;
    distances = malloc(sizeof(double)*length_A);
    for (int i=0; i<length_A; i++)
        distances[i] = (double *)malloc(length_B * sizeof(double));
    
    for (int i=0; i<length_A; i++)
        distances[i] = one_to_many_distances(points_A[i], points_B, length_B, dims);
    
    return distances;
}

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
            ref_points[i][j]=1.1*rand()*5000/RAND_MAX;
    
    // generate pseudo-random query points
    double *query_points[m];
    for (int i=0; i<m; i++)
        query_points[i] = (double *)malloc(dims * sizeof(double));
    
    for(int i=0; i<m; i++)
        for(int j=0; j<dims; j++)
            query_points[i][j]=1.1*rand()*5000/RAND_MAX;
    
    double **distances = many_to_many_distances(query_points, ref_points, m, n, dims);
    
    printf("Ref point: %f \n", ref_points[0][0]);
    printf("Ref point: %f \n", ref_points[0][1]);
    printf("Query point: %f \n", query_points[0][0]);
    printf("Query point: %f \n", query_points[0][1]);
    printf("Distance: %f \n", distances[0][0]);
    printf("Distance: %f \n", distances[0][1]);
    return 0;
}
