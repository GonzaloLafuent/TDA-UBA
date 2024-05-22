#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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

vector<vector<int>> accorns = test1;

vector<int> max_altura = {}; 

vector<vector<int>> mem = {};

/*
int max_accorns(int i,int j){
    int acc = 0;
    if( mem[i][j] == -1){
        if( i == h-1 && j<t) return mem[i][j] = accorns[i][j];
        else if( j == t-1 ){
            //Caso ultimo arbol
            acc = max_accorns(i+1,j);
            for(int k= j-1; k>=0; k--){
                acc = max(acc, (i+f < h)? max_accorns(i+f,k):0 );
            }
            mem[i][j] = acc + accorns[i][j];
        } else if ( j == 0){
            //Caso primer arbol
            acc = max_accorns(i+1,j);
            for(int k = 1; k <t ; k++){
                acc = max(acc, ( i+f < h)? max_accorns(i+f,k):0);    
            }
            mem[i][j] = acc + accorns[i][j];
        } else{
            acc = max_accorns(i+1,j);
            for(int k = 0; k < t ;k++){
                if( k!=j )
                    acc = max(acc, (i+f < h)?max_accorns(i+f,k):0 );
            }
            mem[i][j] = acc + accorns[i][j];
        }
    } 
    return mem[i][j];
}
*/

void max_accorns(){
    for (size_t j = 0; j < accorns[0].size(); j++) {
        mem[h-1][j] = accorns[h-1][j];
        max_altura[h-1] = max(max_altura[h-1],mem[h-1][j]);
    }

    for(int i = h-2; i>=0; i--){
        for(int j = 0; j < accorns[0].size(); j++){
            if( i + f < h ) {
                mem[i][j] = max(max_altura[i+f],mem[i+1][j]) + accorns[i][j];
            } else mem[i][j] = mem[i+1][j] + accorns[i][j];
            max_altura[i] = max(max_altura[i],mem[i][j]);
        }
    }
}

/*
int jayjay(){
    int cant_accorns = -1;
    for(int i = 0; i<t; i++){
        cant_accorns = max(cant_accorns,max_accorns(0,i));
    }
    return cant_accorns;
}
*/


int main(){    
    /*
    int cant_cases = 0;
    int fin = 0;

    cin >> cant_cases;

    for (int i = 0; i < cant_cases; i++) {
        cin >> t >> h >> f;
        
        vector<vector<int>> test = vector<vector<int>>(h,vector<int>(t,0));

        for (int j = 0; j < t; j++) {
            int cant_accorns = 0;
            int pos_accorns = 0;
            cin >> cant_accorns;
            for (int k = 0; k < cant_accorns; k++){
                cin >> pos_accorns;
                test[h-pos_accorns][j] += 1;
            }
        }
        accorns = test;
        mem = vector<vector<int>>(h,vector<int>(t,-1)); 
        max_altura = vector<int>(h,0);   
        int max = jayjay();
        cout<<max<<endl;
    }

    cin>>fin;
    */

    f = 2;
    h = 10;
    t = 3;

    mem = vector<vector<int>>(h,vector<int>(t,0)); 
    max_altura = vector<int>(h,0);

    max_accorns();
    cout<<max_altura[0];
    return 0;
}