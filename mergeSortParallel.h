#include <stdio.h>
#include <stdlib.h>

#include "omp.h"

/*
OpenMP implementation example
Details of implementation/tutorial can be found here: http://madhugnadig.com/articles/parallel-processing/2017/02/25/parallel-computing-in-c-using-openMP.html
*/

void mergeSortParallel(int a[],int i,int j);
void mergeParallel(int a[],int i1,int j1,int i2,int j2);

 
void mergeSortParallel(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        
        #pragma omp parallel sections 
        {

            #pragma omp section
            {
                mergeSortParallel(a,i,mid);        //left recursion
            }

            #pragma omp section
            {
                mergeSortParallel(a,mid+1,j);    //right recursion
            }
        }

        mergeParallel(a,i,mid,mid+1,j);    //merging of two sorted sub-arrays
    }
}
 
void mergeParallel(int a[],int i1,int j1,int i2,int j2)
{
    int temp[1000];    //array used for merging
    int i,j,k;
    i=i1;    //beginning of the first list
    j=i2;    //beginning of the second list
    k=0;
    
    while(i<=j1 && j<=j2)    //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)    //copy remaining elements of the first list
        temp[k++]=a[i++];
        
    while(j<=j2)    //copy remaining elements of the second list
        temp[k++]=a[j++];
        
    //Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}
