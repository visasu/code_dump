#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
/* Graph Class
 * Contains structure of the graph
 */
template<class V, class C>

class Graph{
	public: 
	V value=0;
	int nodeId=0;
	C cost=0;
	int type=0;//0=undirected, 1=directed
	std::vector<Graph> child;
	
	public:
	Graph(V Value=0,int id=0,C Cost=0,int Type=0) {
		value=Value;
		nodeId=id;
		cost=Cost;
		type=Type;
	}
	
	void setCost(C Cost) {
		cost=Cost;
	}
	void setValue(V Value) {
		value=Value;
	}
	void id(int id) {
		nodeId=id;
	}
	
	C getCost() {
		return cost;
	}
	V getValue() {
		return value;
	}
	int getId() {
		return nodeId;
	}
	
	int addEdge(Graph<V,C> &a, C cost=0) {
		a.setCost(cost);
		child.push_back(a);
		return 0;
	}
	
	std::vector<Graph> returnChild() {
		return child;
	}
	
	bool isChild(Graph<V,C> b) {
		for(Graph a : child) {
			if(a==b) return true;
		return false;
		}
	}
	
	void printChild() {
		for(Graph a : child) std::cout<<a<<std::endl;
		
	}
		
	bool operator==(const Graph<V,C> &b){
        return((this->nodeId==b.nodeId)&&(this->value==b.value));

    }
    Graph &operator=(const Graph<V,C> &b){
        this->nodeId=b.nodeId;
        this->value=b.value;
		this->cost=b.cost;
		this->type=b.type;
		this->child=b.child;
        return *this;


    }
    friend std::ostream &operator<<(std::ostream &o, const Graph<V,C> &b);
	
};

std::ostream &operator<<(std::ostream &o, const Graph<C,V> &b){
	o<<"ID:"<<b.nodeId<<" "<<"Value:"<<b.value;
	return o;
}
