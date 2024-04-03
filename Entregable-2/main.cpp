#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

//building = (width,height)
vector<pair<int,int>> buildings = {
    {50,10},
    {10,100},
    {10,50},
    {15,30},
    {20,80},
    {10,10}
};

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
        else if(decreasing(buildings_subseq) && max_decreasing < subseq_width) max_decreasing = subseq_width;
    } else{
        buildings_subseq.push_back(buildings[i]);

        skylines(i+1,n,subseq_width + buildings[i].first ,buildings_subseq);

        buildings_subseq.pop_back();

        skylines(i+1,n,subseq_width,buildings_subseq);
    }
}

int main(){
    /*
    int t = 0;
    cin>>t;

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

    }

    for (size_t i = 0; i < buildings.size(); i++)
    {
        cout<<buildings[i].first<<" "<<buildings[i].second<<endl;
    }
    */
    vector<pair<int,int>> buildings_subseq = {};
    skylines(0,buildings.size(),0,buildings_subseq);
    
    cout<<max_increasing;
    cout<<max_decreasing;
}