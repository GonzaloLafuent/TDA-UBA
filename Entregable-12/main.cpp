#include "iostream"
#include "vector"
#include <limits>
#include <bits/stdc++.h>
using namespace std;

//Estructura de adyacencia
struct adjacency{
    int dst;
    int weight;
};

//Estructra de arista
struct edge{
    int src;
    int dst;
    int weight;
};

class dGrahpM {
    private:
        int nodes;
        vector<vector<int>> adjacencys;
        vector<edge> edges;
        int weight_sum;
    public:
        dGrahpM(int n);
        void addEdge(int src,int dst,int weight);
        int getCantNodes();
        vector<adjacency> getNeighborhood(int id);
        vector<edge> getEdges();
        vector<vector<int>> getDistances();
        int getWeightSum();
};

dGrahpM::dGrahpM(int n) {
    nodes = n;
    adjacencys = vector<vector<int>>(n, vector<int>(n,numeric_limits<int>::max()));
}

void dGrahpM::addEdge(int src,int dst,int weight){
    adjacencys[src][dst] = weight; 
    edges.push_back({src,dst,weight});
    weight_sum += weight;
} 

int dGrahpM::getWeightSum(){
    return weight_sum;
}

int dGrahpM::getCantNodes(){
    return nodes;
}

vector<adjacency> dGrahpM::getNeighborhood(int id){
    vector<adjacency> neighborhood = {};
    for (size_t i = 0; i < adjacencys[id].size(); i++){
        int weight_src_dst = adjacencys[id][i];
        if(weight_src_dst > 0)
            neighborhood.push_back({(int) i,weight_src_dst});
    }
    return neighborhood;
}

vector<edge> dGrahpM::getEdges(){
    return edges;
}

vector<vector<int>> dGrahpM::getDistances(){
    return adjacencys;
}

vector<int> attacked = {};

int attackCost(dGrahpM& g,vector<int>& attack){
    int n = g.getCantNodes();
    vector<vector<int>> distances = g.getDistances();
    int infinite = numeric_limits<int>::max();
    reverse(attack.begin(),attack.end());
    int sum = 0;

    for (int k: attack){
        attacked[k] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n ; j++){
                int distance_i_k_j = (distances[i][k] != infinite)? (distances[k][j]!= infinite)? distances[i][k] + distances[k][j]: infinite : infinite;
                distances[i][j] = min(distances[i][j],distance_i_k_j);
                sum += (attacked[i]!=0 && attacked[j]!= 0 ) ? distances[i][j]: 0;
            }
        }
    }

    return sum;
}

int main(){
    int cant_test = 0;
    cin>>cant_test;
    for (int test = 0; test < cant_test; test++){
        int cant_towers = 0;
        cin>>cant_towers;
        dGrahpM g {cant_towers};
        attacked = vector<int>(cant_towers,0);
        vector<int> attack_estrategy = {};

        for (int tower_v = 0; tower_v < cant_towers; tower_v++){
            for (int tower_u = 0; tower_u < cant_towers; tower_u++){
                int cost_communication = 0;
                cin>>cost_communication;
                g.addEdge(tower_v,tower_u,cost_communication);
            }   
        }
        
        for(int estrategy = 0; estrategy < cant_towers; estrategy++){
            int attack = 0; 
            cin>>attack;
            attack_estrategy.push_back(attack);
        }    

        cout<<attackCost(g,attack_estrategy)<<endl;

    }
    
    return 0;
}