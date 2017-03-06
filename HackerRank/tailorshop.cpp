#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    float n, p, k;
    long int total=0;
//    vector<int> found;
    unordered_map<float,bool> map;
    float no=0;
    cin>>n;//No of sets
    cin>>p;//Cost of each item
    for(int i=0;i<n;i++){
        cin>>k;
        no=ceil(k/p*1.0);
//        cout<<"k:"<<k<<"no:"<<no<<endl;
        
        while(map[no]==true){
            no++;
        }
//        cout<<no<<endl;
        total +=no;    
        map[no]=true;
//        found.push_back(no);
    }
    cout<<total;
    return 0;
}

