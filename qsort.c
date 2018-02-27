// code adapted from course lab sessions
// changed floats to doubles


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int partition(int p, int r, double *data){
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
            t=data[k];
            data[k]=data[l];
            data[l]=t;
            do{
                k++;
            }while(data[k]<=x);
            do{
                l--;
            }while(data[l]>x);
        }
        t=data[p];
        data[p]=data[l];
        data[l]=t;
        return l;
    }
}

void seq_qsort(int p, int r, double *data){
    if(p < r){
        int q=partition(p, r, data);
        seq_qsort(p, q-1, data);
        seq_qsort(q+1, r, data);
    }
}

void q_sort(int p, int r, double *data, int low_limit){
    
    if(p<r){
        if((r-p)<low_limit){
            seq_qsort(p,r,data);
        }
        else{
            int q=partition(p,r,data);
            q_sort(p,q-1,data,low_limit);
            q_sort(q+1,r,data,low_limit);
        }
    }
}
