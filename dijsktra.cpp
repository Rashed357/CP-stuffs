vector<int> dijkstra(int start, vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX); // Initialize distances with infinity
    dist[start] = 0; // The distance to the start node is 0

    // Min-heap to prioritize the node with the smallest distance
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        // Skip if we already have a better distance
        if (d > dist[u]) continue;

        // Traverse all adjacent nodes
        for (auto edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relax the edge if a shorter path is found
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v}); // Add the neighbor to the priority queue
            }
        }
    }

    return dist; // Return the shortest distances from the start node
}
