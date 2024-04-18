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

vector<vector<int>> accorns = {};

vector<vector<int>> mem = {};

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
    vector<vector<int>> test = {};
    int testCases = 0;
    cin >> testCases;
    for (int case_n = 0; case_n < testCases; ++case_n) {
        cin >> t >> h >> f;
        mem = vector<vector<int>>(h,vector<int>(t,-1));
        test = vector<vector<int>>(h,vector<int>(t,0));
        int acorns_n;
        int height;
        for (int counter_t = 0; counter_t < t; ++counter_t) {
            cin >> acorns_n;
            while(acorns_n--){
                cin >> height;
                test[counter_t][h-height] += 1;
            }
        }
    }

    for (size_t i = 0; i < test.size(); i++){
        for (size_t j = 0; j < test[0].size(); j++){
            cout<<test[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;

    for (size_t i = 0; i < test1.size(); i++){
        for (size_t j = 0; j < test1[0].size(); j++){
            cout<<test1[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;

    for (size_t i = 0; i < mem.size(); i++){
        for (size_t j = 0; j < mem[0].size(); j++){
            cout<<mem[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}