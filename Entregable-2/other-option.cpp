#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <chrono>
#include <thread>
#include <limits>

using namespace std;
using namespace std::chrono;

struct building{
    int width;
    int heigth;
};

struct buildingSubseq{
    int last;
    int length;
};

vector<building> case_1 = {
    {50,10},
    {10,100},
    {10,50},
    {15,30},
    {20,80},
    {10,10}
};

vector<building> case_2 = {
    {20,30},
    {30,20},
    {40,20},
    {50,10}
};

vector<building> case_3 = {
    {15,80},
    {25,80},
    {20,80},
};


vector<building> buildings = {};

int max_increasing = -1;
int max_decreasing = -1;
vector<int> mem = {};

int max_inc(int i,int n){
    if(mem[i] ==-1){
        if( i == n-1){
            return mem[i] = buildings[i].width;
        } else{
            int max = -1;
            for (int j = i+1; j < n; j++){
                //subsecuencia que contiene a elmento j
                int sub_seq_width = max_inc(j,n);
                if( buildings[i].heigth < buildings[j].heigth){
                    if(max < buildings[i].width + sub_seq_width)
                        max = buildings[i].width + sub_seq_width;
                } else max = max{buildings[i],sub_seq_width}
                    
            }
            if(max == -1) max = buildings[i].width;
            mem[i] = max; 
        }
        return mem[i];
    }
    return mem[i];
}

int max_dec(int i,int n){
    if(mem[i] ==-1){
        if( i == n-1){
            return mem[i] = buildings[i].width;
        } else{
            int max = buildings[i].width;
            for (int j = i+1; j < n; j++){
                //subsecuencia que contiene a elmento j
                int sub_seq_width = max_dec(j,n);
                if( buildings[i].heigth > buildings[j].heigth){
                    if(max < buildings[i].width + sub_seq_width)
                        max = buildings[i].width + sub_seq_width;
                } if( buildings[i].heigth == buildings[j].heigth ){
                    if(buildings[i].width > mem[j] && buildings[i].width > max)
                        max = buildings[i].width;
                    else if(buildings[i].width < mem[j] && mem[j] > max)
                        max = mem[j];    
                }
            }
            mem[i] = max; 
        }
        return mem[i];
    }
    return mem[i];
}

int main(){
    /*
    int t = 0;
    cin>>t;

    vector<vector<building>> cases(t,vector<building>(0));

    for (int i = 0; i < t; i++){
        int cant_of_buildings = 0;
        cin>>cant_of_buildings;

        buildings = vector<building>(cant_of_buildings,{0,0});

        for (int i = 0; i < cant_of_buildings; i++){
            int height = 0;
            cin>>height;
            buildings[i].heigth = height;
        }
        
        for (int i = 0; i < cant_of_buildings; i++){
            int width = 0;
            cin>>width;
            buildings[i].width = width;
        }

        cases[i] = buildings;
    }

    for (size_t i = 0; i < cases.size(); i++){
        buildings = cases[i];
        max_increasing = -1;
        max_decreasing = -1;

        mem = vector<buildingSubseq>(buildings.size(),{-1,-1});
        max_increasing = max_inc(0,buildings.size()).length;

        mem = vector<buildingSubseq>(buildings.size(),{-1,-1});
        max_decreasing = max_dec(0,buildings.size()).length;
    
        if( max_increasing >= max_decreasing )
            cout<<"Case "<<(i+1)<<". Increasing ("<<max_increasing<<"). Decreasing ("<<max_decreasing<<")."<<endl;
        else cout<<"Case "<<(i+1)<<". Decreasing ("<<max_decreasing<<"). Increasing ("<<max_increasing<<")."<<endl;
    }
    */

    buildings = case_2;
    mem = vector<int>(buildings.size(),-1);
    int max = max_inc(0,buildings.size());
    cout<<max<<endl;
    mem = vector<int>(buildings.size(),-1);
    max = max_dec(0,buildings.size());
    cout<<max<<endl;
    return 0;
}