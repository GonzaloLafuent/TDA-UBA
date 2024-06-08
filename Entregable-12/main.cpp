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
    long weight;
};

class dGrahpM {
    private:
        int nodes;
        vector<vector<long>> adjacencys;
        vector<edge> edges;
    public:
        dGrahpM(int n);
        void addEdge(int src,int dst,long weight);
        int getCantNodes();
        vector<adjacency> getNeighborhood(int id);
        vector<edge> getEdges();
        vector<vector<long>> getDistances();
};

dGrahpM::dGrahpM(int n) {
    nodes = n;
    adjacencys = vector<vector<long>>(n, vector<long>(n,0));
}

void dGrahpM::addEdge(int src,int dst,long weight){
    adjacencys[src][dst] = weight; 
    edges.push_back({src,dst,weight});
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

vector<vector<long>> dGrahpM::getDistances(){
    return adjacencys;
}

vector<int> attacked = {};
vector<int> estrategy = {};

int attackCost(dGrahpM g){
    int n = g.getCantNodes();
    vector<vector<long>> distances = g.getDistances();
    reverse(estrategy.begin(),estrategy.end());
    long sum = 0;

    for (int k: estrategy){
        attacked[k] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n ; j++){
                distances[i][j] = min(distances[i][j],distances[i][k]+ distances[k][j]);
                if( attacked[i] == 1 && attacked[j] == 1 )
                    sum += distances[i][j];
            }
        }
    }

    return sum;
}

int main(){
    int cant_test = 0;
    cin>>cant_test;
    
    for(int test = 0; test < cant_test; test++){
        int n = 0;
        cin>>n;

        dGrahpM g {n};
        attacked = vector<int>(n,0);
        estrategy = vector<int>(n,0);

        for(int u = 0; u < n; u++){
            for(int v = 0; v < n; v++){
                int cost = 0;
                cin>>cost;
                g.addEdge(u,v,cost);
            }    
        }

        for(int v = 0; v<n ; v++){
            cin>>estrategy[v];
        }

        cout<<attackCost(g)<<endl;
    
    return 0;
}