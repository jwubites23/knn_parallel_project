// adapted from https://www.geeksforgeeks.org/merge-sort/

#include<stdlib.h>
#include<stdio.h>
 
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(double *data, int *index, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    double dataL[n1], dataR[n2];
    int indexL[n1], indexR[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        dataL[i] = data[l + i];
        indexL[i] = index[l + i];
    }
        
    for (j = 0; j < n2; j++){
        dataR[j] = data[m + 1+ j];
        indexR[j] = index[m + 1+ j];
    }
        
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (dataL[i] <= dataR[j])
        {
            data[k] = dataL[i];
            index[k] = indexL[i];
            i++;
        }
        else
        {
            data[k] = dataR[j];
            index[k] = indexR[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        data[k] = dataL[i];
        index[k] = indexL[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        data[k] = dataR[j];
        index[k] = indexR[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergesort(double *data, int *index, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergesort(data, index, l, m);
        mergesort(data, index, m+1, r);
 
        merge(data, index, l, m, r);
    }
}
 
 
/* Driver program to test above functions */
int *mergeargsort(double *data, int length)
{
    int *index;
    index = (int*)malloc(sizeof(int)*length);
    for (int i = 0; i<length; i++)
        index[i] = i;
 
    mergesort(data, index, 0, length - 1);
 
    return index;
}

void test_mergeargsort(){
    printf("\n\n testing merge sort function: \n");
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
    
    int *sorted = mergeargsort(a, 5);
    
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
