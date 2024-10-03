// Application: Topological sorting is used in scheduling tasks, course prerequisites, etc.
vector<int> topologicalSort(int n, vector<vector<int>>& graph) {
    vector<int> inDegree(n, 0);
    vector<int> topoOrder;
    queue<int> q;

    // Compute in-degrees of all nodes
    for (int i = 0; i < n; i++) {
        for (int neighbor : graph[i]) {
            inDegree[neighbor]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) q.push(i); // Nodes with zero in-degree
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);

        for (int neighbor : graph[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) q.push(neighbor);
        }
    }

    if (topoOrder.size() != n) return {}; // Graph has a cycle
    return topoOrder;
}
