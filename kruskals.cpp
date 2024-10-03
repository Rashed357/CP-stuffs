// Application: Kruskal's Algorithm is used to find the Minimum Spanning Tree (MST) in a weighted graph using a union-find data structure.
class KruskalMST {
public:
    int n;
    vector<vector<int>> edges;

    KruskalMST(int n) : n(n) {}

    void addEdge(int u, int v, int weight) {
        edges.push_back({weight, u, v});
    }

    int find(vector<int>& parent, int u) {
        if (parent[u] != u) {
            parent[u] = find(parent, parent[u]);
        }
        return parent[u];
    }

    void unite(vector<int>& parent, vector<int>& rank, int u, int v) {
        int rootU = find(parent, u);
        int rootV = find(parent, v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

    int kruskalMST() {
        vector<int> parent(n), rank(n, 0);
        iota(parent.begin(), parent.end(), 0);

        sort(edges.begin(), edges.end());

        int mst_weight = 0;
        for (auto& edge : edges) {
            int u = edge[1], v = edge[2], weight = edge[0];
            if (find(parent, u) != find(parent, v)) {
                mst_weight += weight;
                unite(parent, rank, u, v);
            }
        }

        return mst_weight;
    }
};
