#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct HeavyLightDecomposition {

    // =========================================================
    // SEGMENT TREE + LAZY PROPAGATION
    // =========================================================
    struct SegTree {

        struct Node {
            long long sum = 0;
            long long mx = LLONG_MIN;
            long long mn = LLONG_MAX;

            long long lazyAdd = 0;
            long long lazySet = 0;
            bool hasSet = false;
        };

        int n;
        vector<Node> st;

        SegTree(int n = 0) {
            this->n = n;
            st.resize(4 * n + 5);
        }

        // -----------------------------------------------------
        // APPLY ASSIGNMENT
        // Set every value in [l,r] = val
        // -----------------------------------------------------
        void applySet(int p, int l, int r, long long val) {

            st[p].sum = (r - l + 1) * val;
            st[p].mx = val;
            st[p].mn = val;

            st[p].lazySet = val;
            st[p].lazyAdd = 0;
            st[p].hasSet = true;
        }

        // -----------------------------------------------------
        // APPLY ADDITION
        // Add val to every value in [l,r]
        // -----------------------------------------------------
        void applyAdd(int p, int l, int r, long long val) {

            st[p].sum += (r - l + 1) * val;
            st[p].mx += val;
            st[p].mn += val;

            if(st[p].hasSet)
                st[p].lazySet += val;
            else
                st[p].lazyAdd += val;
        }

        // -----------------------------------------------------
        // PUSH LAZY
        // -----------------------------------------------------
        void push(int p, int l, int r) {

            if(l == r) {
                st[p].lazyAdd = 0;
                st[p].hasSet = false;
                return;
            }

            int m = (l + r) / 2;

            // First push assignment
            if(st[p].hasSet) {

                applySet(p * 2, l, m, st[p].lazySet);
                applySet(p * 2 + 1, m + 1, r, st[p].lazySet);

                st[p].hasSet = false;
            }

            // Then push addition
            if(st[p].lazyAdd != 0) {

                applyAdd(p * 2, l, m, st[p].lazyAdd);
                applyAdd(p * 2 + 1, m + 1, r, st[p].lazyAdd);

                st[p].lazyAdd = 0;
            }
        }

        // -----------------------------------------------------
        // PULL
        // -----------------------------------------------------
        void pull(int p) {

            st[p].sum = st[p * 2].sum + st[p * 2 + 1].sum;

            st[p].mx = max(st[p * 2].mx,
                           st[p * 2 + 1].mx);

            st[p].mn = min(st[p * 2].mn,
                           st[p * 2 + 1].mn);
        }

        // -----------------------------------------------------
        // BUILD
        // -----------------------------------------------------
        void build(int p, int l, int r,
                   vector<long long>& base) {

            if(l == r) {

                st[p].sum = base[l];
                st[p].mx = base[l];
                st[p].mn = base[l];

                return;
            }

            int m = (l + r) / 2;

            build(p * 2, l, m, base);
            build(p * 2 + 1, m + 1, r, base);

            pull(p);
        }

        // -----------------------------------------------------
        // RANGE ADD
        // -----------------------------------------------------
        void rangeAdd(int p, int l, int r,
                      int ql, int qr,
                      long long val) {

            if(r < ql || l > qr)
                return;

            if(ql <= l && r <= qr) {

                applyAdd(p, l, r, val);
                return;
            }

            push(p, l, r);

            int m = (l + r) / 2;

            rangeAdd(p * 2, l, m,
                     ql, qr, val);

            rangeAdd(p * 2 + 1, m + 1, r,
                     ql, qr, val);

            pull(p);
        }

        // -----------------------------------------------------
        // RANGE ASSIGN
        // -----------------------------------------------------
        void rangeSet(int p, int l, int r,
                      int ql, int qr,
                      long long val) {

            if(r < ql || l > qr)
                return;

            if(ql <= l && r <= qr) {

                applySet(p, l, r, val);
                return;
            }

            push(p, l, r);

            int m = (l + r) / 2;

            rangeSet(p * 2, l, m,
                     ql, qr, val);

            rangeSet(p * 2 + 1, m + 1, r,
                     ql, qr, val);

            pull(p);
        }

        // -----------------------------------------------------
        // QUERY
        // Returns {sum, max, min}
        // -----------------------------------------------------
        struct Info {
            long long sum = 0;
            long long mx = LLONG_MIN;
            long long mn = LLONG_MAX;
        };

        Info query(int p, int l, int r,
                   int ql, int qr) {

            if(r < ql || l > qr)
                return {0, LLONG_MIN, LLONG_MAX};

            if(ql <= l && r <= qr) {

                return {
                    st[p].sum,
                    st[p].mx,
                    st[p].mn
                };
            }

            push(p, l, r);

            int m = (l + r) / 2;

            Info L = query(p * 2, l, m,
                           ql, qr);

            Info R = query(p * 2 + 1, m + 1, r,
                           ql, qr);

            return {
                L.sum + R.sum,
                max(L.mx, R.mx),
                min(L.mn, R.mn)
            };
        }

        // -----------------------------------------------------
        // POINT SET
        // -----------------------------------------------------
        void pointSet(int p, int l, int r,
                      int idx,
                      long long val) {

            if(l == r) {

                st[p].sum = val;
                st[p].mx = val;
                st[p].mn = val;

                st[p].lazyAdd = 0;
                st[p].lazySet = 0;
                st[p].hasSet = false;

                return;
            }

            push(p, l, r);

            int m = (l + r) / 2;

            if(idx <= m)
                pointSet(p * 2, l, m, idx, val);
            else
                pointSet(p * 2 + 1, m + 1, r, idx, val);

            pull(p);
        }

    } seg;


    // =========================================================
    // HLD
    // =========================================================

    int n;
    int curPos;

    vector<vector<int>> adj;

    vector<int> parent;
    vector<int> depth;
    vector<int> heavy;
    vector<int> head;
    vector<int> pos;
    vector<int> sub;

    vector<long long> nodeVal;
    vector<long long> base;


    // ---------------------------------------------------------
    // CONSTRUCTOR
    // ---------------------------------------------------------
    HeavyLightDecomposition(int n)
        : n(n),
          curPos(0),
          adj(n + 1),
          parent(n + 1),
          depth(n + 1),
          heavy(n + 1, -1),
          head(n + 1),
          pos(n + 1),
          sub(n + 1),
          nodeVal(n + 1),
          base(n + 1),
          seg(n) {}


    // ---------------------------------------------------------
    // ADD EDGE
    // ---------------------------------------------------------
    void addEdge(int u, int v) {

        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    // ---------------------------------------------------------
    // INITIAL VALUE
    // ---------------------------------------------------------
    void setValue(int u, long long val) {

        nodeVal[u] = val;
    }


    // =========================================================
    // DFS 1
    // Find:
    // parent
    // depth
    // subtree size
    // heavy child
    // =========================================================
    void dfs1(int u, int p) {

        parent[u] = p;
        sub[u] = 1;
        heavy[u] = -1;

        for(auto v : adj[u]) {

            if(v == p)
                continue;

            depth[v] = depth[u] + 1;

            dfs1(v, u);

            sub[u] += sub[v];

            if(heavy[u] == -1 ||
               sub[v] > sub[heavy[u]])

                heavy[u] = v;
        }
    }


    // =========================================================
    // DFS 2
    // Decompose into heavy chains
    // =========================================================
    void dfs2(int u, int h) {

        head[u] = h;

        pos[u] = ++curPos;

        base[curPos] = nodeVal[u];


        // Heavy child first
        if(heavy[u] != -1)

            dfs2(heavy[u], h);


        // Light children
        for(auto v : adj[u]) {

            if(v == parent[u] ||
               v == heavy[u])

                continue;

            dfs2(v, v);
        }
    }


    // =========================================================
    // BUILD
    // =========================================================
    void build(int root = 1) {

        depth[root] = 0;

        dfs1(root, 0);

        dfs2(root, root);

        seg.build(1, 1, n, base);
    }


    // =========================================================
    // PATH ADD
    // Add val to every node on u -> v
    // =========================================================
    void pathAdd(int u, int v, long long val) {

        while(head[u] != head[v]) {

            if(depth[head[u]] <
               depth[head[v]])

                swap(u, v);


            seg.rangeAdd(
                1, 1, n,
                pos[head[u]],
                pos[u],
                val
            );

            u = parent[head[u]];
        }


        if(depth[u] > depth[v])
            swap(u, v);


        seg.rangeAdd(
            1, 1, n,
            pos[u],
            pos[v],
            val
        );
    }


    // =========================================================
    // PATH UPDATE / ASSIGN
    // Set every node on u -> v = val
    // =========================================================
    void pathUpdate(int u, int v, long long val) {

        while(head[u] != head[v]) {

            if(depth[head[u]] <
               depth[head[v]])

                swap(u, v);


            seg.rangeSet(
                1, 1, n,
                pos[head[u]],
                pos[u],
                val
            );

            u = parent[head[u]];
        }


        if(depth[u] > depth[v])
            swap(u, v);


        seg.rangeSet(
            1, 1, n,
            pos[u],
            pos[v],
            val
        );
    }


    // =========================================================
    // PATH QUERY
    // Returns sum / max / min
    // =========================================================
    typename SegTree::Info queryPath(int u, int v) {

        typename SegTree::Info res;

        res.sum = 0;
        res.mx = LLONG_MIN;
        res.mn = LLONG_MAX;


        while(head[u] != head[v]) {

            if(depth[head[u]] <
               depth[head[v]])

                swap(u, v);


            auto cur =
                seg.query(
                    1, 1, n,
                    pos[head[u]],
                    pos[u]
                );


            res.sum += cur.sum;

            res.mx = max(res.mx, cur.mx);

            res.mn = min(res.mn, cur.mn);


            u = parent[head[u]];
        }


        if(depth[u] > depth[v])
            swap(u, v);


        auto cur =
            seg.query(
                1, 1, n,
                pos[u],
                pos[v]
            );


        res.sum += cur.sum;

        res.mx = max(res.mx, cur.mx);

        res.mn = min(res.mn, cur.mn);


        return res;
    }


    // =========================================================
    // SUBTREE ADD
    // =========================================================
    void subtreeAdd(int u, long long val) {

        seg.rangeAdd(
            1, 1, n,
            pos[u],
            pos[u] + sub[u] - 1,
            val
        );
    }


    // =========================================================
    // SUBTREE UPDATE / ASSIGN
    // =========================================================
    void subtreeUpdate(int u, long long val) {

        seg.rangeSet(
            1, 1, n,
            pos[u],
            pos[u] + sub[u] - 1,
            val
        );
    }


    // =========================================================
    // SUBTREE QUERY
    // =========================================================
    typename SegTree::Info querySubtree(int u) {

        return seg.query(
            1, 1, n,
            pos[u],
            pos[u] + sub[u] - 1
        );
    }


    // =========================================================
    // POINT SET
    // =========================================================
    void pointUpdate(int u, long long val) {

        seg.pointSet(
            1, 1, n,
            pos[u],
            val
        );
    }
};


// =============================================================
// MAIN
// =============================================================

int32_t main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    HeavyLightDecomposition hld(n);


    // values
    for(int i = 1; i <= n; i++) {

        int x;
        cin >> x;

        hld.setValue(i, x);
    }


    // edges
    for(int i = 1; i < n; i++) {

        int u, v;
        cin >> u >> v;

        hld.addEdge(u, v);
    }


    // MUST build
    hld.build();


    // Example usage:

    // Path add
    // hld.pathAdd(u, v, x);

    // Path assignment
    // hld.pathUpdate(u, v, x);

    // Subtree add
    // hld.subtreeAdd(u, x);

    // Subtree assignment
    // hld.subtreeUpdate(u, x);

    // Point assignment
    // hld.pointUpdate(u, x);

    // Path query
    // auto ans = hld.queryPath(u, v);
    // ans.sum
    // ans.mx
    // ans.mn

    // Subtree query
    // auto ans = hld.querySubtree(u);
    // ans.sum
    // ans.mx
    // ans.mn
}
