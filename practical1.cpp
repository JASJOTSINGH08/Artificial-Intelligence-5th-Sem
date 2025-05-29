#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

//func prt for bfs
vector <int> bfs(const vector <vector <int>>& list, int start){
    vector <int> visited(list.size(), 0);
    vector<int> series;
    queue<int> q;

    q.push(start);
    visited[start] = 1;

    while (!q.empty()){
        int node = q.front();
        q.pop();
        series.push_back(node);

    for (int neighbour : list[node]){
        if (visited[neighbour] == 0){
            visited[neighbour] = 1;
            q.push(neighbour);
    }
  }
}
  return series;
}

//func prt for dfs
vector <int> dfs(const vector <vector<int>>& list, int start){
    vector <int> visited(list.size(), 0);
    vector<int> series;
    stack<int>s;

    s.push(start);

    while(!s.empty()){
        int node = s.top();
        s.pop();

        if (visited[node])
        continue;

        visited[node]= 1;
        series.push_back(node);

        for ( int neighbour : list[node]){
            if(!visited[neighbour]){
                s.push(neighbour);
            }
        }
    } 
    return series;
}


int main(){
    int nodes;
    cout<<"Enter number of nodes in graph (nearly 8 - 10): ";
    cin >> nodes;

    vector<vector<int>>list(nodes);

    cout<<"Enter the edges (e.g., 0 1 for an edge between node 0 and 1):\n";
    int u,v;
    while ( cin>> u >> v){
        list[u].push_back(v);
        list[v].push_back(u);
        if(cin.peek() =='\n') 
        break; // rokne ke liye
    }

    int startNode;
    cout<<"Enter the starting node: ";
    cin>>startNode;

    cout<<"Choose search method ( Either (1)bfs or (2)dfs ) :";
    int choice;
    cin >> choice;

    vector<int>series;

    if (choice == 1) {
        series = bfs(list, startNode);
    }
    else if (choice == 2){
        series = dfs(list, startNode);
    }
    else {
        cout<<"Inavlid Choice!"<< endl;
        return 1;
    }

    cout << "Visited Nodes : ";
    for(int node : series){
        cout << node << " ";
    }
    cout << endl;

}