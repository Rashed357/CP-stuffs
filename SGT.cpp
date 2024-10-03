class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(2 * n); // Allocate space for the segment tree
        build(arr); // Build the tree
    }

    void build(vector<int>& arr) {
        // Initialize leaves with array elements
        for (int i = 0; i < n; i++) {
            tree[n + i] = arr[i];
        }
        // Build the tree by summing up children
        for (int i = n - 1; i > 0; i--) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    void update(int pos, int value) {
        pos += n; // Go to the leaf node
        tree[pos] = value; // Update the value
        // Update the parent nodes
        for (int i = pos / 2; i > 0; i /= 2) {
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
        }
    }

    int query(int left, int right) {
        int sum = 0;
        left += n;
        right += n + 1;
        while (left < right) {
            if (left % 2 == 1) {
                sum += tree[left++]; // If left is odd, add and move to the next
            }
            if (right % 2 == 1) {
                sum += tree[--right]; // If right is odd, move back and add
            }
            left /= 2;
            right /= 2; // Move to the parent nodes
        }
        return sum;
    }
};
