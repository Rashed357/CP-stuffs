void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true; // Mark the node as visited
    
    // Process the node (can be any operation, like printing the node value)
    cout << "Visited " << node << endl;
    
    // Traverse through all adjacent nodes
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) { // If the neighbor has not been visited
            dfs(neighbor, graph, visited); // Recur for the neighbor
        }
    }
}
