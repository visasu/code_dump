#include<iostream>

using namespace std;

int partition(int *arr, int left, int right){
	int pivot=arr[left];
	int pivotIndex=left;
	int temp=0;
	for(int i=left+1;i<=right;i++){
		if(arr[i] < pivot){
			pivotIndex++;
			temp=arr[i];
			arr[i]=arr[pivotIndex];
			arr[pivotIndex]=temp;
		}
	}
	temp=arr[pivotIndex];
	arr[pivotIndex]=arr[left];
	arr[left]=temp;
	return pivotIndex;
}
			


int quickSort(int *arr, int left, int right){
	if(left>=right) return 0;
	
	int pivotIndex=partition(arr, left, right);
	
	quickSort(arr, left, pivotIndex-1);
	quickSort(arr, pivotIndex+1, right);
	for(int i=left;i<=right;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}


int main(){
	int n=0;
	int t=0;
	scanf("%d",&n);
	int *arr=(int *)calloc(n,sizeof(int));
	int temp[n];
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	printf("Input:\n");
	for(int i=0;i<n;i++){
		printf("%d\n",arr[i]);
	}
	
	quickSort(arr, 0, n-1);
	printf("Output:\n");
	for(int i=0;i<n;i++){
		printf("%d\n",arr[i]);
	}
	return 0;
}