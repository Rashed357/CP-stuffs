struct KMP {
    vector<int> pi;
    string s;

    // build prefix-function for string t
    void build(const string &t) {
        s = t;
        int n = s.size();
        pi.assign(n, 0);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j])
                j = pi[j - 1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
    }

    // longest prefix which is also suffix
    int longest_prefix_suffix() const {
        return pi.empty() ? 0 : pi.back();
    }

    // count occurrences of pattern in text
    int count_occurrences(const string &pat, const string &txt) {
        string t = pat + "#" + txt;
        build(t);
        int cnt = 0;
        int m = pat.size();
        for (int x : pi)
            if (x == m)
                cnt++;
        return cnt;
    }

    // shortest palindrome length by appending to RIGHT
    int make_palindrome_append_right(const string &str) {
        string r = str;
        reverse(r.begin(), r.end());
        string t = r + "#" + str;
        build(t);
        int L = longest_prefix_suffix();
        return 2 * (int)str.size() - L;
    }

    // check if string is periodic
    // returns smallest period length
    int smallest_period() const {
        int n = s.size();
        int k = n - pi.back();
        if (n % k == 0) return k;
        return n; // not periodic
    }
};
