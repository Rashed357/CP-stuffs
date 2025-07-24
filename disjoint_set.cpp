struct DSU {
    vector<int> parent, size;

    // Constructor
    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1); // Initially, size of each set is 1
        for (int i = 1; i <= n; ++i) {
            parent[i] = i; // Initially, each node is its own parent
        }
    }

    // Find with path compression
    int find(int v) {
        if (parent[v] == v)
            return v;
        return parent[v] = find(parent[v]);
    }

    // Union by size
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b); // Make sure a has bigger size
            parent[b] = a;
            size[a] += size[b];
        }
    }

    // Check if two nodes are in same component
    bool same(int a, int b) {
        return find(a) == find(b);
    }

    // Get size of the component of a node
    int getSize(int v) {
        return size[find(v)];
    }
};
