#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int f = 0;
int t = 0;
int h = 0;

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
    int cant_cases = 0;
    int fin = 0;

    vector<vector<vector<int>>> tests = {};
    vector<vector<int>> test_values = {};

    cin >> cant_cases;

    for (int i = 0; i < cant_cases; i++) {
        cin >> t >> h >> f;
        test_values.push_back({t,h,f});
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
        tests.push_back(test);
    }

    cin>>fin;

    for (size_t i = 0; i < tests.size(); i++){
        accorns = tests[i];
        t = test_values[i][0];
        h = test_values[i][1]; 
        f = test_values[i][2];

        mem = vector<vector<int>>(h,vector<int>(t,-1));
        int max = 0;
        max = jayjay();

        cout<<max<<endl;
    }

    return 0;
}