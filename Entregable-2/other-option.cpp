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

vector<building> buildings = {};

int max_increasing = -1;
int max_decreasing = -1;
vector<buildingSubseq> mem = {};

buildingSubseq max_inc(int i,int n){
    if(mem[i].last == -1 && mem[i].length ==-1){
        if( i == n-1){
            return mem[i] = {buildings[i].heigth, buildings[i].width};
        } else{
            buildingSubseq max = {-1,-1};
            for (int j = i; j < n-1; j++){
                buildingSubseq subseq = max_inc(j+1,n);
                if( buildings[i].heigth < subseq.last ){
                    
                    if( max.length < subseq.length + buildings[i].width )
                        max = {buildings[i].heigth, subseq.length + buildings[i].width};

                } else if( buildings[i].heigth > subseq.last){

                    if( buildings[i].width > subseq.length && buildings[i].width > max.length)
                        max = {buildings[i].heigth, buildings[i].width};
                    else if(buildings[i].width < subseq.length && subseq.length > max.length)
                        max = subseq;

                } else{

                    if( subseq.length > buildings[i].width && subseq.length > max.length )
                        max = subseq;
                    else if ( subseq.length < buildings[i].width && buildings[i].width > max.length)
                        max = {buildings[i].heigth, buildings[i].width};

                }
            }
            mem[i] = max;
        }
        return mem[i];
    }
    return mem[i];
}

buildingSubseq max_dec(int i,int n){
    if(mem[i].last == -1 && mem[i].length ==-1){
        if( i == n-1){
            return mem[i] = {buildings[i].heigth, buildings[i].width};
        } else{
            buildingSubseq max = {-1,-1};
            for (int j = i; j < n-1; j++){
                buildingSubseq subseq = max_dec(j+1,n);
                if( buildings[i].heigth > subseq.last ){
                    
                    if( max.length <= subseq.length + buildings[i].width )
                        max = {buildings[i].heigth, subseq.length + buildings[i].width};

                } else if( buildings[i].heigth < subseq.last){

                    if( buildings[i].width > subseq.length && buildings[i].width > max.length)
                        max = {buildings[i].heigth, buildings[i].width};
                    else if(buildings[i].width < subseq.length && subseq.length > max.length)
                        max = subseq;

                } else{

                    if( subseq.length > buildings[i].width && subseq.length > max.length )
                        max = subseq;
                    else if ( subseq.length < buildings[i].width && buildings[i].width > max.length)
                        max = {buildings[i].heigth, buildings[i].width};

                }
            }
            mem[i] = max;
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

        mem = vector<buildingSubseq>(buildings.size(),{-1,-1});
        max_increasing = max_inc(0,buildings.size()).length;

        mem = vector<buildingSubseq>(buildings.size(),{-1,-1});
        max_decreasing = max_dec(0,buildings.size()).length;
    
        if( max_increasing >= max_decreasing )
            cout<<"Case "<<(i+1)<<". Increasing ("<<max_increasing<<"). Decreasing ("<<max_decreasing<<")."<<endl;
        else cout<<"Case "<<(i+1)<<". Decreasing ("<<max_decreasing<<"). Increasing ("<<max_increasing<<")."<<endl;
    }
    
}