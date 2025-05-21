// Application: Topological sorting is used in scheduling tasks, course prerequisites, etc.
vector<int> topologicalSort(int n, vector<vector<int>>& graph) {
    vector<int> inDegree(n, 0);
    vector<int> topoOrder;
    queue<int> q;

    // Compute in-degrees of all nodes
    for (int i = 0; i < n; i++) {
        for (int neighbor : graph[i]) {
            inDegree[neighbor]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) q.push(i); // Nodes with zero in-degree
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);

        for (int neighbor : graph[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) q.push(neighbor);
        }
    }

    if (topoOrder.size() != n) return {}; // Graph has a cycle
    return topoOrder;
}


//O(v+e)

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
int indeg[N];
vector<int> g[N];
bool vis[N];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  while (m--) {
    int u, v; cin >> u >> v;
    indeg[v]++;
    g[u].push_back(v);
  }
  vector<int> z;
  for (int i = 1; i <= n; i++) {
    if (indeg[i] == 0) {
      z.push_back(i);
      vis[i] = true;
    }
  }
  vector<int> ans;
  while (ans.size() < n) {
    if (z.empty()) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
    int cur = z.back();
    z.pop_back();
    ans.push_back(cur);
    for (auto v: g[cur]) {
      indeg[v]--;
      if (!vis[v] and indeg[v] == 0) {
        z.push_back(v);
        vis[v] = true;
      }
    }
  }
  for (auto x: ans) cout << x << ' ';
  return 0;
}
