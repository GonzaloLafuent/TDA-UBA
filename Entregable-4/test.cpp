#include <iostream>
using namespace std;


bool equivalente(string &a,string &b,int n){
    if( a == b ) return true; 
    if(a.length() % 2 != 0 ) return false;

    string a1 = a.substr(0,n/2);
    string a2 = a.substr(n/2);

    string b1 = b.substr(0,n/2);
    string b2 = b.substr(n/2);

    int m = a1.length();

    return (equivalente(a1,b1,n/2) && equivalente(a2,b2,n/2)) || (equivalente(a1,b2,n/2) && equivalente(a2,b1,n/2));        
}


int main(){
    string a = "";
    string b = "";

    cin>>a;
    cin>>b;

    int n = a.length();

    if(equivalente(a,b,n))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

    return 0;
}