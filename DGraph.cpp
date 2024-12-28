#include "iostream"
#include "vector"
#include "queue"
#include <limits>
using namespace std;

//Grafo dirigido con lista de adyacencia
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

//Implementacion de Grafo
class Dgraph {
    private:
        vector<vector<adjacency>> adjacencies;
        vector<edge> edges;
        int cant_nodes;    
    public:
        Dgraph(int n);   
        void addEdge(int src,int dst,int weight);
        int getCantNodes();
        vector<adjacency> getNeighborhood(int id);
        vector<edge> getEdges();
};

Dgraph::Dgraph(int n){
    adjacencies = vector<vector<adjacency>>(n, vector<adjacency> {});
    edges = {};
    cant_nodes = n;
}

int Dgraph::getCantNodes(){
    return cant_nodes;
}

vector<edge> Dgraph::getEdges(){
    return edges;
}

vector<adjacency> Dgraph::getNeighborhood(int id){
    return adjacencies[id];
}

void Dgraph::addEdge(int src, int dst,int weight){
    //Agrego (v,u)
    adjacencies[src].push_back({dst,weight});
    //Agrego la arista a la lista de aristas con su peso
    edges.push_back({src,dst,weight});
}

//Grafo dirigido con matriz de adyacencias
class dGrahpM {
    private:
        int nodes;
        vector<vector<int>> adjacencys;
        vector<edge> edges;
    public:
        dGrahpM(int n);
        void addEdge(int src,int dst,int weight);
        int getCantNodes();
        vector<adjacency> getNeighborhood(int id);
        vector<edge> getEdges(); 
};

dGrahpM::dGrahpM(int n) {
    nodes = n;
    adjacencys = vector<vector<int>>(n, vector<int>(n,0));
}

void dGrahpM::addEdge(int src,int dst,int weight){
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

struct priorityElem{
    int value;
    int priority;
};

class Compare {
    public:
        bool operator () (priorityElem a,priorityElem b){
            return a.priority > b.priority;
        }
};

vector<int> dijsktra(Dgraph g,int r){
    int n = g.getCantNodes();
    vector<int> distances(n,numeric_limits<int>::max());
    priority_queue<priorityElem,vector<priorityElem>,Compare> pq;
    vector<int> select_nodes(n,0);

    distances[r] = 0;
    pq.push({r,0});

    while( n > 0 || !pq.empty()){
        int w = pq.top().value;
        pq.pop();
        if( select_nodes[w]==0 ){
            n--;
            select_nodes[w] = 1;
            vector<adjacency> w_adj = g.getNeighborhood(w);

            for(size_t i = 0;  i < w_adj.size();i++ ){
                int u = w_adj[i].dst;
                int weight_w_u = w_adj[i].weight;
                if( select_nodes[u] == 0 && distances[u] > (distances[w] + weight_w_u) ){
                    distances[u] = distances[w] + weight_w_u;
                    pq.push({u,distances[u]});
                }    
            }
        }
    }

    return distances;
}

void printEdges(vector<edge> edges,vector<int> nodes){
    for (edge e: edges){
        cout<<"("<<nodes[e.src]<<" ,"<<nodes[e.dst]<<") W: "<<e.weight<<endl;   
    }
}

void printDistances(int v,vector<int> distances,vector<int> nodes){
    for (size_t i = 0; i < nodes.size(); i++) {
        cout<<"el camino minimo de "<<nodes[v]<<" a "<<nodes[i]<<" es "<<distances[i]<<endl;
    }
}

int main(){
    Dgraph g = {6};
    vector<int> nodes = {1,2,3,4,5,6};
    g.addEdge(0,1,4);
    g.addEdge(0,5,3);
    g.addEdge(0,2,7);
    g.addEdge(1,2,3);
    g.addEdge(1,4,1);
    g.addEdge(2,3,1);
    g.addEdge(2,4,1);
    g.addEdge(4,3,4);
    g.addEdge(5,4,3);

    printEdges(g.getEdges(),nodes);

    vector<int> r = dijsktra(g,0);
    printDistances(0,r,nodes);
    

    return 0;
}