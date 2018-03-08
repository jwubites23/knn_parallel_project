// adapted from https://www.programmingsimplified.com/c/source-code/c-program-insertion-sort

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *insertionargsort(double *data, int length)
{
    int c, d, temp_data, temp_index;
    
    int *index;
    index = (int*)malloc(sizeof(int)*length);
    for (int i = 0; i<length; i++)
        index[i] = i;
    
    for (c = 1 ; c <= length - 1; c++) {
        d = c;
        
        while (d > 0 && data[d-1] > data[d]) {
            temp_data = data[d];
            data[d] = data[d-1];
            data[d-1] = temp_data;
            
            temp_index = index[d];
            index[d] = index[d-1];
            index[d-1] = temp_index;
            
            d--;
        }
    }
    
    return index;
}


void test_insertionargsort(){
    printf("\n\n testing insertion sort function: \n");
    double *a;
    a = (double*)malloc(sizeof(double)*5);
    a[0] = 3.0;
    a[1] = 2.0;
    a[2] = 5.0;
    a[3] = 1.0;
    a[4] = 7.0;
    
    int *sort;
    sort = (int*)malloc(sizeof(int)*5);
    sort[0] = 3;
    sort[1] = 1;
    sort[2] = 0;
    sort[3] = 2;
    sort[4] = 4;
    
    int *sorted = insertionargsort(a, 5);
    
    for (int i=0; i<5; i++){
        if (sort[i] == sorted[i]){
            printf("pass %d", sort[i]);
            printf("     %d \n", sorted[i]);
        }
        else {
            printf("fail %d", sort[i]);
            printf("     %d \n", sorted[i]);
        }
    }
}
