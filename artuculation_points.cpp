#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5; // change according to problem constraints

vector<int> adj[N];
bool visited[N], isArticulation[N];
int tin[N], low[N], timer;

void dfs(int u, int parent = -1) {
    visited[u] = true;
    tin[u] = low[u] = timer++;
    int children = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;
        if (visited[v]) {
            // Back edge
            low[u] = min(low[u], tin[v]);
        } else {
            // Tree edge
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tin[u] && parent != -1) {
                isArticulation[u] = true;
            }
            ++children;
        }
    }

    if (parent == -1 && children > 1) {
        isArticulation[u] = true; // root case
    }
}

void findArticulationPoints(int n) {
    timer = 0;
    fill(visited, visited + n + 1, false);
    fill(isArticulation, isArticulation + n + 1, false);

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) dfs(i);
    }

    cout << "Articulation Points:\n";
    for (int i = 1; i <= n; ++i) {
        if (isArticulation[i]) cout << i << " ";
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m; // number of nodes and edges

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    findArticulationPoints(n);
    return 0;
}
