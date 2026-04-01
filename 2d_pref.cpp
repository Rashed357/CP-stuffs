// pref[i][j] = sum of rectangle (1,1) to (i,j)
vector<vector<long long>> build_prefix(vector<vector<long long>> &a, int n, int m) {
    vector<vector<long long>> pref(n + 1, vector<long long>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pref[i][j] = a[i][j]
                       + pref[i-1][j]
                       + pref[i][j-1]
                       - pref[i-1][j-1];
        }
    }
    return pref;
}

long long query(vector<vector<long long>> &pref, int x1, int y1, int x2, int y2) {
    return pref[x2][y2]
         - pref[x1-1][y2]
         - pref[x2][y1-1]
         + pref[x1-1][y1-1];
}
