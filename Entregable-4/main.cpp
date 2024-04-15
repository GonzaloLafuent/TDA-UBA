#include <iostream>
using namespace std;


bool equivalente(string a,string b){
    if(a.length() != b.length()) return  false;
    if(a.length() % 2 != 0 ) return a==b; 
    if( a == b ) return true;
    if( a.length()== 1 && b.length() == 1) return a == b;
    
    string a1 = a.substr(0,a.length()/2);
    string a2 = a.substr(a.length()/2);

    string b1 = b.substr(0,b.length()/2);
    string b2 = b.substr(b.length()/2);

    if(equivalente(a1,b1) && equivalente(a2,b2))
        return true;
    else if(equivalente(a1,b2) && equivalente(a2,b1))
        return true;
        
    return false;
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