#include "graph.h"

/* DFS
 * Need to change the visited
 */

int dfs(Graph g,Graph a){//g is source and a is destination
    std::stack<Graph> q;
	std::vector<Graph> temp;
    std::vector<Graph> visited;
    Graph t;
    int found=0;
    q.push(g);
    while (!q.empty()){
        found=0;
        t=q.top();
        q.pop();
		for(Graph b : visited) {
            if (b==t){
                found=1;
            }
        }
        if (found==0){
            std::cout<<"\n"<<t;
            visited.push_back(t);
            if(t==a){
                std::cout<<"\nFound:"<<t;
                break;
            }
			temp=t.returnChild();
			for(Graph b : temp) {
				q.push(b);

            }
        }


    }


}
