#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<ll>

const int N = 1e5 + 5;
ll tree[4 * N], lazy[4 * N];
int n;

// Build the tree from the initial array
void build(int node, int l, int r, const vi &arr) {
    if (l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid, arr);
    build(2 * node + 1, mid + 1, r, arr);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Propagate pending updates
void propagate(int node, int l, int r) {
    if (lazy[node] != 0) {
        tree[node] += (r - l + 1) * lazy[node]; // apply pending update
        if (l != r) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

// Range update: add val to all elements in [ql, qr]
void update(int node, int l, int r, int ql, int qr, ll val) {
    propagate(node, l, r);
    if (qr < l || r < ql) return; // no overlap
    if (ql <= l && r <= qr) { // total overlap
        lazy[node] += val;
        propagate(node, l, r);
        return;
    }

    int mid = (l + r) / 2;
    update(2 * node, l, mid, ql, qr, val);
    update(2 * node + 1, mid + 1, r, ql, qr, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

// Range query: sum of elements in [ql, qr]
ll query(int node, int l, int r, int ql, int qr) {
    propagate(node, l, r);
    if (qr < l || r < ql) return 0; // no overlap
    if (ql <= l && r <= qr) return tree[node]; // total overlap

    int mid = (l + r) / 2;
    return query(2 * node, l, mid, ql, qr) +
           query(2 * node + 1, mid + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vi arr(n + 1); // 1-based indexing

    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    build(1, 1, n, arr);

    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << '\n';
        } else if (type == 2) {
            int l, r;
            ll val;
            cin >> l >> r >> val;
            update(1, 1, n, l, r, val);
        }
    }

    return 0;
}
