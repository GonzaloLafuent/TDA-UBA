/*
void printDistances(int v,vector<int> distances,vector<floor> nodes){
    for (size_t i = 0; i < nodes.size(); i++) {
        if(distances[i] == 499 ) cout<<"fhjkdsfjkhsdjkfd";
        cout<<"el camino minimo de "<<nodes[v].floor_numb<<" a "<<nodes[i].floor_numb<<" es "<<distances[i]<<endl;
    }
}

void printEdges(vector<edge> edges,vector<floor> n){
    for (edge e: edges) {
        int elev = (e.weight==60)? -1: n[e.src].elevator_cost;
        int src_numb = n[e.src].floor_numb; int dst_numb = n[e.dst].floor_numb;
        int src_elev = n[e.src].elevator_cost; int dst_elev = n[e.dst].elevator_cost;
        if(src_numb == dst_numb ) cout <<"puedo cambiar de ascensor en piso "<<src_numb<<" Desde ascensor "<<src_elev<<" a "<<dst_elev<<endl;
        else cout<<"voy de "<<src_numb<<" a "<<dst_numb<<" con un costo de "<<e.weight<<" Por el ascensor: "<<elev<<endl;
    }
}

void printNeighborhood(int src,vector<adjacency> neigh,vector<floor> n){
    cout<<"los vecinos de "<<nodes[src].floor_numb<<" son ";
    for(adjacency a: neigh)
        cout<<n[a.dst].floor_numb <<" con peso "<< a.weight<<", ";
    cout<<endl;
}
*/

/*
    int n = 3;
    int k = 50;

    Graph g = {(int) nodes.size()};
    g.addEdge(0,1,0);
    g.addEdge(0,2,0);
    g.addEdge(0,3,0);
    g.addEdge(1,4,time(1,4));
    g.addEdge(2,5,time(2,5));
    g.addEdge(3,6,time(3,6));
    g.addEdge(4,7,time(4,7));
    g.addEdge(5,8,time(5,8));
    g.addEdge(5,6,time(5,6));
    g.addEdge(7,8,time(7,8));
    g.addEdge(7,9,time(7,9));
    g.addEdge(6,10,time(6,10));

    
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
