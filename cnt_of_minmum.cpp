#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

class SGT {
public:
    vector<pair<int, int>> tree;
    SGT(int n) {
        tree.resize(4 * n + 7);
        for (int i = 0; i < 4 * n + 7; i++) {
            tree[i] = {INT_MAX, 0};  // Initialize with max value and count 0
        }
    }

    void build(int node, int low, int high, int a[]) {
        if (low == high) {
            tree[node] = {a[low], 1};
            return;
        }

        int mid = (low + high) >> 1;
        int lf = 2 * node;
        int rt = lf + 1;
        build(lf, low, mid, a);
        build(rt, mid + 1, high, a);
        
        tree[node].first = min(tree[lf].first, tree[rt].first);
        tree[node].second = 0;

        if (tree[node].first == tree[lf].first)
            tree[node].second += tree[lf].second;
        if (tree[node].first == tree[rt].first)
            tree[node].second += tree[rt].second;
    }

    pair<int, int> query(int node, int low, int high, int l, int r) {
        if (l <= low && high <= r)  // Complete overlap
            return tree[node];

        if (high < l || low > r)  // No overlap
            return {INT_MAX, 0};

        int mid = (low + high) >> 1;
        int lf = 2 * node;
        int rt = lf + 1;

        pair<int, int> left_part = query(lf, low, mid, l, r);
        pair<int, int> right_part = query(rt, mid + 1, high, l, r);

        pair<int, int> res;
        res.first = min(left_part.first, right_part.first);
        res.second = 0;

        if (res.first == left_part.first)
            res.second += left_part.second;
        if (res.first == right_part.first)
            res.second += right_part.second;

        return res;
    }

    void update(int node, int low, int high, int idx, int val) {
        if (low == high) {
            tree[node] = {val, 1};
            return;
        }

        int mid = (low + high) >> 1;
        int lf = 2 * node;
        int rt = lf + 1;

        if (idx <= mid)
            update(lf, low, mid, idx, val);
        else
            update(rt, mid + 1, high, idx, val);

        tree[node].first = min(tree[lf].first, tree[rt].first);
        tree[node].second = 0;

        if (tree[node].first == tree[lf].first)
            tree[node].second += tree[lf].second;
        if (tree[node].first == tree[rt].first)
            tree[node].second += tree[rt].second;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    int a[n + 1];
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    SGT obj(n);
    obj.build(1, 1, n, a);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int idx, val;
            cin >> idx >> val;
            obj.update(1, 1, n, idx+1, val);
        } else {
            int l, r;
            cin >> l >> r;
            l++;
            pair<int, int> ans = obj.query(1, 1, n, l, r);
            cout << ans.first << ' ' << ans.second << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
