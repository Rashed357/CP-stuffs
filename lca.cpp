#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
const int LOG = 20;   // enough for N <= 2e5

vector<int> adj[N];
int up[N][LOG];
int depth[N];

void dfs(int v, int p)
{
    up[v][0] = p;

    for(int j = 1; j < LOG; j++)
        up[v][j] = up[ up[v][j-1] ][j-1];

    for(int to : adj[v])
    {
        if(to == p) continue;
        depth[to] = depth[v] + 1;
        dfs(to, v);
    }
}

int lca(int a, int b)
{
    if(depth[a] < depth[b])
        swap(a, b);

    // Lift a to same depth as b
    int diff = depth[a] - depth[b];

    for(int j = LOG-1; j >= 0; j--)
    {
        if(diff & (1<<j))
            a = up[a][j];
    }

    if(a == b)
        return a;

    // Lift both
    for(int j = LOG-1; j >= 0; j--)
    {
        if(up[a][j] != up[b][j])
        {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}
