#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int f = 0;
int t = 0;
int h = 0;

vector<vector<int>> accorns = {
    {1,0,0},
    {0,2,1},
    {0,1,0},
    {0,1,0},
    {0,0,1},
    {0,1,1},
    {1,0,1},
    {0,1,1},
    {0,0,0},
    {1,0,0},
};

vector<vector<int>> mem(t,vector<int>(h,-1));

// 0<= i < t , 0 <= j < h  
int max_accorns(int i,int j){
    int acc = 0;
    if( i >= h ) return 0;
    if( j >= t) return 0;
    if( i == h-1 && j<t) return accorns[i][j];
    else if( j == t-1 ){
        acc = max_accorns(i+1,j);
        for (size_t k = j-1; k >= 0; k--){
            int sum = 0;
            sum = max_accorns(i+f,k);
            acc = max(acc,sum);
        }
        return acc + accorns[i][j];
    } else if ( j == 0){
        acc = max_accorns(i+1,j);
        for (int k = 1; k < t; k++){
            int sum = 0;
            sum = max_accorns(i+f,k);
            acc = max(sum,acc);    
        }
        return acc + accorns[i][j];
    } else{
        acc = max_accorns(i+1,j);
        for (int k = 0; k < t; k++){
            int sum = 0;
            if( k!=j )
                sum = max_accorns(i+f,k);
            acc = max(acc,sum);
        }
        return acc + accorns[i][j];
    }
    return acc;
}

int main(){
    f = 2;
    t = 3;
    h = 10;
    int max = max_accorns(0,0); 
    //cout<<max<<endl;
    return 0;
}