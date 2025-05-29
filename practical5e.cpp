#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node {
    int vertex;
    int cost;
    
    // priortizing nodes with lower heeuristic values
    bool operator<(const Node& other) const {
        return cost > other.cost;
    }
};

void beamSearch(vector<vector<int>>& graph, vector<int>& heuristic, int start, int goal, int beamWidth) {
    priority_queue<Node> pq;
    pq.push({start, heuristic[start]});
    
    vector<bool> visited(graph.size(), false);
    visited[start] = true;
    
    vector<int> order;  
    
    while (!pq.empty()) {
        // extract the best beamWidth nodes
        vector<Node> candidates;
        for (int i = 0; i < beamWidth && !pq.empty(); i++) {
            Node current = pq.top();
            pq.pop();
            candidates.push_back(current);
        }
        
        for (Node candidate : candidates) {
            int currentNode = candidate.vertex;
            order.push_back(currentNode);
            cout << "Expanding Node: " << (char)('A' + currentNode) << endl;
            
            if (currentNode == goal) {
                cout << "Goal Node " << (char)('A' + goal) << " found!" << endl;
                
                // output print
                cout << "Order of expansion: ";
                for (int i = 0; i < order.size(); i++) {
                    cout << (char)('A' + order[i]);
                    if (i != order.size() - 1) cout << " -> ";
                }
                cout << endl;
                return;
            }
            
            // explore neighbors
            for (int i = 0; i < graph[currentNode].size(); i++) {
                if (graph[currentNode][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    pq.push({i, heuristic[i]});
                }
            }
        }
    }
    cout << "Goal Node not found within the beam width." << endl;
}

int main() {
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
    
    // Heuristic values
    vector<int> heuristic = {15, 13, 13, 12, 10, 9, 7, 6, 5, 0};
    
    int startNode = 0; // Node A
    int goalNode = 9;  // Node J
    int beamWidth = 2; // Beam width
    
    beamSearch(graph, heuristic, startNode, goalNode, beamWidth);
    
    return 0;
}