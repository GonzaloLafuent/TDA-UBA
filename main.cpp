#include "vector"
#include "iostream"
#include "queue"

using namespace std;

//Implementacion de Edge
template<typename p>
struct edge{
    int id_src;
    int id_dst;
    p weight;
};

//Implementacion de Grafo
template<typename p>
class Graph {
    private:
        vector<vector<edge<p>>> adjacencies;
        vector<edge<p>> edges;
        int cant_nodes;    
    public:
        Graph(int n);   
        void addEdge(int id_src,int id_dst,p weight);
        int getCantNodes();
        vector<edge<p>> getNeighborhood(int id);
        vector<edge<p>> getEdges();
};

template <typename p>
Graph<p>::Graph(int n){
    adjacencies = vector<vector<edge<p>>>(n,vector<edge<p>> {});
    edges = {};
    cant_nodes = n;
}

template <typename p>
int Graph<p>::getCantNodes(){
    return cant_nodes;
}

template <typename p>
vector<edge<p>> Graph<p>::getEdges(){
    return edges;
}

template<typename p>
vector<edge<p>> Graph<p>::getNeighborhood(int id){
    return adjacencies[id];
}

template <typename p>
void Graph<p>::addEdge(int id_src, int id_dst,p weight){
    edge<p> e1 = {id_src,id_dst,weight};
    edge<p> e2 = {id_dst,id_src,weight};
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
    return parent[v] == findSet(parent[v]);

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



template <typename p>
void printEdges(vector<edge<p>> edges,vector<string> nodes){
    for (edge<p> e: edges){
        cout<<"Src: "<<nodes[e.id_src]<<" Dst: "<<nodes[e.id_dst]<<" W: "<<e.weight<<endl;   
    }
}

template <typename p> 
void bfs(Graph<p> g,int root,vector<string> nodes){
    queue<int> a_visitar = {};
    vector<bool> visitados(g.getCantNodes(),false); 
    a_visitar.push(root);
    visitados[root] = true;

    while( !a_visitar.empty()){
        int actual = a_visitar.front();
        a_visitar.pop();
        cout<<nodes[actual]<<endl;
        for (edge<p> v: g.getNeighborhood(actual)){
            if( !visitados[v.id_dst] ){
                a_visitar.push(v.id_dst);
                visitados[v.id_dst] = true;
            }
        }
    }

}

int main(){
    vector<string> nodes = {"bs as","mdq","tandil","bahia"};
    Graph<int> g {4};
    g.addEdge(0,1,6);
    g.addEdge(0,3,12);
    g.addEdge(1,2,13);
    vector<edge<int>> edges = g.getEdges();
    printEdges(edges,nodes);

    bfs(g,0,nodes);

    return 0;
}