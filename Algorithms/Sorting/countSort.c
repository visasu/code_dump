#include<stdio.h>

unsigned char tab[1000001];

int main(){
	int t=0,n=0,i=0;
	scanf("%d",&t);
	for(i=0;i<t;i++){
		scanf("%d",&n);
		tab[n]++;
	}
	for(i=0;i<=1000000;i++){
		while(tab[i] != 0){
			printf("%d\n",i);
			tab[i]--;
		}
	}
	return 0;
}
		