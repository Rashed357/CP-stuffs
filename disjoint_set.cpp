class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Initialize each node as its own parent
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX; // Attach smaller tree under larger tree
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++; // Increment rank if both trees have the same rank
            }
        }
    }
};
