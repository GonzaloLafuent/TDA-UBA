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

//Implemetatcion de grafo dirigido
class Graph {
    private:
        vector<vector<adjacency>> adjacencies;
        vector<edge> edges;
        int cant_nodes;    
    public:
        Graph(int n);   
        void addEdge(int src,int dst,int weight);
        int getCantNodes();
        vector<adjacency> getNeighborhood(int id);
        vector<edge> getEdges();
};

Graph::Graph(int n){
    adjacencies = vector<vector<adjacency>>(n, vector<adjacency> {});
    edges = {};
    cant_nodes = n;
}

int Graph::getCantNodes(){
    return cant_nodes;
}

vector<edge> Graph::getEdges(){
    return edges;
}

vector<adjacency> Graph::getNeighborhood(int id){
    return adjacencies[id];
}

void Graph::addEdge(int src, int dst,int weight){
    //Agrego (v,u)
    adjacencies[src].push_back({dst,weight});
    //Agrego (u,v)
    adjacencies[dst].push_back({src,weight});
    //Agrego la arista a la lista de aristas con su peso
    edges.push_back({src,dst,weight});
}

//Ponemos aca que nodo representa cada piso al ir agregandolo
//Representamos un piso con el numero de y en que ascensor estamos en ese piso
struct floor{
    int floor_numb;
    int elevator_cost;
};

vector<vector<int>> id_node_floors = {};

vector<int> times = {};

vector<floor> nodes = {};

int k_min_distance = numeric_limits<int>::max();

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

void dijsktra(Graph g,int r,int cant_nodes,int k){
    int n = cant_nodes;
    vector<int> distances(n,numeric_limits<int>::max());
    priority_queue<priorityElem,vector<priorityElem>,Compare> pq;
    vector<int> select_nodes(n,0);

    distances[r] = 0;
    pq.push({r,0});

    while( n>0 && !pq.empty()){
        int w = pq.top().value;
        pq.pop();
        if( n > 0 &&select_nodes[w]==0 ){
            n--;
            select_nodes[w] = 1;
            vector<adjacency> w_adj = g.getNeighborhood(w);

            for(size_t i = 0;  i < w_adj.size();i++ ){
                int u = w_adj[i].dst;
                int weight_w_u = w_adj[i].weight;
                if( select_nodes[u] == 0 && distances[u] > (distances[w] + weight_w_u) ){
                    distances[u] = distances[w] + weight_w_u;
                    k_min_distance = (nodes[u].floor_numb==k && distances[u] < k_min_distance)? distances[u]: k_min_distance;
                    pq.push({u,distances[u]});
                }    
            }
        }
    }
}

void another_elev_in_floor(int f,int node_id,Graph& g){
    if( f!= 0){
        if( id_node_floors[f].size() == 0 ){
            id_node_floors[f].push_back(node_id);
        } else {
            for(int n: id_node_floors[f]){
                g.addEdge(n,node_id,60);    
            }
            id_node_floors[f].push_back(node_id);
        }    
    }
}

int time(int src,int dst){
    int floor_dst = nodes[dst].floor_numb;
    int floor_src = nodes[src].floor_numb;
    int floor_cost = nodes[src].elevator_cost;
    return (floor_src==-1)? 0 :(floor_dst!=floor_src)? times[floor_cost]*(abs(floor_dst-floor_src)): 60;
}

int main(){
    int n = 0;
    int k = 0;

    while(cin >> n >> k){
        Graph g {500};
        times = vector<int>(n,0);
        nodes = {{-1,-1}};
        id_node_floors = vector<vector<int>>(100,vector<int> {});
        k_min_distance = numeric_limits<int>::max();
        bool is_k = false;

        for(int elevs = 0; elevs < n; elevs++){
            int time_elevs = 0;
            cin>>time_elevs;
            times[elevs] = time_elevs;
        }

        int node_id = 0;
        for(int j = 0; j < n; j++){
            string line = "";
            if(j==0) getline(cin,line);
            getline(cin,line);
            stringstream stream(line);
            int f1 = -1;
            int f2 = -1;
            while(stream) {
                    
                stream >> f2;
                is_k = (f2==k)? true: is_k;

                if(f1 != f2 ){
                    if( f2 != 0 && f1 == -1) {                        
                        nodes.push_back({f2,j});
                        node_id++;
                        if(stream){
                            another_elev_in_floor(f2,node_id,g);
                            f1 = f2;                        
                        } else another_elev_in_floor(f2,node_id,g);
                    } else { 
                        nodes.push_back({f2,j});
                        int old_node_id = node_id;
                        node_id++;
                        g.addEdge((f2==0)?0:old_node_id, node_id ,time((f2==0)?0:old_node_id,node_id));
                        another_elev_in_floor(f2,node_id,g);
                        f1 = f2;
                    } 
                }
            }
        } 

        string result = "";
        if(k != 0) {
            dijsktra(g,0, (int)nodes.size(),k);
            stringstream ss;
            ss << k_min_distance;
            result = (!is_k || k_min_distance== numeric_limits<int>::max())? "IMPOSSIBLE":ss.str();
            cout<<result<<endl;
        } else cout<<"0"<<endl;
    }

    return 0;
}