#include <iostream>
#include <vector>
using namespace std;
/*

Este esquema esta menos optimizado, la copia es O(n+m) siendo n y la longitud de s y m la de s_parcila,
a su vez cada vez que s_parcial.size == n tengo que recorre toda la matriz, O(n²)

int suma(vector<int> s,vector<vector<int>> m){
    int sum = 0;
    if(s.size()!= 0){
        for(int i : s){
    	    for(int j : s){
                sum += m[i][j];
            }
        }
    }
    return sum;
}

void copy(vector<int>& a,vector<int>& b,int size_a,int size_b){
    for (size_t i = 0; i < size_b; i++){
        b.pop_back();
    }
    for (size_t i = 0; i < size_a; i++){
        b.push_back(a[i]);
    }
}

void maxiSubconjunto(int indice,int n, int k,vector<vector<int>> m,vector<int>& s, vector<int>& s_parcial){
    vector<int> r = s;
    if(s_parcial.size() == k && suma(s_parcial,m) > suma(s,m)){
       copy(s_parcial,s,s_parcial.size(),s.size());
    } else{
        for(int i = indice; i<n ;i++){
            s_parcial.push_back(i);
            maxiSubconjunto(indice+1,n,k,m,s,s_parcial);
            s_parcial.pop_back();
        }
    }
}
*/

//Aux
void showVector(vector<int> s){
    for (int i=0; i<s.size(); i++)  
        cout << s[i] << " ";  
    cout<< endl;
}

//maxiSubconjunto
vector<int> res;
int max_sum = -1;

void maxiSubconjunto(int indice,int k,vector<vector<int>> m,vector<int>& sol_parcial,int suma_parcial){
    int n = m.size();
    if(sol_parcial.size() == k ){
        if(suma_parcial > max_sum){
            res = sol_parcial;
            max_sum = suma_parcial;
        }
    } else{
        //Agrego poda, no busco si la solucion parcial ya es mayor a k
        if(sol_parcial.size() <= k){
            for(int i = indice; i<n ;i++){
                sol_parcial.push_back(i);

                int s = 0;
                for(int j = 0; j < sol_parcial.size(); j++){
                    s += m[i][sol_parcial[j]] + m[sol_parcial[j]][i];
                }

                maxiSubconjunto(indice+1,k,m,sol_parcial,suma_parcial + s);
                sol_parcial.pop_back();
                s = 0;
            }
        }
    }
    showVector(sol_parcial);
}

int main() {
    vector<vector<int>> m = {{0,10,10,1},{0,0,5,2},{0,0,0,1},{0,0,0,0}};
    vector<int> s = {};
    vector<int> s_parcial = {};
    vector<int> r = {};
    int k = 3;
    maxiSubconjunto(0,k,m,s_parcial,0);
    showVector(res);
    return 0;
}

