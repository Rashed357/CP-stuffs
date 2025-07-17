#include <bits/stdc++.h>
using namespace std;

const int MAX = 10005;

vector<int> graph[MAX];      // Original graph
vector<int> rev_graph[MAX];  // Reversed graph
vector<bool> visited;
stack<int> finishing_order;
int scc_id[MAX];             // scc_id[i] = SCC number of node i
int total_scc;

void reset(int n) {
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        rev_graph[i].clear();
    }
    visited.assign(n + 1, false);
    while (!finishing_order.empty()) finishing_order.pop();
    total_scc = 0;
    memset(scc_id, 0, sizeof(scc_id));
}

void dfs1(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v])
            dfs1(v);
    }
    finishing_order.push(u);
}

void dfs2(int u, int id) {
    scc_id[u] = id;
    for (int v : rev_graph[u]) {
        if (scc_id[v] == 0)
            dfs2(v, id);
    }
}

int kosaraju(int n) {
    // Step 1: Fill finishing order
    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            dfs1(i);
    }

    // Step 2: Process nodes in reverse finishing order
    int id = 0;
    while (!finishing_order.empty()) {
        int u = finishing_order.top();
        finishing_order.pop();
        if (scc_id[u] == 0) {
            ++id;
            dfs2(u, id);
        }
    }
    total_scc = id;
    return id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int cs = 1; cs <= T; cs++) {
        string blank;
        getline(cin, blank); // read the newline after T
        getline(cin, blank); // blank line between test cases

        int n, m;
        cin >> n >> m;

        reset(n);

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            rev_graph[b].push_back(a);
        }

        int scc_count = kosaraju(n);

        // Build in-degree of condensation graph
        vector<int> indegree(total_scc + 1, 0);
        for (int u = 1; u <= n; u++) {
            for (int v : graph[u]) {
                if (scc_id[u] != scc_id[v]) {
                    indegree[scc_id[v]]++;
                }
            }
        }

        // Count how many SCCs have in-degree 0
        int answer = 0;
        for (int i = 1; i <= total_scc; i++) {
            if (indegree[i] == 0)
                answer++;
        }

        cout << "Case " << cs << ": " << answer << "\n";
    }

    return 0;
}
