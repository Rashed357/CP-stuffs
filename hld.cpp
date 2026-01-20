#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


struct HeavyLightDecomposition {
    int n, curPos;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, sub;
    vector<long long> nodeVal, base;

    // ---------- SEGMENT TREE ----------
    struct SegTree {
        int n;
        vector<long long> st;

        SegTree(int n = 0) {
            this->n = n;
            st.assign(4*n + 4, 0);
        }

        void build(int p, int l, int r, vector<long long>& base) {
            if (l == r) {
                st[p] = base[l];
                return;
            }
            int m = (l + r) / 2;
            build(p*2, l, m, base);
            build(p*2+1, m+1, r, base);
            st[p] = st[p*2] + st[p*2+1];
        }

        long long query(int p, int l, int r, int i, int j) {
            if (r < i || l > j) return 0;
            if (l >= i && r <= j) return st[p];
            int m = (l + r) / 2;
            return query(p*2, l, m, i, j) +
                   query(p*2+1, m+1, r, i, j);
        }

        void update(int p, int l, int r, int idx, long long val) {
            if (l == r) {
                st[p] = val;
                return;
            }
            int m = (l + r) / 2;
            if (idx <= m) update(p*2, l, m, idx, val);
            else update(p*2+1, m+1, r, idx, val);
            st[p] = st[p*2] + st[p*2+1];
        }
    } seg;

    // ---------- CONSTRUCTOR ----------
    HeavyLightDecomposition(int n)
        : n(n), curPos(0),
          adj(n+1),
          parent(n+1), depth(n+1),
          heavy(n+1, -1), head(n+1),
          pos(n+1), sub(n+1),
          nodeVal(n+1), base(n+1),
          seg(n) {}

    // ---------- ADD EDGE ----------
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ---------- SET INITIAL NODE VALUE ----------
    void setValue(int u, long long val) {
        nodeVal[u] = val;
    }

    // ---------- DFS 1 ----------
    void dfs1(int u, int p) {
        parent[u] = p;
        sub[u] = 1;
        heavy[u] = -1;

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs1(v, u);
            sub[u] += sub[v];
            if (heavy[u] == -1 || sub[v] > sub[heavy[u]])
                heavy[u] = v;
        }
    }

    // ---------- DFS 2 ----------
    void dfs2(int u, int h) {
        head[u] = h;
        pos[u] = ++curPos;
        base[curPos] = nodeVal[u];

        if (heavy[u] != -1)
            dfs2(heavy[u], h);

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            dfs2(v, v);
        }
    }

    // ---------- BUILD HLD ----------
    void build(int root = 1) {
        depth[root] = 0;
        dfs1(root, 0);
        dfs2(root, root);
        seg.build(1, 1, n, base);
    }

    // ---------- PATH QUERY ----------
    long long queryPath(int u, int v) {
        long long res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            res += seg.query(1, 1, n, pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        res += seg.query(1, 1, n, pos[u], pos[v]);
        return res;
    }

    // ---------- POINT UPDATE ----------
    void updateNode(int u, long long val) {
        seg.update(1, 1, n, pos[u], val);
    }
};

int cs;

void solve(){

    cout<<"Case "<<++cs<<":\n";
    int n; cin>>n; 

    HeavyLightDecomposition obj(n);

    for(int i = 1; i<=n; i++){
        int x; cin>>x; 
        obj.setValue(i,x);
    }

    for(int i = 1; i<n; i++){
        int u,v; cin>>u>>v; 
        u++;
        v++;
        obj.addEdge(u,v);
    }

    obj.build();

    int m; cin>>m; 
    while(m--){
        int type; cin>>type;
        if(type==0){
            int u,v; cin>>u>>v;
            u++;
            v++;
            cout<<obj.queryPath(u,v)<<endl;
        }
        else{
            int i, val;
            cin>>i>>val;
            i++;
            obj.updateNode(i,val);
        }
    }
}

int32_t main(){
   ios::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);
   
   int t; cin >> t; while(t--)
   solve();

   return 0;
}
