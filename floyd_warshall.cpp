// Application: Floyd-Warshall is used to find shortest paths between all pairs of nodes in a weighted graph.
void floydWarshall(vector<vector<int>>& dist) {
    int n = dist.size();

    // Update the distances using each node as an intermediate node
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}
