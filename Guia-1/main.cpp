// Your First C++ Program

#include <iostream>
#include <vector>
using namespace std;



//Aux
void showVector(vector<int> s){
    for (int i=0; i<s.size(); i++)  
        cout << s[i] << " ";  
    cout<< endl;
}

//Maxi-Subconjunto con copia de vector
/*
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

//Maxi-subcojunton con variable global
vector<int> res;
int max_sum = -1;

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

void maxiSubconjuntoGlobal(int indice,int k,vector<vector<int>> m,vector<int>& s_parcial){
    int n = m.size();
    if(s_parcial.size() == k && suma(s_parcial,m) > max_sum){
        int suma_parcial = suma(s_parcial,m);
        if(suma_parcial > max_sum){
            res = s_parcial;
            max_sum = suma_parcial;
        }
    } else{
        for(int i = indice; i<n ;i++){
            s_parcial.push_back(i);
            maxiSubconjuntoGlobal(indice+1,k,m,s_parcial);
            s_parcial.pop_back();
        }
    }
}

int main() {
    vector<vector<int>> m = {{0,10,10,1},{0,0,5,2},{0,0,0,1},{0,0,0,0}};
    vector<int> s = {};
    vector<int> s_parcial = {};
    vector<int> r = {};
    int n = 4;
    int k = 3;
    maxiSubconjunto(0,n,k,m,s,s_parcial);
    maxiSubconjuntoGlobal(0,k,m,s_parcial);
    cout<<suma({0,1,2},m)<<endl;
    cout<<suma({0,1,3},m)<<endl;
    showVector(res);
    showVector(s);
    return 0;
}