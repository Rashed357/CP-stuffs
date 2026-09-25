#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int LOG = 20;   // enough for N <= 2e5

class BinaryLifting
{
public:
    int n;
    vector<int> adj[N];
    int up[N][LOG];
    int depth[N];

    BinaryLifting(int n)
    {
        this->n = n;
        for(int i = 1; i <= n; i++)
        {
            adj[i].clear();
            depth[i] = 0;
        }

        memset(up, 0, sizeof(up));
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p)
    {
        up[v][0] = p;

        for(int j = 1; j < LOG; j++)
            up[v][j] = up[up[v][j-1]][j-1];

        for(int to : adj[v])
        {
            if(to == p) continue;

            depth[to] = depth[v] + 1;
            dfs(to, v);
        }
    }

    void build(int root = 1)
    {
        depth[root] = 0;
        dfs(root, root);
    }

    // kth ancestor of node v
    // Example: kthAncestor(7, 3)
    int kthAncestor(int v, int k)
    {
        for(int j = LOG - 1; j >= 0; j--)
        {
            if(k & (1 << j))
                v = up[v][j];
        }

        return v;
    }

    // Lowest Common Ancestor
    int lca(int a, int b)
    {
        if(depth[a] < depth[b])
            swap(a, b);

        // Make same depth
        int diff = depth[a] - depth[b];

        for(int j = LOG - 1; j >= 0; j--)
        {
            if(diff & (1 << j))
                a = up[a][j];
        }

        if(a == b)
            return a;

        // Lift both
        for(int j = LOG - 1; j >= 0; j--)
        {
            if(up[a][j] != up[b][j])
            {
                a = up[a][j];
                b = up[b][j];
            }
        }

        return up[a][0];
    }

    // Distance between two nodes
    int distance(int a, int b)
    {
        int c = lca(a, b);

        return depth[a] + depth[b] - 2 * depth[c];
    }

    // Is u an ancestor of v?
    bool isAncestor(int u, int v)
    {
        return lca(u, v) == u;
    }

    // Move v upward by k nodes
    int jump(int v, int k)
    {
        return kthAncestor(v, k);
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    BinaryLifting bl(n);

    // Tree edges
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        bl.addEdge(u, v);
    }

    bl.build(1);

    int q;
    cin >> q;

    while(q--)
    {
        int type;
        cin >> type;

        if(type == 1)
        {
            // LCA
            int u, v;
            cin >> u >> v;

            cout << bl.lca(u, v) << '\n';
        }
        else if(type == 2)
        {
            // kth ancestor
            int u, k;
            cin >> u >> k;

            cout << bl.kthAncestor(u, k) << '\n';
        }
        else if(type == 3)
        {
            // distance
            int u, v;
            cin >> u >> v;

            cout << bl.distance(u, v) << '\n';
        }
        else if(type == 4)
        {
            // check ancestor
            int u, v;
            cin >> u >> v;

            cout << (bl.isAncestor(u, v) ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
