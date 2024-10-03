// Application: Fenwick Tree is used for efficient range queries and point updates in logarithmic time.
class FenwickTree {
public:
    vector<int> tree;
    int n;

    FenwickTree(int size) : n(size) {
        tree.resize(n + 1, 0);
    }

    // Add value to element at index i
    void update(int i, int delta) {
        while (i <= n) {
            tree[i] += delta;
            i += i & -i;
        }
    }

    // Get prefix sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & -i;
        }
        return sum;
    }

    // Get sum in range [left, right]
    int rangeQuery(int left, int right) {
        return query(right) - query(left - 1);
    }
};
