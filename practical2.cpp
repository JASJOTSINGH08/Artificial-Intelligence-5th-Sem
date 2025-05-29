#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

//fnc for width at level for bfs traversing all nodes 
int widthAtLevel(const vector<vector<int>>& graph, int w){
    int n = graph.size();
    int max_width = 0;
    
    for (int i =0 ; i< n; i++){
        vector<bool>visited(n,false);
        queue<pair<int,int>>q; // pair bnega for (node,level)
        vector <int> level_count(n,0);

        visited[i] = true;
        q.push({i,0});

        while(!q.empty()){
            int node = q.front().first;
            int level = q.front().second;
            q.pop();
            level_count[level]++;

            for (int j=0; j<n;j++){
                if (graph[node][j]==1 && !visited[j]){
                    visited[j] = true;
                    q.push({j,level+1});
                }
            }
        }

        int currentMaxWidth = *max_element(level_count.begin(),level_count.begin()+w);
    }
    return max_width;
}

//fnc for degree calculation for node
int calculateWidthNode(const vector<vector<int>>& graph, int w){
    int max_width = 0;
    int n = graph.size();

    for (int i =0; i<n ; i++ ){
        int node_degree = 0;

        for (int j=0; j<n; j++){
            node_degree+=graph[i][j];
        }

        int current_width = min(node_degree, w);
        max_width = max(max_width, current_width);
    }
    return max_width;
}

int main(){
     vector<vector<int>> graph_10 = {
        {0, 1, 1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0}
    };

    // Sample 12 Node Graph
    vector<vector<int>> graph_12 = {
        {0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}
    };

    // Test with different width values w
    cout << "Width at Level Wl for w=1 (Graph 10): " << widthAtLevel(graph_10, 1) << endl;
    cout << "Width for Node Wn for w=1 (Graph 10): " << calculateWidthNode(graph_10, 1) << endl;
    cout << "Width at Level Wl for w=2 (Graph 10): " << widthAtLevel(graph_10, 2) << endl;
    cout << "Width for Node Wn for w=2 (Graph 10): " << calculateWidthNode(graph_10, 2) << endl;
    cout << "Width at Level Wl for w=3 (Graph 10): " << widthAtLevel(graph_10, 3) << endl;
    cout << "Width for Node Wn for w=3 (Graph 10): " << calculateWidthNode(graph_10, 3) << endl;

    cout << "Width at Level Wl for w=1 (Graph 12): " << widthAtLevel(graph_12, 1) << endl;
    cout << "Width for Node Wn for w=1 (Graph 12): " << calculateWidthNode(graph_12, 1) << endl;
    cout << "Width at Level Wl for w=2 (Graph 12): " << widthAtLevel(graph_12, 2) << endl;
    cout << "Width for Node Wn for w=2 (Graph 12): " << calculateWidthNode(graph_12, 2) << endl;
    cout << "Width at Level Wl for w=3 (Graph 12): " << widthAtLevel(graph_12, 3) << endl;
    cout << "Width for Node Wn for w=3 (Graph 12): " << calculateWidthNode(graph_12, 3) << endl;

    return 0;
}