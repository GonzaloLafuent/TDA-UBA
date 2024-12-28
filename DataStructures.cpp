#include "vector"
#include "iostream"
#include "queue"
#include "algorithm"
#include <limits>

using namespace std;

//Implementacion de Edge
struct edge{
    int id_src;
    int id_dst;
    int weight;
};

//Implementacion de Grafo
class Graph {
    private:
        vector<vector<edge>> adjacencies;
        vector<edge> edges;
        int cant_nodes;    
    public:
        Graph(int n);   
        void addEdge(int id_src,int id_dst,int weight);
        int getCantNodes();
        vector<edge> getNeighborhood(int id);
        vector<edge> getEdges();
};

Graph::Graph(int n){
    adjacencies = vector<vector<edge>>(n, vector<edge> {});
    edges = {};
    cant_nodes = n;
}

int Graph::getCantNodes(){
    return cant_nodes;
}

vector<edge> Graph::getEdges(){
    return edges;
}

vector<edge> Graph::getNeighborhood(int id){
    return adjacencies[id];
}

void Graph::addEdge(int id_src, int id_dst,int weight){
    edge e1 = {id_src,id_dst,weight};
    edge e2 = {id_dst,id_src,weight};
    adjacencies[id_src].push_back(e1);
    adjacencies[id_dst].push_back(e2);
    edges.push_back(e1);
}

//Implementacion de djsoint-set
class DsjointSet{
    private:
        vector<int> parent;
        vector<int> size;
    public:
        DsjointSet(int n);
        void makeSet(int v);
        int findSet(int v);
        void unionSet(int v,int w);
};

DsjointSet::DsjointSet(int n){
    parent = vector<int>(n,-1);
    size = vector<int>(n,-1);
}

void DsjointSet::makeSet(int v){
    parent[v] = v;
    size[v] = 1;
}

int DsjointSet::findSet(int v){
    if(v == parent[v])
        return v;
    int result = findSet(parent[v]);  
    parent[v] = result;  
    return result; 

}

void DsjointSet::unionSet(int v,int w){
    v = findSet(v);
    w = findSet(w);
    if (v != w) {
        if (size[v] < size[w])
            swap(v, w);
        parent[v] = w;
        size[v] += size[w];
    }     
}

//Kruskal
bool compareEdge(edge x,edge y){
    return x.weight < y.weight;
}

vector<edge> kruskal(Graph g){
    DsjointSet set {g.getCantNodes()};
    vector<edge> a = {};
    for(int i=0; i<g.getCantNodes(); i++){
        set.makeSet(i);
    }
    vector<edge> edges = g.getEdges();
    sort(edges.begin(),edges.end(),compareEdge);

    for(edge e:edges){
        int u = e.id_src;
        int v = e.id_dst;
        if(set.findSet(u)!=set.findSet(v)){
            a.push_back(e);
            set.unionSet(u,v);
        }
    }
    
    return a;
}

//Implemenetacion de prim
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

class PriorityQueue{
    private:
        vector<priorityElem> q;
    public:

};

vector<edge> prim(Graph g,int r){
    int n = g.getCantNodes();
    vector<edge> result = {}; 
    priority_queue<priorityElem,vector<priorityElem>,Compare> pq;

    //Mantengo los pesos de cada vertice
    vector<int> weights(n,numeric_limits<int>::max());

    //Mantengo los padres de cade vertice
    vector<int> parents(n,0);

    //Mantengo los vertices que voy agregando al AGM
    vector<int> agm(n,0);
    pq.push({r,0});

    while(!pq.empty()){
        priorityElem u = pq.top();
        pq.pop();
        
        if(agm[u.value]==0){
            agm[u.value] = 1;
            if(u.value != r) result.push_back({parents[u.value],u.value,u.priority});
            for(edge e: g.getNeighborhood(u.value)){
                if( agm[e.id_dst] == 0 && e.weight < weights[e.id_dst] ){
                    weights[e.id_dst] = e.weight;
                    pq.push({e.id_dst,e.weight});
                    parents[e.id_dst] = u.value;
                }
            }
        }
    }    

    return result; 
}


