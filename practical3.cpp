#include<iostream>
#include<vector>
using namespace std;

class Graph{
    int V;   // no. of vertices
    vector<vector<int>>adj; 

    public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int v, int depth);
    void iterativeDFS(int start);
};

Graph::Graph(int V){
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w); //adds w to v's list
}

void Graph::DFS(int v, int depth){
    if (depth == 0){
        return;  //Exit condition applied
    }
    cout << v << " ";   // printing of current node

    // recursion at all vertices
    for (int i : adj[v]){
        DFS(i, depth - 1);  // reduction of depth by 1
    }
}


void Graph::iterativeDFS(int start){
    for(int depth = 1; depth <=3; depth++){
        cout<< "DFS with depth "<< depth<<": ";

        DFS(start, depth);
        cout<<endl;
    }
}

int main(){
    int V,E;
    cout<<"Enter the number of nodes in the graph: ";
    cin>>V;

    Graph g(V);  //creates a graph with V nodes

    cout << "Enter number of edges: ";
    cin>>E;

    cout << "Enter edges:";
    for(int i = 0; i < E; i++){
        int from,to;
        cin>>from>>to;
        g.addEdge(from, to);
    }

    int startingNode;
    cout<<"Enter the starting node for DFS: ";
    cin>>startingNode;
    cout<<endl;


    g.iterativeDFS(startingNode);

    return 0;
}