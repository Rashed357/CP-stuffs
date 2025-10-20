#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Clean Segment Tree (Range Add, Range Sum)
// - 1-based indexing for array a[1..n]
// - Build: O(n)
// - Range add / Range sum: O(log n) per operation
// - Memory: O(4*n)

struct SegTree {
    int n;
    vector<ll> sum;   // segment sums
    vector<ll> lazy;  // pending add for each node

    // construct empty tree for size _n
    SegTree(int _n = 0) { init(_n); }

    void init(int _n) {
        n = max(0, _n);
        if (n == 0) return;
        sum.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }

    // build from 1-based array a of size n+1 (a[1]..a[n])
    void build(const vector<ll> &a) {
        if ((int)a.size() != n + 1) return; // guard
        build(1, 1, n, a);
    }

private:
    void build(int node, int L, int R, const vector<ll> &a) {
        if (L == R) {
            sum[node] = a[L];
            return;
        }
        int mid = (L + R) >> 1;
        build(node << 1, L, mid, a);
        build(node << 1 | 1, mid + 1, R, a);
        sum[node] = sum[node << 1] + sum[node << 1 | 1];
    }

    // apply pending value to node
    void apply(int node, int L, int R, ll val) {
        sum[node] += val * (R - L + 1);
        if (L != R) lazy[node << 1] += val, lazy[node << 1 | 1] += val;
    }

    // push lazy down
    void push(int node, int L, int R) {
        if (lazy[node] == 0) return;
        int mid = (L + R) >> 1;
        apply(node << 1, L, mid, lazy[node]);
        apply(node << 1 | 1, mid + 1, R, lazy[node]);
        lazy[node] = 0;
    }

    // update range [l,r] by adding val
    void update(int node, int L, int R, int l, int r, ll val) {
        if (r < L || R < l) return; // no overlap
        if (l <= L && R <= r) { apply(node, L, R, val); return; }
        push(node, L, R);
        int mid = (L + R) >> 1;
        update(node << 1, L, mid, l, r, val);
        update(node << 1 | 1, mid + 1, R, l, r, val);
        sum[node] = sum[node << 1] + sum[node << 1 | 1];
    }

    // query sum on [l,r]
    ll query(int node, int L, int R, int l, int r) {
        if (r < L || R < l) return 0; // no overlap
        if (l <= L && R <= r) return sum[node];
        push(node, L, R);
        int mid = (L + R) >> 1;
        return query(node << 1, L, mid, l, r) + query(node << 1 | 1, mid + 1, R, l, r);
    }

public:
    // public wrappers (1-based indices)
    void range_add(int l, int r, ll val) {
        if (l > r) return;
        update(1, 1, n, l, r, val);
    }

    ll range_sum(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

// ------------------- Example usage -------------------
// Input format (typical CP):
// n
// a1 a2 ... an   (space separated)
// q
// q lines: either
// 1 l r val   --> add val to a[l..r]
// 2 l r       --> print sum of a[l..r]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    SegTree st(n);
    st.build(a);

    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r; ll v; cin >> l >> r >> v;
            // if input is 0-based, do: ++l; ++r;
            st.range_add(l, r, v);
        } else {
            int l, r; cin >> l >> r;
            // if input is 0-based, do: ++l; ++r;
            cout << st.range_sum(l, r) << '
';
        }
    }
    return 0;
}
