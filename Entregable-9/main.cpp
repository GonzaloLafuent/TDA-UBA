#include "iostream"
#include "queue"
#include "algorithm"
#include <limits>

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

//Implementacion de Grafo
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

//Printear aristas del grafo
void printEdges(vector<edge> edges,vector<int> nodes){
    for (edge e: edges){
        cout<<"("<<nodes[e.src]<<" ,"<<nodes[e.dst]<<") W: "<<e.weight<<endl;   
    }
}

//Elemento de cola de prioridad
struct priorityElem{
    int value;
    int priority;
};

//Comparador de prioridades
class Compare {
    public:
        bool operator () (priorityElem a,priorityElem b){
            return a.priority > b.priority;
        }
};

//Construyo la cantidad minima de rolls en base a prim
int minRolls(Graph g,int r){
    int minRolls = 0;
    int n = g.getCantNodes(); 
    priority_queue<priorityElem,vector<priorityElem>,Compare> pq;

    //Mantengo los pesos de cada vertice
    vector<int> weights(n,numeric_limits<int>::max());

    //Mantengo los padres de cade vertice
    vector<int> parents(n,0);

    //Mantengo los vertices que voy agregando al AGM
    vector<int> agm(n,0);
    //Agrego la raiz
    pq.push({r,0});

    //Itero hasta que desencole todos las aritas de la cola, o hasta haber agregado
    //todos los nodos al arbol
    while(!pq.empty() && n>=0){
        priorityElem u = pq.top();
        pq.pop();

        if(agm[u.value]==0){
            n--;
            agm[u.value] = 1;
            minRolls+= u.priority;
            int v = u.value;
            for(adjacency a: g.getNeighborhood(v)){
                int w = a.dst;
                int new_weight_vw = a.weight;
                if( agm[w] == 0 && new_weight_vw < weights[w] ){
                    weights[a.dst] = new_weight_vw;
                    pq.push({w,new_weight_vw});
                    parents[w] = v;
                }
            }
        }
    }    

    return minRolls; 
}

//Calculo de peso de los nodos
int weight(int v,int w){
    int rolls = 0;
    for(int i=0; i <4; i++){
        int d1 = v % 10, d2 = w % 10;
        int max_d = max(d1,d2);
        int min_d = min(d1,d2);
        rolls += min(max_d-min_d,(min_d-max_d)+10); 
        v = v/10, w = w/10;
    }  
    return rolls;
}

vector<int> keys_nodes = {};

int main(){
    int cant_tests = 0;
    cin>>cant_tests;

    for (int test = 0; test < cant_tests; test++){
        int cant_keys = 0;
        cin>>cant_keys;

        keys_nodes = {};
        keys_nodes.push_back(0);

        for (int keys = 0; keys < cant_keys; keys++) {
            int key = 0;
            cin>>key;
            keys_nodes.push_back(key);
        }

        Graph g {(int) keys_nodes.size()}; 

        int min_weight_0 = -1;
        int adjs_0 = -1;

        for(size_t i = 0; i < keys_nodes.size(); i++){
            for(size_t j = i+1; j< keys_nodes.size(); j++){
                int weight_v_w = weight(keys_nodes[i],keys_nodes[j]);
                if( i==0 ){
                    if( weight_v_w < min_weight_0 || min_weight_0 ==-1){
                        min_weight_0 = weight_v_w;
                        adjs_0 = j;
                    }    
                } else g.addEdge(i,j,weight_v_w);
            }
            if(i==0) g.addEdge(0,adjs_0,min_weight_0);
             
        }
        cout<<minRolls(g,0)<<endl;    
    }
    return 0;
}