// adapted from https://www.programmingsimplified.com/c/source-code/c-program-insertion-sort

#include <stdio.h>
#include <stdlib.h>

int *insertionargsort(double *data, int length)
{
    int n, c, d, temp_data, temp_index;
    
    int *index;
    index = (int*)malloc(sizeof(int)*length);
    for (int i = 0; i<length; i++)
        index[i] = i;
    
    for (c = 1 ; c <= n - 1; c++) {
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