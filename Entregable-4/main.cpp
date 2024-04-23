#include <iostream>
using namespace std;

string a = "aaba";
string b = "abaa";

//Usar los strings como arrays de chars

bool equivalente(int inicio_a,int fin_a,int inicio_b,int fin_b){
    int tamañoString = (fin_a - inicio_a) + 1;
    int medio = tamañoString / 2;

    if(tamañoString == 1) return a[fin_a] == b[fin_b];
    else if (tamañoString % 2 == 0 ){
        return (equivalente(inicio_a, medio-1, inicio_b, medio-1) && 
                equivalente(medio, fin_a, medio, fin_b)) 
                                || 
                (equivalente(inicio_a,medio-1,medio,fin_b) && 
                 equivalente(medio,fin_a,inicio_b,medio-1));
    } else if (tamañoString % 2 != 0) return a.substr(inicio_a,fin_a) == b.substr(inicio_b,fin_b);
}


int main(){
    //cin>>a;
    //cin>>b;

    int n = a.length();

    if( a == b || equivalente(0,n-1,0,n-1))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}