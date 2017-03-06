#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
	long int t,n,k;
	long int temp;
	cin>>t;
	
	for(int i=0;i<t;i++){
		cin>>n;
		vector<long int> a;
		for(int j=0;j<n;j++){
			cin>>temp;
			a.push_back(temp);
		}
		cin>>k;
		long int s=a.at(k-1);
		int index=0;
		sort(a.begin(), a.end());
		
		for(int i=0;i<a.size();i++){
			if(a.at(i)==s){
				index=i+1;
			}
		}

		cout<<index<<endl;
	}
	return 0;
}
	
	
	
	
