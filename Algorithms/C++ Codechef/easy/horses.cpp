#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main(){
	long int t,n;
	long int temp;
	cin>>t;
	
	for(int i=0;i<t;i++){
		cin>>n;
		vector<long int> a;
		for(int j=0;j<n;j++){
			cin>>temp;
			a.push_back(temp);
		}
		sort(a.begin(), a.end());

		long int min=a.at(1)-a.at(0);
		for(int i=0;i<a.size()-1;i++){
			if(min>(a.at(i+1)-a.at(i))){
				min=a.at(i+1)-a.at(i);
			}
		}
		cout<<min<<endl;
	}
	return 0;
}
	
	
	
	
