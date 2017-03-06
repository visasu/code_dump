#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int merge(int *arr, int left, int right){
	int mid=(left+right)/2;
	int count=0;
	int i=left;
	int j=mid+1;
	int k=left;
	int temp[right+1];
	while((i<=mid)&&(j<=right)){
		if(arr[i]<=arr[j]){
			temp[k]=arr[i];
			k++;i++;
		}
		else{
			temp[k]=arr[j];
			k++;j++;
			count += mid-i+1;
		}
	}
	while(i<=mid){
		temp[k] = arr[i];
		k++;i++;
	}
	while(j<=right){
		temp[k] = arr[j];
		k++;j++;
	}
	for(int i=left;i<=right;i++){
		arr[i]=temp[i];
	}
	return count;
}


int mergeSort(int *arr, int left, int right){
	int mid=0;
	int inv=0;
	if(left>=right) return 0;
	
	mid=(left+right)/2;
	inv = mergeSort(arr,left,mid);
	inv += mergeSort(arr, mid+1,right);
	inv += merge(arr, left, right);
	return inv;
}
	

int main(){
    int t; 
    scanf("%d",&t);
    for(int a0 = 0; a0 < t; a0++){
        int n; 
        scanf("%d",&n);
        int *arr = malloc(sizeof(int) * n);
        for(int arr_i = 0; arr_i < n; arr_i++){
           scanf("%d",&arr[arr_i]);
        }
        printf("%d\n",mergeSort(arr,0,n-1));
    }
    return 0;
}
