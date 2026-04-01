#include <bits/stdc++.h>
using namespace std;

/*
    Sparse Table

    Supports:
    1. Range Minimum Query (RMQ)
    2. Can be modified for Range Maximum, GCD, OR etc.
    3. Only works on static arrays (no updates efficiently)

    Time Complexity:
    - Build: O(n * log n)
    - Query: O(1)
*/

struct SparseTable {
    int n;
    vector<int> log2;
    vector<vector<int>> st;

    // Initialize with array a
    SparseTable(const vector<int> &a) {
        n = a.size();
        int K = 32 - __builtin_clz(n); // max log
        st.assign(n, vector<int>(K + 1));
        log2.assign(n + 1, 0);

        // Precompute logs
        for (int i = 2; i <= n; i++)
            log2[i] = log2[i / 2] + 1;

        // Initialize 0th column (interval of length 1)
        for (int i = 0; i < n; i++)
            st[i][0] = a[i];

        // Build Sparse Table
        for (int j = 1; j <= K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Query min in range [l, r]
    int query(int l, int r) {
        int j = log2[r - l + 1];
        return min(st[l][j], st[r - (1 << j) + 1][j]);
    }
};

int main() {
    vector<int> a = {5, 2, 4, 7, 1, 3, 6};
    SparseTable st(a);

    cout << st.query(1, 4) << "\n"; // min from index 1 to 4 -> 1
    cout << st.query(0, 2) << "\n"; // min from index 0 to 2 -> 2
}
