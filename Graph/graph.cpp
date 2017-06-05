//graph_new.cpp
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>

using namespace std;


class Graph{
	public: 
	int value=0;
	int nodeId=0;
	int cost=0;
	int type=0;//0=undirected, 1=directed
	vector<Graph> child;
	
	public:
	Graph(int Value=0,int id=0,int Cost=0,int Type=0) {
		value=Value;
		nodeId=id;
		cost=Cost;
		type=Type;
	}
	
	void setCost(int Cost) {
		cost=Cost;
	}
	void setValue(int Value) {
		value=Value;
	}
	void id(int id) {
		nodeId=id;
	}
	
	int getCost() {
		return cost;
	}
	int getValue() {
		return value;
	}
	int getId() {
		return nodeId;
	}
	
	int addEdge(Graph &a,int cost=0) {
		a.setCost(cost);
		child.push_back(a);
		return 0;
	}
	
	vector<Graph> returnChild() {
		return child;
	}
	
	bool isChild(Graph b) {
		for(Graph a : child) {
			if(a==b) return true;
		return false;
		}
	}
		
			
	
	void printChild() {
		int i=0;
		for(Graph a : child) cout<<a<<endl;
		
	}
		
	bool operator==(const Graph &b){
        return((this->nodeId==b.nodeId)&&(this->value==b.value));

    }
    Graph &operator=(const Graph &b){
        this->nodeId=b.nodeId;
        this->value=b.value;
		this->cost=b.cost;
		this->type=b.type;
		this->child=b.child;
        return *this;


    }
    friend ostream &operator<<(ostream &o, const Graph &b);
	
};

ostream &operator<<(ostream &o, const Graph &b){
	o<<"ID:"<<b.nodeId<<" "<<"Value:"<<b.value;
	return o;
}
		
int dfs(Graph g,Graph a){//g is source and a is destination
    stack<Graph> q;
	vector<Graph> temp;
    vector<Graph> visited;
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
            cout<<"\n"<<t;
            visited.push_back(t);
            if(t==a){
                cout<<"\nFound:"<<t;
                break;
            }
			temp=t.returnChild();
			for(Graph b : temp) {
				q.push(b);

            }
        }


    }


}
int bfs(Graph g, Graph a){
	queue<Graph> q;
	vector<Graph> visited;
	vector<Graph> child;
	Graph temp;
	q.push(g);
	visited.push_back(g);
	bool found=false;
	while(!q.empty()){
		temp=q.front();
		cout<<temp<<endl;
		q.pop();
		if(temp==a){
			cout<<"\nFound:"<<a;
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
				
		

int bfs_cost(Graph g,Graph a){
	
    queue<Graph> q;
    vector<Graph> temp;
    vector<Graph> visited;
    Graph t;
    int found=0;
    q.push(g);
    while (!q.empty()){
        found=0;
        t=q.front();
//		cout<<"T Cost is:"<<t.getCost()<<endl;
		q.pop();

        for(int i=0;i<visited.size();i++){
            if (visited[i]==t){
                found=1;
            }
        }
        if (found==0){
            //cout<<"\n"<<t;
            visited.push_back(t);
            if(t==a){
                return t.getCost()-g.getCost();
                //break;
            }
            temp=t.returnChild();

            for(int i=0;i<temp.size();i++){
				temp.at(i).setCost(temp.at(i).getCost()+t.getCost());
//				cout<<"\nAdding:"<<temp.at(i)<<" Cost:"<<temp.at(i).getCost()<<endl;
                q.push(temp.at(i));
//				print_queue(q);
            }
        }


    }
	return -1;

}

//Topological sort incomplete
int topologicalSort(vector<Graph> nodes){
	stack<Graph> st;
	stack<Graph> t;
	vector<Graph> ch;
	vector<Graph> visited;
	Graph root;
	bool found=false;
	for(Graph b : nodes){
		found=false;
		for(Graph s: visited){
			if(s==b){
				found=true;
			}
		}
		if(found==false){
			t.push(b);
			visited.push_back(b);
			//m[b]=true;
		}
		while(!t.empty()){
			root=t.top();
			t.pop();
			ch=root.returnChild();//This will only add the last node;
			if(ch.empty()){
				cout<<root<<endl;
				st.push(root);
				continue;
			}
			for(Graph a: ch){
				found=false;
				for(Graph s: visited){
					if(s==a){
						found=true;
					}
				}
				if(found==false){
					t.push(a);
				}
			}
		}
	}
	cout<<"Printing order:"<<endl;
	while(!st.empty()){
		root=st.top();
		cout<<root<<endl;
		st.pop();
	}
	return 0;
}
				
			
		
	

#define TYPE 0 //undirected

int main() {
	Graph a1(1,1,0,TYPE);
	Graph a2(2,2,0,TYPE);
	Graph a3(3,3,0,TYPE);
	Graph a4(4,4,0,TYPE);

	a2.addEdge(a4,6);
	a3.addEdge(a4,6);

	a1.addEdge(a2,6);
	a1.addEdge(a3,6);
	
	vector<Graph> nodes;
	nodes.push_back(a1);
	nodes.push_back(a2);
	nodes.push_back(a3);
	nodes.push_back(a4);
	
	bfs(a1,a3);
//	topologicalSort(nodes);
	//cout<<bfs_cost(a1,a4);
//	a1.printChild();
	cout<<endl;

	return 0;
	
}
