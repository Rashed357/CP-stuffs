#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Segment Tree (Range Add, Range Sum) - 1-based indexing
// - Build: O(n)
// - Range add / Range sum: O(log n) per operation (amortized)
// - Memory: O(4*n)

struct SegTree {
    int n;
    vector<ll> st;   // segment tree sums
    vector<ll> lazy; // pending add for each node

    SegTree(int _n = 0) { init(_n); }

    void init(int _n) {
        n = _n;
        if (n <= 0) return;
        st.assign(4*n + 5, 0);
        lazy.assign(4*n + 5, 0);
    }

    // build from 1-based array a (size should be n+1, a[1..n])
    void build(int node, int l, int r, const vector<ll> &a) {
        if (l == r) {
            st[node] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(node<<1, l, mid, a);
        build(node<<1|1, mid+1, r, a);
        st[node] = st[node<<1] + st[node<<1|1];
    }

    void build(const vector<ll> &a) {
        if ((int)a.size() == 0) return;
        // assume a is size n+1 and 1-based
        build(1, 1, n, a);
    }

    // push pending lazy value at node to children
    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;
        ll add = lazy[node];
        st[node] += add * (r - l + 1);
        if (l != r) {
            lazy[node<<1] += add;
            lazy[node<<1|1] += add;
        }
        lazy[node] = 0;
    }

    // range add: add 'val' to every element in [ql, qr]
    void update(int node, int l, int r, int ql, int qr, ll val) {
        push(node, l, r);
        if (qr < l || r < ql) return; // no overlap
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        update(node<<1, l, mid, ql, qr, val);
        update(node<<1|1, mid+1, r, ql, qr, val);
        st[node] = st[node<<1] + st[node<<1|1];
    }

    void range_add(int l, int r, ll val) {
        if (l > r) return;
        update(1, 1, n, l, r, val);
    }

    // range sum query on [ql, qr]
    ll query(int node, int l, int r, int ql, int qr) {
        push(node, l, r);
        if (qr < l || r < ql) return 0; // no overlap
        if (ql <= l && r <= qr) return st[node];
        int mid = (l + r) >> 1;
        return query(node<<1, l, mid, ql, qr) + query(node<<1|1, mid+1, r, ql, qr);
    }

    ll range_sum(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r);
    }
};

// Example usage (competitive programming style):
// Input:
// n
// a1 a2 ... an  (1-based reading; if you read 0-based, shift to 1-based)
// q
// queries (type l r [val])
// type 1: add val to [l, r]
// type 2: print sum on [l, r]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if (!(cin >> n)) return 0;
    vector<ll> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    SegTree st(n);
    st.build(a);

    int q; cin >> q;
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int l, r; ll val; cin >> l >> r >> val;
            // if input is 0-based, do l++, r++ here
            st.range_add(l, r, val);
        } else if (type == 2) {
            int l, r; cin >> l >> r;
            // if input is 0-based, do l++, r++ here
            cout << st.range_sum(l, r) << '\n';
        }
    }
    return 0;
}
