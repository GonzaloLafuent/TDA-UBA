#include <iostream>
#include <vector>
using namespace std;

//Aux
void showVector(vector<int>& s){
    for (size_t i=0; i<s.size(); i++)  
        cout << s[i] << " ";  
    cout<< endl;
}

int esMagico(vector<vector<int>> s){
    int numb_magic = 0;
    for (size_t i = 0; i < s.size(); i++){
        int suma_fila  = 0;
        int suma_col  = 0;
        for (size_t j = 0; j < s.size(); j++){
            suma_fila += s[i][j];
            suma_col += s[j][i];
        }
        if(i == 0) numb_magic = suma_fila;
        if( (numb_magic != suma_fila) | (numb_magic!= suma_col)) return 0;
    }

    int sum_diag = 0;
    int n = s.size();
    for (size_t i = 0; i < s.size(); i++){
        sum_diag += s[i][i] + s[i][n-i-1]; 
    }
    if(sum_diag != numb_magic*2) return 0;
    return 1;
}

int cuadradoMagico(int i,int j,vector<int>& m,vector<vector<int>>& s){
    int n = s.size();
    int r = 0;
    if( (i == n)) r += esMagico(s);
        else if(j==n) r += cuadradoMagico(i+1,0,m,s);
            else{
                for (size_t k = 0; k < (n*n); k++){
                    if(m[k] == 0){
                        m[k] = 1;
                        s[i][j] = k+1;
                        r += cuadradoMagico(i,j+1,m,s);
                        m[k] = 0;
                        s[i][j] = 0;
                    }
                }
                
            }
    return r;
}

int main(){
    int n = 3;
    // m = mapea numeros de {1...n²}
    vector<int> m(n*n,0);
    // s = matriz magica, coloca los valores en las posiiones de la matriz
    vector<vector<int>> s( n , vector<int> (n,0));

    vector<vector<int>> p = {
        {2,7,6},
        {9,5,1},
        {4,3,8},
    };
    cout<<esMagico(p)<<endl;
    cout<<cuadradoMagico(0,0,m,s)<<endl;
    return 0;
}