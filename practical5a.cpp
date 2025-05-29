#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void DFS(int start, vector<vector<int>>&graph, vector<bool> &visited ){
stack<int> s;
s.push(start);
bool firstNode = true;

while(!s.empty()){
    int node = s.top();
    s.pop();
    if (!visited[node]) {
            if (firstNode) {
                cout << char(node + 'A');
                firstNode = false;
            } else {
                cout << "->" << char(node + 'A');
            }
            visited[node] = true;
        }
        for (int i = graph[node].size() - 1; i >= 0; i--) {
            if (graph[node][i] != 0 && !visited[i]) {
                s.push(i);
            }
        }
    }
}

int main(){
    vector<vector<int>> graph = {
        {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},     //A
        {6, 0, 2, 6, 3, 4, 0, 0, 0, 0},     //B
        {3, 2, 0, 0, 4, 5, 0, 0, 0, 0},     //C
        {1, 6, 0, 0, 7, 8, 9, 0, 0, 0},     //D
        {0, 3, 4, 7, 0, 6, 9, 9, 0, 0},     //E
        {0, 4, 5, 8, 6, 0, 8, 9, 0, 0},     //F
        {0, 0, 0, 9, 9, 8, 0, 11, 12, 14},  //G
        {0, 0, 0, 0, 9, 9, 11, 0, 14, 15},  //H
        {0, 0, 0, 0, 0, 0, 12, 14, 0, 0},  //I
        {0, 0, 0, 0, 0, 0, 14, 15, 0, 0},  //J
    };

    vector<bool> visited(10,false);

    cout<<"DFS Traversal: ";
    DFS(0,graph, visited);
    cout<<endl;

    return 0;
}