// Your First C++ Program

#include <iostream>
#include <vector>
using namespace std;

//Aux
void copy(vector<int>& a,vector<int>& b,int size_a,int size_b){
    for (size_t i = 0; i < size_b; i++){
        b.pop_back();
    }
    for (size_t i = 0; i < size_a; i++){
        b.push_back(a[i]);
    }
}

void showVector(vector<int> s){
    for (int i=0; i<s.size(); i++)  
        cout << s[i] << " ";  
    cout<< endl;
}

//MagiCuadrados

//Maxi-Subconjunto
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

vector<int> maxiSubconjunto(int indice,int n, int k,vector<vector<int>> m,vector<int>& s, vector<int>& s_parcial){
    vector<int> r = s;
    if(s_parcial.size() == k && suma(s_parcial,m) > suma(s,m)){
       copy(s_parcial,s,s_parcial.size(),s.size());
    } else{
        for(int i = indice; i<n ;i++){
            s_parcial.push_back(i);
            r = maxiSubconjunto(indice+1,n,k,m,s,s_parcial);
            s_parcial.pop_back();
        }
    }
    return r;
}


//RutaMinima
int main() {
    vector<vector<int>> m = {{0,10,10,1},{0,0,5,2},{0,0,0,1},{0,0,0,0}};
    vector<int> s = {};
    vector<int> s_parcial = {};
    vector<int> r = {};
    int n = 4;
    int k = 3;
    r = maxiSubconjunto(0,n,k,m,s,s_parcial);
    cout<<suma({0,1,2},m)<<endl;
    cout<<suma({0,1,3},m)<<endl;
    showVector(r);
    return 0;
}