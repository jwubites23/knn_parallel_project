// qsort
void exchange(double *data, int *index, int i, int j);
int partition(int p, int r, double *data, int *index);
void seq_qsort(int p, int r, double *data, int *index);
void q_sort(int p, int r, double *data, int *index, int low_limit);
int *quickargsort(double *data, int length, int low_limit);
void test_quickargsort();

// distance
double euclidean_distance(double *pointA, double *pointB, int dims);
double *one_to_many_distances(double *one_point, double **many_points, int many_length, int dims);
double **many_to_many_distances(double **points_A, double **points_B, int length_A, int length_B, int dims);
double **many_to_many_distances_omp(double **points_A, double **points_B, int length_A, int length_B, int dims);
void test_many_to_many_distances();