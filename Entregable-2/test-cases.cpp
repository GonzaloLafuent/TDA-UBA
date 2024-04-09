#include <iostream>
#include <vector>
#include <utility>

using namespace std;

struct building{
    int width;
    int heigth;
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


vector<pair<int,int>> buildings = {};

//Otra opcion que se me paso del tiempo
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
