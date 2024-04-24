#include <iostream>
using namespace std;

string a = "";
string b = "";

bool equivalente(int ia,int fa,int ib,int fb,int n){
    bool equiv = false;
    if(n==1){
        equiv = a[fa] == b[fb];
    } else if( n%2 == 0){
        // equiv = (a1==b1 && a2==b2) || (a1==b2 && b1==a2)
        int medio = (fa + ia) / 2;
        equiv = ( equivalente(ia,medio,ib,medio,n/2) && equivalente(medio+1,fa,medio+1,fb,n/2) ) 
                || ( equivalente(ia,medio,medio+1,fb,n/2) && equivalente(medio+1,fa,ib,medio,n/2) );
    } else if( n%2 !=0){
        equiv = a.substr(ia,n) == b.substr(ib,n);
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