
#include <iostream>
#include <vector>
using namespace std;

vector<int> res;
int sum_min = -1;

//Aux
void showVector(vector<int> s){
    for (int i=0; i<s.size(); i++)  
        cout << s[i] << " ";  
    cout<< endl;
}

//rutaMinima
void rutaMinima(vector<vector<int>> d,vector<int>& m,vector<int>& s,int suma_parcial){
    int n = d.size();
    if(s.size() == n){
        suma_parcial = d[n-1][0];
        if( sum_min == -1 || suma_parcial < sum_min ){
            sum_min = suma_parcial;
            res = s;
        }
    } else {
        for (int i = 0; i < n; i++){
            if( m[i] == 0) {
                m[i] = 1;
                s.push_back(i);
                
                int suma  = (i!=n-1)? d[i][i+1]: 0;

                //Poda para evitar mas casos
                if( sum_min == -1  || suma + suma_parcial < sum_min )
                    rutaMinima(d,m,s,suma_parcial + suma);
                s.pop_back();
                suma = 0;
                m[i] = 0;
            }
        }
    }
}


main(){
    vector<vector<int>> d = {
        {0,1,10,10},
        {10,0,3,15},
        {21,17,0,2},
        {3,22,30,0},
    };

    vector<int> m = {0,0,0,0};

    vector<int> s = {};

    rutaMinima(d,m,s,0);

    showVector(res);
    
    return 0;
}