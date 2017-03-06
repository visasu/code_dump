#include<stdio.h>
int check(int notes[], int n, int w){
	int tab[w+1][n+1];
	int i=0,j=0;
	for(i=0;i<=n;i++){
		for(j=0;j<=w;j++){
			if((i==0)||(j==0)){
				tab[i][j]=0;
			}
			else if (notes[i-1]<=w){
				tab[i][j] = tab[i-1][j-notes[i-1]]+notes[i-1];
			}
			else{
				tab[i][j]=tab[i-1][j];
			}
			if(tab[i][j]==w){
				return 1;
			}
		}
	}
	return 0;
}
				
	
	
int main(){
	int t=0;
	int n=0,w=0;
	int temp;
	int i=0,j=0;
	scanf("%d", &t);
	for(i=0;i<t;i++){
		scanf("%d %d",&n,&w);
		int notes[n];
		for(j=0;j<n;j++){
			scanf("%d", &n[j]);
			if(check(notes,n,w)==1){
				printf("yes\n");
			}
			else{
				printf("no\n");
			}
		}
	}
	return 0;
}