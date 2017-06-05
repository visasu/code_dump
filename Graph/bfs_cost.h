#include "graph.h"

/* BFS_COST
 * Need to change visited from std::vector to map
 */


int bfs_cost(Graph g,Graph a){
	
    std::queue<Graph> q;
    std::vector<Graph> temp;
    std::vector<Graph> visited;
    Graph t;
    int found=0;
    q.push(g);
    while (!q.empty()){
        found=0;
        t=q.front();
//		std::cout<<"T Cost is:"<<t.getCost()<<std::endl;
		q.pop();

        for(int i=0;i<visited.size();i++){
            if (visited[i]==t){
                found=1;
            }
        }
        if (found==0){
            //std::cout<<"\n"<<t;
            visited.push_back(t);
            if(t==a){
                return t.getCost()-g.getCost();
                //break;
            }
            temp=t.returnChild();

            for(int i=0;i<temp.size();i++){
				temp.at(i).setCost(temp.at(i).getCost()+t.getCost());
//				std::cout<<"\nAdding:"<<temp.at(i)<<" Cost:"<<temp.at(i).getCost()<<std::endl;
                q.push(temp.at(i));
//				print_std::queue(q);
            }
        }


    }
	return -1;

}
