struct KMP {
    vector<int> pi;
    string p;

    // Constructor
    // Time:  O(m)
    // Space: O(m)
    // where m = length of pattern
    KMP(const string &pattern) {
        p = pattern;
        int m = p.size();
        pi.assign(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && p[i] != p[j]) 
                j = pi[j - 1];
            if (p[i] == p[j]) 
                ++j;
            pi[i] = j;
        }
    }

    // Find all occurrences of pattern in text (0-based)
    // Time:  O(n)
    // Space: O(1) extra (excluding result vector)
    vector<int> find_all(const string &s) {
        vector<int> res;
        int n = s.size(), m = p.size();
        if (m == 0 || n < m) return res;

        int j = 0;
        for (int i = 0; i < n; ++i) {
            while (j > 0 && s[i] != p[j]) 
                j = pi[j - 1];
            if (s[i] == p[j]) 
                ++j;
            if (j == m) {
                res.push_back(i - m + 1); // match found
                j = pi[j - 1];           // allow overlap
            }
        }
        return res;
    }

    // Count occurrences of pattern in text
    // Time:  O(n)
    // Space: O(1)
    int count_occurrences(const string &s) {
        int n = s.size(), m = p.size();
        if (m == 0 || n < m) return 0;

        int cnt = 0, j = 0;
        for (int i = 0; i < n; ++i) {
            while (j > 0 && s[i] != p[j]) 
                j = pi[j - 1];
            if (s[i] == p[j]) 
                ++j;
            if (j == m) {
                ++cnt;
                j = pi[j - 1];
            }
        }
        return cnt;
    }
};
