#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <chrono>
#include <thread>
#include <limits>

using namespace std;
using namespace std::chrono;

vector<pair<int,int>> case_1 = {
    {50,10},
    {10,100},
    {10,50},
    {15,30},
    {20,80},
    {10,10}
};

vector<pair<int,int>> case_2 = {
    {20,30},
    {30,20},
    {40,20},
    {50,10}
};

vector<pair<int,int>> case_3 = {
    {15,80},
    {25,80},
    {20,80},
};

//building = (width,height)
vector<pair<int,int>> buildings = {};

int max_increasing = -1;
int max_decreasing = -1;

int max_width_subseq_inc(int i,int n,int subseq_width,int last){
    int aux = -1;
    if(i == n){
        return subseq_width;
    } else{
        if( buildings[i].second > last ){
             aux = max_width_subseq_inc(i+1,n,subseq_width + buildings[i].first,buildings[i].second);
        }
        return max(aux,max_width_subseq_inc(i+1,n,subseq_width,last));
    }
}

int max_width_subseq_dec(int i,int n,int subseq_width,int last){
    int aux = -1;
    if(i == n){
        return subseq_width;
    } else{
        if( buildings[i].second < last ){
             aux = max_width_subseq_dec(i+1,n,subseq_width + buildings[i].first,buildings[i].second);
        }
        return max(aux,max_width_subseq_dec(i+1,n,subseq_width,last));
    }
}

int main(){
    /*
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

        max_increasing = max_width_subseq_inc(0,buildings.size(),0,-1);
        //max_decreasing = max_width_subseq_dec(0,buildings.size(),0,1000000);
    
        if( max_increasing >= max_decreasing )
            cout<<"Case "<<(i+1)<<". Increasing ("<<max_increasing<<"). Decreasing ("<<max_decreasing<<")."<<endl;
        else cout<<"Case "<<(i+1)<<". Decreasing ("<<max_decreasing<<"). Increasing ("<<max_increasing<<")."<<endl;
    }
    */

   buildings = case_1;

    max_increasing = max_width_subseq_inc(0,buildings.size(),0,-1);
    max_decreasing = max_width_subseq_dec(0,buildings.size(),0,1000000);

    if( max_increasing >= max_decreasing )
            cout<<"Case "<<(1)<<". Increasing ("<<max_increasing<<"). Decreasing ("<<max_decreasing<<")."<<endl;
        else cout<<"Case "<<(1)<<". Decreasing ("<<max_decreasing<<"). Increasing ("<<max_increasing<<")."<<endl;
}