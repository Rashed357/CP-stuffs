#include <bits/stdc++.h>
using namespace std;

class Kosaraju
{
    int n;
    vector<vector<int>> g, rg;
    vector<bool> vis;
    vector<int> order;

public:
    vector<int> comp;          // comp[u] = SCC id of u
    int scc_cnt;

    Kosaraju(int n)
    {
        init(n);
    }

    void init(int n)
    {
        this->n = n;

        g.assign(n + 1, {});
        rg.assign(n + 1, {});
        vis.assign(n + 1, false);

        comp.assign(n + 1, 0);
        order.clear();

        scc_cnt = 0;
    }

    void add_edge(int u, int v)
    {
        g[u].push_back(v);
        rg[v].push_back(u);
    }

private:
    void dfs1(int u)
    {
        vis[u] = true;

        for (int v : g[u])
        {
            if (!vis[v])
                dfs1(v);
        }

        order.push_back(u);
    }

    void dfs2(int u, int id)
    {
        comp[u] = id;

        for (int v : rg[u])
        {
            if (comp[v] == 0)
                dfs2(v, id);
        }
    }

public:
    // Main SCC decomposition
    int build()
    {
        // Step 1
        fill(vis.begin(), vis.end(), false);
        order.clear();

        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
                dfs1(i);
        }

        // Step 2
        reverse(order.begin(), order.end());

        fill(comp.begin(), comp.end(), 0);
        scc_cnt = 0;

        for (int u : order)
        {
            if (comp[u] == 0)
            {
                ++scc_cnt;
                dfs2(u, scc_cnt);
            }
        }

        return scc_cnt;
    }

    // Are u and v in the same SCC?
    bool same_scc(int u, int v)
    {
        return comp[u] == comp[v];
    }

    // Size of each SCC
    vector<int> component_sizes()
    {
        vector<int> sz(scc_cnt + 1, 0);

        for (int i = 1; i <= n; i++)
            sz[comp[i]]++;

        return sz;
    }

    // Build condensation DAG
    vector<vector<int>> build_condensation()
    {
        vector<vector<int>> dag(scc_cnt + 1);

        for (int u = 1; u <= n; u++)
        {
            for (int v : g[u])
            {
                int cu = comp[u];
                int cv = comp[v];

                if (cu != cv)
                    dag[cu].push_back(cv);
            }
        }

        return dag;
    }

    // In-degree of SCCs in condensation DAG
    vector<int> indegree()
    {
        vector<int> in(scc_cnt + 1, 0);

        for (int u = 1; u <= n; u++)
        {
            for (int v : g[u])
            {
                int cu = comp[u];
                int cv = comp[v];

                if (cu != cv)
                    in[cv]++;
            }
        }

        return in;
    }

    // Out-degree of SCCs in condensation DAG
    vector<int> outdegree()
    {
        vector<int> out(scc_cnt + 1, 0);

        for (int u = 1; u <= n; u++)
        {
            for (int v : g[u])
            {
                int cu = comp[u];
                int cv = comp[v];

                if (cu != cv)
                    out[cu]++;
            }
        }

        return out;
    }

    // Number of source SCCs
    int source_scc_count()
    {
        vector<int> in = indegree();

        int ans = 0;

        for (int i = 1; i <= scc_cnt; i++)
        {
            if (in[i] == 0)
                ans++;
        }

        return ans;
    }

    // Number of sink SCCs
    int sink_scc_count()
    {
        vector<int> out = outdegree();

        int ans = 0;

        for (int i = 1; i <= scc_cnt; i++)
        {
            if (out[i] == 0)
                ans++;
        }

        return ans;
    }

    // Get original graph if needed
    vector<vector<int>>& graph()
    {
        return g;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    Kosaraju scc(n);

    for(int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
    }

    scc.build();

    // number of SCCs
    cout << scc.scc_cnt << '\n';

    // SCC id of node 5
    cout << scc.comp[5] << '\n';

    // source SCC count
    cout << scc.source_scc_count() << '\n';
}
