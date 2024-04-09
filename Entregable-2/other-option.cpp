#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <chrono>
#include <thread>
#include <limits>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct building{
    int width;
    int heigth;
};

vector<building> buildings = {};

int max_increasing = -1;
int max_decreasing = -1;
vector<int> mem = {};

int max_inc(int i,int n){
    if(mem[i] ==-1){
        if( i == n-1){
            max_increasing = buildings[i].width; 
            return mem[i] = buildings[i].width;
        } else{
            int max_width = buildings[i].width;
            for (int j = i+1; j < n; j++){
                //subsecuencia que contiene a elmento j
                int sub_seq_width = max_inc(j,n);
                if( buildings[i].heigth < buildings[j].heigth){
                    if(max_width < buildings[i].width + sub_seq_width)
                        max_width = buildings[i].width + sub_seq_width;
                } 
            }
            max_increasing = (max_width > max_increasing)? max_width : max_increasing;
            mem[i] = max_width; 
        }
        return mem[i];
    }
    return mem[i];
}

int max_dec(int i,int n){
    if(mem[i] ==-1){
        if( i == n-1){
            max_decreasing = buildings[i].width;
            return mem[i] = buildings[i].width;
        } else{
            int max_width = buildings[i].width;
            for (int j = i+1; j < n; j++){
                //subsecuencia que contiene a elmento j
                int sub_seq_width = max_dec(j,n);
                if( buildings[i].heigth > buildings[j].heigth){
                    if(max_width < buildings[i].width + sub_seq_width)
                        max_width = buildings[i].width + sub_seq_width;
                } 
            }
            max_decreasing = (max_width > max_decreasing)? max_width : max_decreasing;
            mem[i] = max_width; 
        }
        return mem[i];
    }
    return mem[i];
}

int main(){
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

       mem = vector<int>(buildings.size(),-1);
       max_inc(0,buildings.size());
       mem = vector<int>(buildings.size(),-1);
       max_dec(0,buildings.size());
    
        if( max_increasing >= max_decreasing )
            cout<<"Case "<<(i+1)<<". Increasing ("<<max_increasing<<"). Decreasing ("<<max_decreasing<<")."<<endl;
        else cout<<"Case "<<(i+1)<<". Decreasing ("<<max_decreasing<<"). Increasing ("<<max_increasing<<")."<<endl;
    }

}