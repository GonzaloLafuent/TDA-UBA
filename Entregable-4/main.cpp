#include <iostream>
using namespace std;

string a = "aaba";
string b = "abaa";

//Usar los strings como arrays de chars

bool equivalente(int inicio_a,int fin_a,int inicio_b,int fin_b,int n){
    int medio = n / 2;

    if(n == 2){
         return (a[inicio_a] == b[inicio_b] && a[fin_a-1] == b[fin_b-1]) || (a[inicio_a]==b[fin_b-1] && a[fin_a]==b[inicio_b-1]);
    } else if (n % 2 == 0 ){
        return (equivalente(inicio_a,medio,inicio_b,medio,n/2) && 
                equivalente(medio,fin_a,medio,fin_b,n/2)) 
                                || 
                (equivalente(inicio_a,medio,medio,fin_b,n/2) && 
                 equivalente(medio,fin_a,inicio_b,medio,n/2));
    } else if (n % 2 != 0) {
        return a.substr(inicio_a,fin_a) == b.substr(inicio_b,fin_b);
    }   
    return false;
}


int main(){
    cin>>a;
    cin>>b;

    int n = a.length();

    if( a == b || equivalente(0,n,0,n,n))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}