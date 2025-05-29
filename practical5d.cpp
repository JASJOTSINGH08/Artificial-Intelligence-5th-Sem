#include<iostream>
#include<queue>
#include<vector>

using namespace std;

void BFS(int startNode, vector<vector<int>>&adjMatrix, int numNodes){
    vector<bool>visited(numNodes,false);  // to track visited nodes
    queue<int>q;  // queue for bfs
    vector<int> order;

    visited[startNode] = true;
    q.push(startNode);

    while(!q.empty()){
        int currentNode = q.front();
        q.pop();
        order.push_back(currentNode);  // store current node

        // exploring other neighbours
        for(int i = 0; i < numNodes; i++){
            if(adjMatrix[currentNode][i] != 0 && !visited[i]){
                visited[i] = true;
                q.push(i);
            }
        }
    }

    for (int i = 0; i < order.size(); i++) {
        cout << static_cast<char>('A' + order[i]);
        if (i != order.size() - 1) {  
            cout << " -> ";
        }
    }
    cout << endl;  
}

int main(){
    int numNodes = 10;  

    vector<vector<int>> adjMatrix = {
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

    cout<<"BFS: ";
    BFS(0, adjMatrix, numNodes);

    return 0;
}