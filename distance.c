#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <string.h>

double euclidean_distance(double *pointA, double *pointB, int dims) {
    double distance = 0.0;
    for (int i=0; i<dims; i++)
        distance += pow(pointA[i] - pointB[i],2);
    return sqrt(distance);
}

double manhattan_distance(double *pointA, double *pointB, int dims) {
    double distance = 0.0;
    for (int i=0; i<dims; i++)
        distance += fabs(pointA[i] - pointB[i]);
    return distance;
}

double *one_to_many_distances(double *one_point, double **many_points, int many_length, int dims, char *dist_func) {
    
    double *distances;
    distances = malloc(sizeof(double)*many_length);
    
    if (strcmp(dist_func,"euclidean") == 0L)
        for (int i=0; i<many_length; i++)
            distances[i] = euclidean_distance(one_point, many_points[i], dims);
    
    if (strcmp(dist_func,"manhattan") == 0L)
        for (int i=0; i<many_length; i++)
            distances[i] = manhattan_distance(one_point, many_points[i], dims);
    
    return distances;
}

double **many_to_many_distances(double **points_A, double **points_B, int length_A, int length_B, int dims, char *dist_func) {
    
    double ** distances;
    distances = malloc(sizeof(double)*length_A);
    for (int i=0; i<length_A; i++)
        distances[i] = (double *)malloc(length_B * sizeof(double));
    
    for (int i=0; i<length_A; i++)
        distances[i] = one_to_many_distances(points_A[i], points_B, length_B, dims, dist_func);
    
    return distances;
}

double **many_to_many_distances_omp(double **points_A, double **points_B, int length_A, int length_B, int dims, char *dist_func) {
    
    double ** distances;
    distances = malloc(sizeof(double)*length_A);
    for (int i=0; i<length_A; i++)
        distances[i] = (double *)malloc(length_B * sizeof(double));
    
    #pragma omp parallel for
    for (int i=0; i<length_A; i++){
        double *temp = one_to_many_distances(points_A[i], points_B, length_B, dims, dist_func);
        distances[i] = temp;
    }
    
    return distances;
}

void test_euclidean_distances(){
    printf("\n\n testing euclidean distance function: \n");
    int length_A = 3;
    int length_B = 2;
    int dims = 2;
    double threshold = 0.00001;
    
    double *a[length_A];
    for (int i=0; i<length_A; i++)
        a[i] = (double *)malloc(dims * sizeof(double));
    
    double *b[length_B];
    for (int i=0; i<length_B; i++)
        b[i] = (double *)malloc(dims * sizeof(double));
    
    double *dist[length_B];
    for (int i=0; i<length_A; i++)
        dist[i] = (double *)malloc(length_B * sizeof(double));
    
    
    a[0][0] = 11.0;
    a[0][1] = 12.0;
    a[1][0] = 14.0;
    a[1][1] = 15.0;
    a[2][0] = 17.0;
    a[2][1] = 16.0;
    
    b[0][0] = 7.0;
    b[0][1] = 3.0;
    b[1][0] = 7.0;
    b[1][1] = 14.0;
    
    dist[0][0] = 9.848857802;
    dist[0][1] = 4.472135955;
    dist[1][0] = 13.89244399;
    dist[1][1] = 7.071067812;
    dist[2][0] = 16.40121947;
    dist[2][1] = 10.19803903;
    
    double **distance = many_to_many_distances(a, b, 3, 2, 2, "euclidean");
    double **distance_omp = many_to_many_distances_omp(a, b, 3, 2, 2, "euclidean");
    double error, error_omp;
    
    for (int i=0; i<length_A; i++)
        for (int j=0; j<length_B; j++){
            error = distance[i][j] - dist[i][j];
            error = sqrt(error*error);
            error_omp = distance_omp[i][j] - dist[i][j];
            error_omp = sqrt(error_omp*error_omp);
            if (error < threshold && error_omp < threshold){
                printf("pass %f", distance[i][j]);
                printf("     %f", distance_omp[i][j]);
                printf("     %f \n", dist[i][j]);
            }
            else {
                printf("fail %f", distance[i][j]);
                printf("     %f", distance_omp[i][j]);
                printf("     %f \n", dist[i][j]);
            }
        }
}


void test_manhattan_distances(){
    printf("\n\n testing manhattan distance function: \n");
    int length_A = 3;
    int length_B = 2;
    int dims = 2;
    double threshold = 0.00001;
    
    double *a[length_A];
    for (int i=0; i<length_A; i++)
        a[i] = (double *)malloc(dims * sizeof(double));
    
    double *b[length_B];
    for (int i=0; i<length_B; i++)
        b[i] = (double *)malloc(dims * sizeof(double));
    
    double *dist[length_B];
    for (int i=0; i<length_A; i++)
        dist[i] = (double *)malloc(length_B * sizeof(double));
    
    a[0][0] = 11.0;
    a[0][1] = 12.0;
    a[1][0] = 14.0;
    a[1][1] = 15.0;
    a[2][0] = 17.0;
    a[2][1] = 16.0;
    
    b[0][0] = 7.0;
    b[0][1] = 3.0;
    b[1][0] = 7.0;
    b[1][1] = 14.0;
    
    dist[0][0] = 13.0;
    dist[0][1] = 6.0;
    dist[1][0] = 19.0;
    dist[1][1] = 8.0;
    dist[2][0] = 23.0;
    dist[2][1] = 12.0;
    
    double **distance = many_to_many_distances(a, b, 3, 2, 2, "manhattan");
    double **distance_omp = many_to_many_distances_omp(a, b, 3, 2, 2, "manhattan");
    double error, error_omp;
    
    for (int i=0; i<length_A; i++)
        for (int j=0; j<length_B; j++){
            error = fabs(distance[i][j] - dist[i][j]);
            error_omp = fabs(distance_omp[i][j] - dist[i][j]);
            if (error < threshold && error_omp < threshold){
                printf("pass %f", distance[i][j]);
                printf("     %f", distance_omp[i][j]);
                    printf("     %f \n", dist[i][j]);
            }
            else {
                printf("fail %f", distance[i][j]);
                printf("     %f", distance_omp[i][j]);
                printf("     %f \n", dist[i][j]);
            }
        }
}

