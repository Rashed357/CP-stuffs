#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5; // adjust size as needed
vector<int> adj[N];
bool visited[N];
int tin[N], low[N];
int timer;
vector<pair<int, int>> bridges;

void dfs(int u, int p = -1) {
    visited[u] = true;
    tin[u] = low[u] = timer++;

    for (int v : adj[u]) {
        if (v == p) continue;
        if (visited[v]) {
            // Back edge
            low[u] = min(low[u], tin[v]);
        } else {
            // Tree edge
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > tin[u]) {
                // Bridge found
                bridges.emplace_back(u, v);
            }
        }
    }
}

void find_bridges(int n) {
    timer = 0;
    bridges.clear();
    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m; // n = number of nodes, m = number of edges
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    find_bridges(n);

    cout << "Bridges:\n";
    for (auto [u, v] : bridges) {
        cout << u << " - " << v << "\n";
    }

    return 0;
}
