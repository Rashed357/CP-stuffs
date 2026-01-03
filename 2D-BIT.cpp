#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1005; // we will use indices 1..1001 (0..1000 input -> +1)
long long BIT[MAXC+5][MAXC+5];
bool vis[MAXC+5][MAXC+5];

void bit_update(int x, int y, long long val) {
    for (int i = x; i <= MAXC; i += (i & -i)) {
        for (int j = y; j <= MAXC; j += (j & -j)) {
            BIT[i][j] += val;
        }
    }
}

long long bit_query(int x, int y) {
    long long sum = 0;
    if (x <= 0 || y <= 0) return 0; // safe guard
    for (int i = x; i > 0; i -= (i & -i)) {
        for (int j = y; j > 0; j -= (j & -j)) {
            sum += BIT[i][j];
        }
    }
    return sum;
}

long long rect_query(int x1, int y1, int x2, int y2) {
    // inclusive rectangle, assume x1<=x2 and y1<=y2
    return bit_query(x2, y2)
         - bit_query(x1 - 1, y2)
         - bit_query(x2, y1 - 1)
         + bit_query(x1 - 1, y1 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        // reset BIT and visited array for each test
        for (int i = 0; i <= MAXC; ++i) {
            // set row zeros quickly
            memset(BIT[i], 0, sizeof(BIT[i]));
            memset(vis[i], 0, sizeof(vis[i]));
        }
        cout << "Case " << tc << ":\n";

        int q; cin >> q;
        while (q--) {
            int type; cin >> type;
            if (type == 0) {
                int x, y; cin >> x >> y;
                // convert to 1-based indexing for BIT
                ++x; ++y;
                if (!vis[x][y]) {
                    vis[x][y] = true;
                    bit_update(x, y, 1);
                }
            } else if (type == 1) {
                int x1, y1, x2, y2; 
                cin >> x1 >> y1 >> x2 >> y2;
                // convert to 1-based
                ++x1; ++y1; ++x2; ++y2;
                long long ans = rect_query(x1, y1, x2, y2);
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
