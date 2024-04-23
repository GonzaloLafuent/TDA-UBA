#include <iostream>
#include <vector>
using namespace std;

vector<int> ciudad = {};

int gergovia(){
    int esfuerzo = 0;
    for (size_t i = 0; i < ciudad.size()-1; i++){
        esfuerzo += abs(ciudad[i]);
        ciudad[i+1] += ciudad[i];
    }
    return esfuerzo;
}


int main(){
    int n = -1;
    cin>>n;
    
    while(n != 0){
        vector<int> test = {};

        for (int i = 0; i < n; i++){
            int vino = 0;
            cin>>vino;
            test.push_back(vino);
        }
        ciudad = test;
        cout<<gergovia()<<endl;

        cin>>n;
    }

    return 0;
}