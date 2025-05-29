#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Graph represented as an adjacency matrix
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

// Function to perform Depth-Limited Search (DLS)
bool DLS(char current, char goal, int limit, int cost, vector<char>& path) {
    path.push_back(current);

    if (current == goal) {
        cout << "Goal found: " << current << " with cost " << cost << endl;
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
        return true;
    }
    if (limit <= 0) {
        path.pop_back();
        return false;
    }

    int nodeIndex = current - 'A';

    // priortizing the nodes
    vector<pair<int, int>> neighbors;
    for (int i = 0; i < graph[nodeIndex].size(); i++) {
        if (graph[nodeIndex][i] > 0) {
            neighbors.push_back({graph[nodeIndex][i], i});
        }
    }

    // sorting neighbors based on their cost or priority
    sort(neighbors.begin(), neighbors.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;  // lower cost first
    });

    for (auto neighbor : neighbors) {
        char nextNode = 'A' + neighbor.second;
        int nextCost = cost + neighbor.first;
        if (DLS(nextNode, goal, limit - 1, nextCost, path))
            return true;
    }

    path.pop_back(); // backtracking if not found
    return false;
}

// Function to perform Iterative Deepening Best Node First
void iterativeDeepnBestFirst(char start, char goal) {
    int depth = 0;
    while (true) {
        cout << "Depth limit: " << depth << endl;
        vector<char> path;  // reset path for each depth limit
        if (DLS(start, goal, depth, 0, path)) {
            break;
        }
        depth++;
    }
}

int main() {
    char start = 'A';  // Start node
    char goal = 'J';   // Goal node

    iterativeDeepnBestFirst(start, goal);

    return 0;
}
