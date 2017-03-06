/*
Designed for HackerRank problem primMST
https://www.hackerrank.com/challenges/primsmstsub
*/

#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct{
	int v1;
	int v2;
	int cost;
} edge;

struct edgeSort
{
  bool operator()(const edge& n1, const edge& n2) const
  {
    return n1.cost > n2.cost;
  }
};

int main(){
	priority_queue<edge, vector<edge>, edgeSort> q1, q2;
	vector<int> visited;
	int n=0,m=0,root=0;
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;i++){
		edge temp;
		scanf("%d %d %d",&(temp.v1),&(temp.v2),&(temp.cost));
		q1.push(temp);
	}
	scanf("%d",&root);
	
	visited.push_back(root);
	int cost=0;
	while(visited.size()!=n){
		edge temp=q1.top();
		//cout<<"v1:"<<temp.v1<<"v2:"<<temp.v2<<"Cost:"<<temp.cost<<endl;
		if((find(visited.begin(), visited.end(), temp.v1) != visited.end())&&(find(visited.begin(), visited.end(), temp.v2) == visited.end())){
			q1.pop();
			cost+=temp.cost;
			visited.push_back(temp.v2);
			//cout<<"Found1:"<<temp.cost<<endl;
			while(!q2.empty()){
				edge k=q2.top();
				q1.push(k);
				q2.pop();
			}
		}
		else if ((find(visited.begin(), visited.end(), temp.v2) != visited.end())&&(find(visited.begin(), visited.end(), temp.v1) == visited.end())){
			q1.pop();
			cost+=temp.cost;
			visited.push_back(temp.v1);
			//cout<<"Found2:"<<temp.cost<<endl;
			while(!q2.empty()){
				edge k=q2.top();
				q1.push(k);
				q2.pop();
			}
		}
		else{
			q2.push(temp);
			q1.pop();
			
		}
	}
	cout<<cost;
	//cout<<"FinalCost:"<<cost;
	return 0;
}
				
			
	
	
