#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
//int table[2001];
unordered_map <long int,long int> table;


long int hackonacci(long int n){
    table[1]=1;
    table[2]=2;
    table[3]=3;
//	cout<<n<<",";
    if(table[n]!=0){
        return table[n];
    }
    if(n>3){
        table[n]=hackonacci(n-1)+2*hackonacci(n-2)+3*hackonacci(n-3);
        return table[n];
    }

    return table[n];
}

int angles[4];

int main(){
    long int n;
    int q;
    cin >> n >> q;
    bool mat [2001][2001];
    int counter=0;

	try{
    for(int a0 = 0; a0 < q; a0++){
        int angle;
        cin >> angle;
        if(angle%360==0){
            cout<<0<<endl;
            continue;
//            return 0;
        }
        else if(angles[(angle/90)%4] !=0){
            cout<<angles[(angle/90)%4]<<endl;
//            cout<<"using table"<<(angle/90)%4<<endl;
            continue;
        }
        
        
        for(int i=1;i<=7;i++){
            for(int j=1;j<=7;j++){
                mat[i-1][j-1]=hackonacci(i*i*j*j) & 0x1 ? true : false;
//                cout<<mat[i-1][j-1]<<",";
                
            }
//            cout<<endl;
        }
        counter=0;
        for(long int i=0;i<n;i++){
            for(long int j=0;j<n;j++){
                if(angle%360==90){
                    if(mat[i%7][j%7]!=mat[j%7][(n-i-1)%7]){//90
//                    cout<<mat[i][j]<<" : "<<mat[j][n-i-1]<<",";

                        counter++;
                  }
                }

                else if(angle%360==180){
                if(mat[i%7][j%7]!=mat[(n-i-1)%7][(n-j-1)%7])//180
                    counter++;
                }

                else if(angle%360==270){
                if(mat[i%7][j%7]!=mat[(n-i-1)%7][j%7])//270
                    counter++;
                }
                
            }
//            cout<<endl;
        }
        angles[(angle/90)%4]=counter;
//        cout<<endl;
        cout<<counter<<endl;
        
        // your code goes here
        
    }
	}catch(const runtime_error& e){
		cout<<"Exception:";
		cout<<e.what();
	}
    
    
    return 0;
}

