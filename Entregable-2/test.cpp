#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

vector<pair<int,int>> buildings = {};

//Funciona pero se excede en tiempo

int max_increasing = -1;
int max_decreasing = -1;

bool increasing(vector<pair<int,int>>& buildings_subseq){
    bool increase = true;    
    for (size_t i = 0; i < buildings_subseq.size()-1 && increase; i++){
        increase = buildings_subseq[i].second < buildings_subseq[i+1].second;
    }
    return increase;
}   

bool decreasing(vector<pair<int,int>>& buildings_subseq){
    bool decrease = true;    
    for (size_t i = 0; i < buildings_subseq.size()-1 && decrease; i++){
        decrease = buildings_subseq[i].second > buildings_subseq[i+1].second;
    }
    return decrease;
} 

void skylines(int i,int n,int subseq_width,vector<pair<int,int>>& buildings_subseq){
    if(i == n){
        if(increasing(buildings_subseq) && max_increasing < subseq_width) max_increasing = subseq_width;
        if(decreasing(buildings_subseq) && max_decreasing < subseq_width) max_decreasing = subseq_width;
    } else{
        buildings_subseq.push_back(buildings[i]);

        skylines(i+1,n,subseq_width + buildings[i].first ,buildings_subseq);

        buildings_subseq.pop_back();

        skylines(i+1,n,subseq_width,buildings_subseq);
    }
}

int main(){
    int t = 0;
    cin>>t;

    vector<vector<pair<int,int>>> cases(t,vector<pair<int,int>>(0));

    for (int i = 0; i < t; i++){
        int cant_of_buildings = 0;
        cin>>cant_of_buildings;

        buildings = vector<pair<int,int>>(cant_of_buildings,{0,0});

        for (int i = 0; i < cant_of_buildings; i++){
            int height = 0;
            cin>>height;
            buildings[i].second = height;
        }
        
        for (int i = 0; i < cant_of_buildings; i++){
            int width = 0;
            cin>>width;
            buildings[i].first = width;
        }

        cases[i] = buildings;
    }

    for (size_t i = 0; i < cases.size(); i++){
        buildings = cases[i];
        max_increasing = -1;
        max_decreasing = -1;

        vector<pair<int,int>> buildings_subseq = {};
        skylines(0,buildings.size(),0,buildings_subseq);

        if( max_increasing >= max_decreasing )
            cout<<"Case "<<(i+1)<<". Increasing ("<<max_increasing<<"). Decreasing ("<<max_decreasing<<")."<<endl;
        else cout<<"Case "<<(i+1)<<". Decreasing ("<<max_decreasing<<"). Increasing ("<<max_increasing<<")."<<endl;
    }
}