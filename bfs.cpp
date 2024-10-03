void bfs(int start, vector<vector<int>>& graph) {
    vector<bool> visited(graph.size(), false); // Initialize visited array
    queue<int> q; // Use a queue for BFS
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // Process the node (can be any operation)
        cout << "Visited " << node << endl;

        // Traverse all adjacent nodes
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) { // Visit unvisited neighbors
                visited[neighbor] = true;
                q.push(neighbor); // Add neighbor to queue
            }
        }
    }
}
