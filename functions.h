// qsort
int partition(int p, int r, double *data);
void seq_qsort(int p, int r, double *data);
void q_sort(int p, int r, double *data, int low_limit);

// distance
double euclidean_distance(double *pointA, double *pointB, int dims);
double *one_to_many_distances(double *one_point, double **many_points, int many_length, int dims);
double **many_to_many_distances(double **points_A, double **points_B, int length_A, int length_B, int dims);