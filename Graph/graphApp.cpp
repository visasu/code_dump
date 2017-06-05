//graph_new.cpp
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
#include "bfs.h"
#define TYPE 0 //undirected

using namespace std;
int main() {
        Graph a1(1,1,0,TYPE);
        Graph a2(2,2,0,TYPE);
        Graph a3(3,3,0,TYPE);
        Graph a4(4,4,0,TYPE);

        a2.addEdge(a4,6);
        a3.addEdge(a4,6);

        a1.addEdge(a2,6);
        a1.addEdge(a3,6);
        
        a2.addEdge(a4,6);
        a3.addEdge(a4,6);
        vector<Graph> nodes;
        nodes.push_back(a1);
        nodes.push_back(a2);
        nodes.push_back(a3);
        nodes.push_back(a4);
        
        bfs(a1,a3);
//      topologicalSort(nodes);
        //cout<<bfs_cost(a1,a4);
//      a1.printChild();
        cout<<endl;

        return 0;
        
}


