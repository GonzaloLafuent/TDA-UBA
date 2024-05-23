#include "iostream"
#include "vector"
using namespace std;

int f = 0;
int t = 0;
int h = 0;

vector<vector<int>> accorns = {};

vector<int> max_altura = {}; 

vector<vector<int>> mem = {};

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

int jayjay(){
    int cant_accorns = -1;
    for(int i = 0; i<t; i++){
        cant_accorns = max(cant_accorns,max_accorns(0,i));
    }
    return cant_accorns;
}
