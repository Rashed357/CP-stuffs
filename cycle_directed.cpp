vector<int> vis(n + 1);

bool dfs(int u)
{
    vis[u] = 1; // currently in recursion

    for(int v : adj[u])
    {
        if(vis[v] == 1) return true;

        if(vis[v] == 0 && dfs(v))
            return true;
    }

    vis[u] = 2; // finished
    return false;
}
