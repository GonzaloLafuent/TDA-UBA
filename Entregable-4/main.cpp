#include <iostream>
using namespace std;

string a = "";
string b = "";

bool equivalente(int ia,int ib,int n){
    if(n==1){
        return a[ia] == b[ib];
    } else if( n%2 == 0){
        int medio = n/2;
        return (equivalente(ia,ib,medio) && equivalente(ia + medio,ib + medio,medio)) || (equivalente(ia,ib + medio,medio) && equivalente(ia + medio,ib,medio));
    } else {
        return a.substr(ia,n) == b.substr(ib,n);
    }
    return false;
}


int main(){
    cin>>a;
    cin>>b;

    int n = a.length();

    if( a == b || equivalente(0,0,n))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}