#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstdio>
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

vector<edge> edges; 


typedef struct{
	int clus_no=0;
	vector<int> nodes;
} cluster;

int dis(cluster a, cluster b, priority_queue<edge, vector<edge>, edgeSort> q2){
	for(int i=0;i<a.nodes.size();i++){
		for(int j=0;j<b.nodes.size();j++){
			while(!q2.empty()){
				if((q2.top().v1==a.nodes.at(i))&&(q2.top().v2==b.nodes.at(j))){
					return q2.top().cost;
				}
				q2.pop();
			}
		}
	}
}
	
	

int findEntry(vector<cluster> cl, int n){
	int en=-1,i=0;
	for(cluster a : cl){
		if(a.clus_no==n){
			en=i;
		}
		i++;
	}
	return en;
}

int main(){
	priority_queue<edge, vector<edge>, edgeSort> q1, q2;
	vector<cluster> clusterGroup;
	
	vector<int> visited;
	int n=0,m=0,root=0,k=4;
	FILE *fp=fopen("sampleClustering.txt","r");
	fscanf(fp,"%d",&n);
	
	while(!feof(fp)){
		edge temp;
		fscanf(fp,"%d %d %d",&(temp.v1),&(temp.v2),&(temp.cost));
		q1.push(temp);
		edges.push_back(temp);
	}
	////////Removing Duplicates///////////
	root=1;
	visited.push_back(root);
	int cost=0;
	while(visited.size()!=n){
		edge temp=q1.top();
		//cout<<"v1:"<<temp.v1<<"v2:"<<temp.v2<<"Cost:"<<temp.cost<<endl;
		if (temp.v2==temp.v1){
			q1.pop();
			while(!q2.empty()){
				edge k=q2.top();
				q1.push(k);
				q2.pop();
			}
		}
		else if((find(visited.begin(), visited.end(), temp.v1) != visited.end())&&(find(visited.begin(), visited.end(), temp.v2) == visited.end())){
			q1.pop();
			visited.push_back(temp.v2);
			while(!q2.empty()){
				edge k=q2.top();
				q1.push(k);
				q2.pop();
			}
		}
		else if ((find(visited.begin(), visited.end(), temp.v2) != visited.end())&&(find(visited.begin(), visited.end(), temp.v1) == visited.end())){
			q1.pop();
			visited.push_back(temp.v1);
			while(!q2.empty()){
				edge k=q2.top();
				q1.push(k);
				q2.pop();
			}
		}
		else if ((find(visited.begin(), visited.end(), temp.v2) != visited.end())&&(find(visited.begin(), visited.end(), temp.v1) != visited.end())){
			q1.pop();
			while(!q2.empty()){
				edge k=q2.top();
				q1.push(k);
				q2.pop();
			}
		}
		else if (temp.v2==temp.v1){
			q1.pop();
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
	///Fill intial clusterGroup with n clusters
	cluster ctemp;
	for(int i=1;i<=n;i++){
		ctemp.clus_no=i;
		ctemp.nodes.push_back(i);
		clusterGroup.push_back(ctemp);
	}
	
	while(clusterGroup.size()!=k){
		edge temp=q1.top();
		q2.push(temp);
		q1.pop();
		int s,d=0;
		if(temp.v1<temp.v2){
			s=temp.v2;
			d=temp.v1;
		}
		else{
			s=temp.v1;
			d=temp.v2;
		}
		int i=0,si=0,di=0;
		cout<<"Searching S:"<<s<<" "<<"D:"<<d<<endl;
		si=findEntry(clusterGroup, s);
		di=findEntry(clusterGroup, d);
		
		if((si== -1)&&(di == -1)){
			cout<<"Remaping Source and Destination"<<endl;
			for(cluster n : clusterGroup){
				if(find(n.nodes.begin(), n.nodes.end(), s) != n.nodes.end()){
					for(cluster k :clusterGroup){
						if(find(k.nodes.begin(), k.nodes.end(), d) != k.nodes.end()){

							if(n.clus_no<k.clus_no){
								s=k.clus_no;
								d=n.clus_no;
							}
							else{
								s=n.clus_no;
								d=k.clus_no;
							}
						}
					}
				}
			}
		}			
		else if(si == -1){
			cout<<"Remaping Source"<<endl;
			for(cluster n : clusterGroup){
				if(find(n.nodes.begin(), n.nodes.end(), s) != n.nodes.end()){
					if(n.clus_no<d){
						s=d;
						d=n.clus_no;
					}
					else{
						s=n.clus_no;
					}
				}
			}
		}
		else if(di == -1){
			cout<<"Remaping Destination"<<endl;
			for(cluster n : clusterGroup){
				if(find(n.nodes.begin(), n.nodes.end(), d) != n.nodes.end()){
					if(n.clus_no<s){
						d=n.clus_no;
					}
					else{
						s=n.clus_no;
						d=s;
					}
				}
			}
		}
		si=findEntry(clusterGroup, s);
		di=findEntry(clusterGroup, d);
					
					
				

			
		cout<<"Index S:"<<si<<" "<<"D:"<<di<<endl;
		if(si != di){
			
		while(i!=clusterGroup.at(si).nodes.size()-1){
			clusterGroup.at(di).nodes.push_back(clusterGroup.at(si).nodes.at(i++));
		}
		clusterGroup.erase(clusterGroup.begin()+si);
		}
		
	}
	int maxspace=0;
	for(cluster a : clusterGroup){
		for(cluster b : clusterGroup){
			if(dis(a,b,q2)>maxspace){
				maxspace=dis(a,b,q2);
			}
		}
	}
	cout<<maxspace;	
	return 0;
}
				
			
	
	
