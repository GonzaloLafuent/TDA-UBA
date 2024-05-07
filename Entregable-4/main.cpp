#include <iostream>
using namespace std;

string a = "";
string b = "";

//ia = incio dl string a, ib = inicio del string b, n = tamaño del string
bool comparar(int ia,int ib,int n){
    if(n==1){
        //Si el string posee tamaño 1, solo comparo los caracteres de la posion ia e ib
        return a[ia] == b[ib];
    } else if( n%2 == 0){
        //Si el tamaño es par, lo divido en a1 a2 y b1 b2, y comparo de acuerdo a la consigna
        int medio = n/2;
        return (comparar(ia,ib,medio) && comparar(ia + medio,ib + medio,medio)) || (comparar(ia,ib + medio,medio) && comparar(ia + medio,ib,medio));
    } else {
        //de ser impar no se puede dividir en dos mitades, los comparo directamente
        return a.substr(ia,n) == b.substr(ib,n);
    }
    return false;
}

bool equivalente(){
    return (a == b || comparar(0,0,a.length()))?true:false;
}

int main(){
    cin>>a;
    cin>>b;

    if(equivalente())
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}