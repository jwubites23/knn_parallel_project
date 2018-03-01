#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

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

double **many_to_many_distances_omp(double **points_A, double **points_B, int length_A, int length_B, int dims) {
    
    double ** distances;
    distances = malloc(sizeof(double)*length_A);
    for (int i=0; i<length_A; i++)
        distances[i] = (double *)malloc(length_B * sizeof(double));
    
    #pragma omp parallel for
    for (int i=0; i<length_A; i++){
        double *temp = one_to_many_distances(points_A[i], points_B, length_B, dims);
        distances[i] = temp;
    }
    
    return distances;
}

void test_many_to_many_distances(){
    int length_A = 3;
    int length_B = 2;
    int dims = 2;
    
    double *a[length_A];
    for (int i=0; i<length_A; i++)
        a[i] = (double *)malloc(dims * sizeof(double));
    
    double *b[length_B];
    for (int i=0; i<length_B; i++)
        b[i] = (double *)malloc(dims * sizeof(double));
    
    double *dist[length_B];
    for (int i=0; i<length_A; i++)
        dist[i] = (double *)malloc(length_B * sizeof(double));
    
    
    a[0][0] = 1.0;
    a[0][1] = 2.0;
    a[1][0] = 3.0;
    a[1][1] = 4.0;
    a[2][0] = 5.0;
    a[2][1] = 6.0;
    
    b[0][0] = 7.0;
    b[0][1] = 8.0;
    b[1][0] = 9.0;
    b[1][1] = 10.0;
    
    dist[0][0] = 8.485;
    dist[0][1] = 11.314;
    dist[1][0] = 5.657;
    dist[1][1] = 8.485;
    dist[2][0] = 2.828;
    dist[2][1] = 5.657;
    
    double **distance = many_to_many_distances(a, b, 3, 2, 2);
    double error;
    
    for (int i=0; i<length_A; i++)
        for (int j=0; j<length_B; j++){
            error = distance[i][j] - dist[i][j];
            error = sqrt(error*error);
            if (error < 0.01){
                printf("pass %f", distance[i][j]);
                printf("     %f \n", dist[i][j]);
            }
            else {
                printf("fail %f", distance[i][j]);
                printf("     %f \n", dist[i][j]);
            }
        }
}

