#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18; // Use 1e18 to prevent overflow on addition

void floydWarshall(int n, vector<vector<long long>>& dist) {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Optional: Check for negative cycles
    // for (int i = 1; i <= n; ++i) {
    //     if (dist[i][i] < 0) {
    //         cout << "Graph contains a negative cycle\n";
    //         break;
    //     }
    // }
}

int main() {
    int n = 4; // Number of vertices (1-indexed)
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));

    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
    }

    // Add edges: dist[u][v] = weight
    // If undirected: dist[v][u] = weight as well
    dist[1][2] = 5;
    dist[2][3] = 3;
    dist[3][4] = 1;
    dist[1][4] = 10;

    floydWarshall(n, dist);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
