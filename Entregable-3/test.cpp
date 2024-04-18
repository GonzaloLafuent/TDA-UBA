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

int max_accorns_sin_memo(int i,int j){
    int acc = 0;
    if( i >= h ) return 0;
    if( j >= t) return 0;
    if( i == h-1 && j<t) return accorns[i][j];
    else{
        if( j == t-1 ){
            //Caso ultimo arbol
            acc = max_accorns_sin_memo(i+1,j);
            for (int k = j-1; k >= 0; k--){
                int sum = 0;
                sum = max_accorns_sin_memo(i+f,k);
                acc = max(acc,sum);
            }
            return acc + accorns[i][j];
        } else if ( j == 0){
            //Caso primer arbol
            acc = max_accorns_sin_memo(i+1,j);
            for (int k = 1; k < t; k++){
                int sum = 0;
                sum = max_accorns_sin_memo(i+f,k);
                acc = max(sum,acc);    
            }
            return acc + accorns[i][j];
        } else{
            acc = max_accorns_sin_memo(i+1,j);
            for (int k = 0; k < t; k++){
                int sum = 0;
                if( k!=j )
                    sum = max_accorns_sin_memo(i+f,k);
                acc = max(acc,sum);
            }
            return acc + accorns[i][j];
        }
    } 
    return acc;
}

int main(){
    f = 2;
    t = 3;
    h = 10;
    accorns = test1;

    auto start = high_resolution_clock::now();
    int max = max_accorns_sin_memo(0,0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout<<"Resultado jay jay: "<<max<<endl;
    cout<<"Tiempo: "<<duration.count()<<endl;

    int testCases;

    cin >> testCases;
    for (int case_n = 0; case_n < testCases; ++case_n) {
        cin >> t >> h >> f;
        acorns_map.assign(t+1,vector<int>(h,0));
        int acorns_n;
        int height;
        for (int counter_t = 0; counter_t < t; ++counter_t) {
            cin >> acorns_n;
            while(acorns_n--){
                cin >> height;
                acorns_map[counter_t][height-1] += 1;
            }
        }
	// resuelvo cosas bottom up

    /*
    for (int i = 0; i < cant_cases; i++){
        cin>>t>>h>>f;

        test_values.push_back({t,h,f});

        int cant_accorns = 0;
        int pos_accorn = 0;
        vector<vector<int>> test = vector<vector<int>>(t,vector<int>(h,0));
        for(int j = 0; j < t; j++){
            cin>>cant_accorns;
            for(int k = 0; k < cant_accorns; k++){
                cin>>pos_accorn;
                test[j][h-pos_accorn] = 1;
            }             
        }
        tests.push_back(test);
    }
    */

    int z;
    cin >> z;
    return 0;
}