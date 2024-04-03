#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

using namespace std;

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