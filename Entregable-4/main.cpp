#include <iostream>
using namespace std;

string a = "aaba";
string b = "abaa";

//Usar los strings como arrays de chars

bool equivalente(int ia,int fa,int ib,int fb,int n){
    int medio = n / 2;
    bool equiv = false;
    if(n==1){
        equiv = 
    } else if( n%2 == 0){
        equiv = 
    } else if( n%2 !=0){
        equiv = a.substr(ia,fa+1) == b.substr(ib,fb+1);
    }
    return equiv;
}


int main(){
    cin>>a;
    cin>>b;

    int n = a.length();

    if( a == b || equivalente(0,n-1,0,n-1,n))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}