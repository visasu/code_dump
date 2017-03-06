#include<iostream>
#include<queue>

using namespace std;

int main(){
	int t=0,n=0,temp=0;
	int i=0;
	priority_queue<int, std::vector<int>, std::greater<int> > q2;
	cin>>t;
	for(i=0;i<t;i++){
		cin>>temp;
		q2.push(temp);
	}
	while(!q2.empty()){
		cout<<q2.top()<<endl;
		q2.pop();
	}
	return 0;
}
		
