#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int total = 1 << n; // 2^n subsets

    for (int mask = 0; mask < total; ++mask) {
        vi subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(a[i]);
            }
        }

        // Print current subset
        cout << "{ ";
        for (int x : subset) cout << x << " ";
        cout << "}\n";
    }

    return 0;
}
