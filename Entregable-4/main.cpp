#include <iostream>
using namespace std;


bool equivalente(string a,string b){
    bool equiv = false;
    if(a.length() != b.length()) return  false;
    if( a == b ) return true;
    if( a.length()== 1 && b.length() == 1) return a == b;
    string a1 = a.substr(0,a.length()/2);
    string a2 = a.substr(a.length()/2);

    string b1 = b.substr(0,b.length()/2);
    string b2 = b.substr(b.length()/2);

    equiv = (equivalente(a1,b1) && equivalente(a2,b2)) || (equivalente(a1,b2) && equivalente(a2,b1));
    
    return equiv;
}


int main(){
    string a = "";
    string b = "";

    cin>>a;
    cin>>b;

    if(equivalente(a,b))
        cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}