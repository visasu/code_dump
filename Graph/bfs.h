#include "graph.h"
/* BFS
 * Need to fix the lookup for visited to map
 */

int bfs(Graph g, Graph a){
	std::queue<Graph> q;
	std::vector<Graph> visited;
	std::vector<Graph> child;
	Graph temp;
	q.push(g);
	visited.push_back(g);
	bool found=false;
	while(!q.empty()){
		temp=q.front();
		std::cout<<temp<<std::endl;
		q.pop();
		if(temp==a){
			std::cout<<"\nFound:"<<a;
			return 0;
		}
		child=temp.returnChild();
		for(Graph k: child){
			//Checking if already visited
			for(Graph s: visited) 
				if(s==k)
					found=true;
			if(found==false){
				q.push(k);
			}
		}
	}
	return -1;
}
