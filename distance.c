#include <math.h>
#include <stdlib.h>

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