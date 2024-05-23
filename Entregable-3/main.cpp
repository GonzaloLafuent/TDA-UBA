#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int f = 0;
int t = 0;
int h = 0;

//Matriz para representar las accorns
vector<vector<int>> accorns = {};

//Maxima cantidad de accorns por altura
vector<int> max_altura = {}; 

//Estrtcura de memorizacion 
vector<vector<int>> mem = {};

void max_accorns(){
    //1° caso, llegue al piso
    for (int j = 0; j < (int) accorns[0].size(); j++) {
        mem[h-1][j] = accorns[h-1][j];
        max_altura[h-1] = max(max_altura[h-1],mem[h-1][j]);
    }

    //2° caso, computo el maximo para cada altura distinta del piso
    for(int i = h-2; i>=0; i--){
        for(int j = 0; j < (int) accorns[0].size(); j++){
            mem[i][j] = ( i + f < h )? max(max_altura[i+f],mem[i+1][j]) + accorns[i][j]: mem[i+1][j] + accorns[i][j];
            max_altura[i] = max(max_altura[i],mem[i][j]);
        }
    }
}

int main(){    
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

        max_accorns();   
        cout<<max_altura[0]<<endl;
    }

    cin>>fin;
    return 0;
}