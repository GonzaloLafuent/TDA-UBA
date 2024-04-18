#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

int f = 0;
int t = 0;
int h = 0;

vector<vector<int>> test1 = {
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
 
vector<vector<int>> test2 = {
    {1,0,0},
    {0,2,1},
    {0,1,0},
    {0,1,0},
};

vector<vector<int>> accorns = {};

vector<vector<int>> mem(t,vector<int>(h,-1));

int max_accorns(int i,int j){
    int acc = 0;
    if( i >= h ) return 0;
    if( j >= t) return 0;
    if( i == h-1 && j<t) return accorns[i][j];
    if( mem[i][j] == -1){
        if( j == t-1 ){
            //Caso ultimo arbol
            acc = max_accorns(i+1,j);
            for (int k = j-1; k >= 0; k--){
                int sum = 0;
                sum = max_accorns(i+f,k);
                acc = max(acc,sum);
            }
            mem[i][j] = acc + accorns[i][j];
        } else if ( j == 0){
            //Caso primer arbol
            acc = max_accorns(i+1,j);
            for (int k = 1; k < t; k++){
                int sum = 0;
                sum = max_accorns(i+f,k);
                acc = max(sum,acc);    
            }
            mem[i][j] = acc + accorns[i][j];
        } else{
            acc = max_accorns(i+1,j);
            for (int k = 0; k < t; k++){
                int sum = 0;
                if( k!=j )
                    sum = max_accorns(i+f,k);
                acc = max(acc,sum);
            }
            mem[i][j] = acc + accorns[i][j];
        }
    } 
    return mem[i][j];
}

int jayjay(){
    int cant_accorns = max_accorns(0,0);
    for(int i = 0; i<t; i++){
        cant_accorns = max(cant_accorns,max_accorns(0,i));
    }
    return cant_accorns;
}

int main(){
    f = 2;
    t = 3;
    h = 10;
    accorns = test1;

    mem = vector<vector<int>>(h,vector<int>(t,-1));    

    cout<<mem.size()<<":"<<mem[0].size()<<endl;

    auto start = high_resolution_clock::now();
    int max = max_accorns(0,0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Resultado jay jay: "<<max<<endl;
    cout<<"Tiempo: "<<duration.count()<<endl;
    return 0;
}