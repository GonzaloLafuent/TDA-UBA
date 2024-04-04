#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

//building = (width,height)
vector<pair<int,int>> buildings = {};

int max_increasing = -1;
int max_decreasing = -1;

void skylines(int i,int n,bool inc,bool dec,int subseq_width,vector<pair<int,int>>& buildings_subseq){
    if(i == n){
        if(buildings_subseq.size()==1 || inc)
            max_increasing = (subseq_width > max_increasing)?subseq_width: max_increasing; 
        if(buildings_subseq.size() ==1 || dec)
            max_decreasing = (subseq_width > max_decreasing)?subseq_width: max_decreasing;
    } else if( buildings_subseq.size() == 1){
        if( buildings[i].second > buildings_subseq.back().second ){
            //Si el proximo elemento es mayor en altura, estimo que va ser creciente
            buildings_subseq.push_back(buildings[i]);
            skylines(i+1,n,true,false,subseq_width + buildings[i].first ,buildings_subseq);

            buildings_subseq.pop_back(); 

            skylines(i+1,n,false,false,subseq_width,buildings_subseq);
        } else if( buildings[i].second < buildings_subseq.back().second){
            //Si el proximo elemnto es menor en altura, estimo que va a ser menor
            buildings_subseq.push_back(buildings[i]);
            skylines(i+1,n,false,true,subseq_width + buildings[i].first ,buildings_subseq);
            buildings_subseq.pop_back();

            skylines(i+1,n,false,false,subseq_width,buildings_subseq);
        } 
        skylines(i+1,n,false,false,subseq_width,buildings_subseq);
    } else if( buildings_subseq.size() > 1){
        if(inc && buildings[i].second > buildings_subseq.back().second){
            buildings_subseq.push_back(buildings[i]);
            skylines(i+1,n,true,false,subseq_width + buildings[i].first ,buildings_subseq);
            buildings_subseq.pop_back();
        } else if( dec && buildings[i].second < buildings_subseq.back().second ) {
            buildings_subseq.push_back(buildings[i]);
            skylines(i+1,n,false,true,subseq_width + buildings[i].first ,buildings_subseq);
            buildings_subseq.pop_back();
        }
        skylines(i+1,n,inc,dec,subseq_width,buildings_subseq);
    } else if(buildings_subseq.size()==0){
        buildings_subseq.push_back(buildings[i]);

        skylines(i+1,n,false,false,subseq_width + buildings[i].first ,buildings_subseq);

        buildings_subseq.pop_back();

        skylines(i+1,n,false,false,subseq_width,buildings_subseq);
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
        auto start = high_resolution_clock::now();
        skylines(0,buildings.size(),false,false,0,buildings_subseq);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        if( max_increasing >= max_decreasing )
            cout<<"Case "<<(i+1)<<". Increasing ("<<max_increasing<<"). Decreasing ("<<max_decreasing<<")."<<endl;
        else cout<<"Case "<<(i+1)<<". Decreasing ("<<max_decreasing<<"). Increasing ("<<max_increasing<<")."<<endl;

        cout <<"Time: "<<duration.count() << endl;
    }

}