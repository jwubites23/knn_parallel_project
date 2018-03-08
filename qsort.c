// code adapted from course lab sessions
// changed floats to doubles
// also used https://stackoverflow.com/questions/951848/java-array-sort-quick-way-to-get-a-sorted-list-of-indices-of-an-array

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void exchange(double *data, int *index, int i, int j){
    double temp_data=data[i];
    data[i]=data[j];
    data[j]=temp_data;
    
    int temp_index=index[i];
    index[i] = index[j];
    index[j] = temp_index;
}

int partition(int p, int r, double *data, int *index){
    double x=data[p];
    int k=p; 
    int l=r+1;
    double t;
    while(1){
        do{
            k++;
        }while((data[k] <= x) && (k<r));
        do{
            l--;
        }while(data[l] > x);
        while(k<l){
            exchange(data, index, k, l);
            
            do{
                k++;
            }while(data[k]<=x);
            do{
                l--;
            }while(data[l]>x);
        }
        
        exchange(data, index, p, l);
        return l;
    }
}

void seq_qsort(int p, int r, double *data, int *index){
    if(p < r){
        int q=partition(p, r, data, index);
        seq_qsort(p, q-1, data, index);
        seq_qsort(q+1, r, data, index);
    }
}

void q_sort(int p, int r, double *data, int *index, int low_limit){
    if(p<r){
        if((r-p)<low_limit){
            seq_qsort(p, r, data, index);
        }
        else{
            int q=partition(p, r, data, index);
            q_sort(p, q-1, data, index, low_limit);
            q_sort(q+1, r, data, index, low_limit);
        }
    }
}

int *quickargsort(double *data, int length, int low_limit){
    int *index;
    index = (int*)malloc(sizeof(int)*length);
    for (int i = 0; i<length; i++)
        index[i] = i;
    
    q_sort(0, length-1, data, index, low_limit);
    return index;
}

void test_quickargsort(){
    printf("\n\n testing quick sort function: \n");
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
    
    int *sorted = quickargsort(a, 5, 2);
    
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


