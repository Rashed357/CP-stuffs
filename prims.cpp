// Application: Prim's Algorithm is used to find the Minimum Spanning Tree (MST) in a weighted graph.
int primMST(vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> key(n, INT_MAX);  // Minimum weight edge to each vertex
    vector<bool> inMST(n, false); // Track vertices included in MST
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0});  // {weight, vertex}

    int mst_weight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        mst_weight += key[u];

        for (auto& [v, weight] : graph[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    return mst_weight;
}
