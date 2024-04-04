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

int max_increasing = -1;
int max_decreasing = -1;

int max_width_subseq_inc(int i,int n,int subseq_width,int last){
    int aux = -1;
    if(i == n){
        return subseq_width;
    } else{
        if( buildings[i].second > last ){
             aux = max(max_width_subseq_inc(i+1,n,subseq_width + buildings[i].first,buildings[i].second) , max_width_subseq_inc(i+1,n,subseq_width,last));
        }
        return max(aux,max_width_subseq_inc(i+1,n,subseq_width,last));
    }
}

int max_width_subseq_dec(int i,int n,int subseq_width,int last){
    int aux = -1;
    if(i == -1){
        return subseq_width;
    } else{
        if( buildings[i].second < last ){
             aux = max(max_width_subseq_inc(i-1,n,subseq_width + buildings[i].first,buildings[i].second) , max_width_subseq_inc(i+1,n,subseq_width,last));
        }
        return max(aux,max_width_subseq_inc(i-1,n,subseq_width,last));
    }
}



int main(){
    buildings = case_1;
    int r = max_width_subseq_inc(0,buildings.size(),0,-1);
    cout<<r;
    r = max_width_subseq_dec(buildings.size()-1,buildings.size(),0,10000);
    cout<<r;
}