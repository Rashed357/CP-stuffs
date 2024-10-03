// Application: Bellman-Ford is used to find the shortest paths from a single source to all other nodes in a graph with possible negative weights.
vector<int> bellmanFord(int n, vector<vector<int>>& edges, int start) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    // Relax all edges n-1 times
    for (int i = 0; i < n - 1; i++) {
        for (auto edge : edges) {
            int u = edge[0], v = edge[1], weight = edge[2];
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (auto edge : edges) {
        int u = edge[0], v = edge[1], weight = edge[2];
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains a negative-weight cycle" << endl;
            return {};
        }
    }

    return dist;
}
