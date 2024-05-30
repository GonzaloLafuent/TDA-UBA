#include "iostream"
#include "vector"
#include "queue"
#include <limits>
#include "queue"
#include <sstream>
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
vector<int> id_node_floors(100,-1);

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
        {40,0},
        {50,2},
};

int time(int src,int dst){
    int floor_dst = nodes[dst].floor_numb;
    int floor_src = nodes[src].floor_numb;
    int floor_cost = nodes[src].elevator_cost;
    return (floor_src==-1)? 0 :(floor_dst!=floor_src)? t[floor_cost]*(abs(floor_dst-floor_src)): 60;
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

void printDistances(int v,vector<int> distances,vector<floor> nodes){
    for (size_t i = 0; i < nodes.size(); i++) {
        cout<<"el camino minimo de "<<nodes[v].floor_numb<<" a "<<nodes[i].floor_numb<<" es "<<distances[i]<<endl;
    }
}

int main(){
    int n = 0;
    int k = 0;
    int i = 0;
    while(cin >> n >> k && i==0){
        Dgraph g {100};
        cout<<n<<" "<<k<<endl;
        for(int elevs = 0; elevs < n; elevs++){
            int time_elevs = 0;
            cin>>time_elevs;
            cout<<time_elevs<<endl;
            t.push_back(time_elevs);
        }
        for(int j = 0; j < n; j++){
            string line = "";
            getline(cin,line);
            getline(cin,line);
            stringstream stream(line);
            int f1; stream >> f1;
            int nodes_id = 0;
            while(stream) {
                int f2;
                stream >> f2;
                nodes.push_back({f1,i});
                if( id_node_floors[f1] == -1) id_node_floors[f1] = nodes_id;
                else{
                    g.addEdge(nodes_id,id_node_floors[f1],time(nodes_id,id_node_floors[f1]));
                    g.addEdge(id_node_floors[f1],nodes_id,time(nodes_id,id_node_floors[f1]));
                    id_node_floors[f1] = nodes_id;
                }
                nodes_id++;
                nodes.push_back({f2,i});
                if( id_node_floors[f2] == -1) id_node_floors[f2] = nodes_id;
                else{
                    g.addEdge(nodes_id,id_node_floors[f2],time(nodes_id,id_node_floors[f2]));
                    g.addEdge(id_node_floors[f2],nodes_id,time(nodes_id,id_node_floors[f2]));
                    id_node_floors[f2] = nodes_id;
                }
                nodes_id++;                 
                f1 = f2;
            }
        }    
    }
    /*
    int n = 3;
    int k = 50;

    Dgraph g = {(int)nodes.size()};
    
    g.addEdge(0,1,0);
    g.addEdge(0,2,0);
    g.addEdge(0,3,0);
    g.addEdge(1,4,time(1,4));
    g.addEdge(4,1,time(4,1));
    g.addEdge(2,5,time(2,5));
    g.addEdge(5,2,time(5,2));
    g.addEdge(3,6,time(3,6));
    g.addEdge(6,3,time(6,3));
    g.addEdge(4,7,time(4,7));
    g.addEdge(7,4,time(7,4));
    g.addEdge(5,8,time(5,8));
    g.addEdge(8,5,time(8,5));
    g.addEdge(5,6,time(5,6));
    g.addEdge(6,5,time(6,5));
    g.addEdge(7,8,time(7,8));
    g.addEdge(8,7,time(8,7));
    g.addEdge(7,9,time(7,9));
    g.addEdge(9,7,time(7,9));
    g.addEdge(6,10,time(6,10));
    g.addEdge(10,6,time(10,6));

    printEdges(g.getEdges(),nodes);
    cout<<endl;

    for (size_t i = 0; i < nodes.size(); i++){
        printNeighborhood(i,g.getNeighborhood(i),nodes);
    }

    vector<int> r = dijsktra(g,0);
    printDistances(0,r,nodes);
    */
    return 0;
}