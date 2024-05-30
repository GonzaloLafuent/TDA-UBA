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

//Representamos un piso con el numero de y en que ascensor estamos en ese piso
struct floor{
    int floor_numb;
    int elevator_cost;
};

//Ponemos aca que nodo representa cada piso al ir agregandolo
vector<int> id_node_floors(99,-1);

vector<int> t = {10,50,100};
vector<int> t1 = {0,10,30,40};
vector<int> t2 = {0,20,30};
vector<int> t3 = {0,20,50};

vector<floor> nodes = {
        {-1,-1},
        {0,0},
        {0,1},
        {0,2},
        {10,0},
        {20,1},
        {20,2},
        {30,0},
        {30,1},
        {50,2},
};

int time(int src,int dst){
    return (nodes[src].floor_numb!=nodes[dst].floor_numb)? t[nodes[src].elevator_cost]*(nodes[dst].floor_numb - nodes[src].floor_numb): 60;
}

void printEdges(vector<edge> edges,vector<floor> n){
    for (edge e: edges) {
        cout<<"voy de "<<n[e.src].floor_numb<<" a "<<n[e.dst].floor_numb<<" con un costo de "<<e.weight<<endl;
    }
}

void printNeighborhood(int src,vector<adjacency> neigh,vector<floor> n){
    cout<<"los vecinos de "<<nodes[src].floor_numb<<" son ";
    for(adjacency a: neigh)
        cout<<n[a.dst].floor_numb <<" con peso "<< a.weight<<", ";
    cout<<endl;
}

int main(){
    int n = 3;
    int k = 50;

    Dgraph g = {(int)(t1.size()+t2.size()+t3.size()+1)};
    
    g.addEdge(0,1,0);
    g.addEdge(0,2,0);
    g.addEdge(0,3,0);
    g.addEdge(1,4,time(1,4));
    g.addEdge(2,5,time(2,5));
    g.addEdge(3,6,time(3,6));
    g.addEdge(4,7,time(4,7));
    g.addEdge(5,8,time(5,8));
    g.addEdge(5,6,time(5,6));
    g.addEdge(6,5,time(6,5));
    g.addEdge(7,8,time(7,8));
    g.addEdge(8,7,time(8,7));
    g.addEdge(6,9,time(6,9));

    printEdges(g.getEdges(),nodes);
    cout<<endl;

    for (size_t i = 0; i < nodes.size(); i++){
        printNeighborhood(i,g.getNeighborhood(i),nodes);
    }
    

    return 0;
}