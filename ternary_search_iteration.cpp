#include <bits/stdc++.h>
using namespace std;

long double L, W;

// volume of the box for a given x
long double volume(long double x) {
    return x * (L - 2.0L * x) * (W - 2.0L * x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    cout << fixed << setprecision(9);

    for (int tc = 1; tc <= T; tc++) {
        cin >> L >> W;

        long double lo = 0.0L;
        long double hi = min(L, W) / 2.0L;

        // ternary search
        for (int i = 0; i < 100; i++) {
            long double m1 = lo + (hi - lo) / 3.0L;
            long double m2 = hi - (hi - lo) / 3.0L;

            if (volume(m1) < volume(m2))
                lo = m1;
            else
                hi = m2;
        }

        long double x = (lo + hi) / 2.0L;
        long double ans = volume(x);

        if (ans < 0) ans = 0; // safety

        cout << "Case " << tc << ": " << (double)ans << '\n';
    }

    return 0;
}
