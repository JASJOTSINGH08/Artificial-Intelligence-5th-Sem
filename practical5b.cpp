#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

// Function to perform Best First Search
void bestFirstSearch(vector<vector<int>> &graph, int start, int goal){
    int n = graph.size();
    vector<bool> visited(n, false);
    priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>>pq;
    string order = "";

    // Push start node to priority queue
    pq.push({0, start});
    visited[start] = true;

    while(!pq.empty()){
        int current_cost = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        if (order.empty()){
            order += char(current_node + 'A');
        }
        else{
            order += "->" + string(1,char(current_node + 'A'));
        }

        cout << "Visiting node: "<< char(current_node + 'A') <<" with current cost: " << current_cost << endl;

        // If the goal is reached
        if(current_node == goal){
            cout << "Goal node " << char(goal + 'A') << " reached with cost: "<< current_cost<<endl;
            cout << "Order Followed: "<< order << endl;
            return;
    }

    for(int neighbor = 0; neighbor < n; neighbor++){
        if(graph[current_node][neighbor] != 0 && !visited[neighbor]){
            pq.push({graph[current_node][neighbor],neighbor});
            visited[neighbor] = true;
        }
    }
}

    cout<<"Goal node not reachable from the start node." << endl;
    cout << "Order Followed: "<< order << endl;
}

int main() {
    // Graph represented as an adjacency matrix (using g values from the image)
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


    int start = 0;  // Start node 'A'
    int goal = 9;   // Goal node 'J'

    bestFirstSearch(graph, start, goal);

    return 0;
}