//Metodos auxiliares
void printEdges(vector<edge> edges,vector<string> nodes){
    for (edge e: edges){
        cout<<"("<<nodes[e.id_src]<<" ,"<<nodes[e.id_dst]<<") W: "<<e.weight<<endl;   
    }
}

//Recorrido por bfs 
void bfs(Graph g,int root,vector<string> nodes){
    queue<int> a_visitar = {};
    vector<bool> visitados(g.getCantNodes(),false); 
    a_visitar.push(root);
    visitados[root] = true;

    while( !a_visitar.empty()){
        int actual = a_visitar.front();
        a_visitar.pop();
        cout<<nodes[actual]<<endl;
        for (edge v: g.getNeighborhood(actual)){
            if( !visitados[v.id_dst] ){
                a_visitar.push(v.id_dst);
                visitados[v.id_dst] = true;
            }
        }
    }

}

int main(){

    vector<string> nodes = {"a","b","c","d","e","f","g","h","i"};
    Graph g {9};
    vector<edge> edges = {};
    vector<edge> a = {};
    /*
    g.addEdge(0,1,4);
    g.addEdge(0,7,8);
    g.addEdge(1,7,12);
    g.addEdge(1,2,8);
    g.addEdge(2,8,3);
    g.addEdge(2,5,4);
    g.addEdge(2,3,6);
    g.addEdge(3,4,9);
    g.addEdge(3,5,13);
    g.addEdge(4,5,10);
    g.addEdge(5,6,3);
    g.addEdge(6,7,1);
    g.addEdge(6,8,5);
    g.addEdge(7,8,6);

    cout<<"GRAFO G: "<<endl;
    edges = g.getEdges();
    sort(edges.begin(),edges.end(),compareEdge);
    printEdges(edges,nodes);

    a =  kruskal(g);

    cout<<""<<endl;
    cout<<"AGM DE GRAGO G CON KRUSKAL: "<<endl;
    printEdges(a,nodes);
    cout<<""<<endl;

    a = prim(g,0);

    cout<<"AGM DE GRAGO G CON PRIM: "<<endl;
    printEdges(a,nodes);
    cout<<""<<endl;
    */
    Graph g1 {12};
    vector<string> nodes1 = {"1","2","3","4","5","6","7","8","9","10","11","12"};
    g1.addEdge(0,1,10);
    g1.addEdge(0,7,11);
    g1.addEdge(0,10,9);
    g1.addEdge(0,11,12);
    g1.addEdge(1,7,8);
    g1.addEdge(1,2,8);
    g1.addEdge(2,11,10);
    g1.addEdge(2,6,8);
    g1.addEdge(2,3,6);
    g1.addEdge(3,4,10);
    g1.addEdge(3,5,7);
    g1.addEdge(4,6,5);
    g1.addEdge(4,5,7);
    g1.addEdge(5,9,6);
    g1.addEdge(5,8,13);
    g1.addEdge(6,7,8);
    g1.addEdge(6,9,5);
    g1.addEdge(7,8,9);
    g1.addEdge(9,10,11);
    g1.addEdge(10,11,8);

    cout<<"GRAGO G1: "<<endl;
    edges = g1.getEdges();
    sort(edges.begin(),edges.end(),compareEdge);
    printEdges(edges,nodes1);

    a =  kruskal(g1);

    cout<<""<<endl;
    cout<<"AGM DE GRAFO G1 CON KRUSKAL: "<<endl;
    printEdges(a,nodes1);
   
    a = prim(g1,0);

    cout<<"AGM DE GRAFO G1 CON PRIM: "<<endl;
    printEdges(a,nodes1);
    cout<<""<<endl;


    return 0;
}