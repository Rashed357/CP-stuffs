// Application: KMP algorithm is used to search for occurrences of a pattern in a text efficiently in O(n + m).
vector<int> computeLPS(string pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Use previously computed LPS values
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMP(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> lps = computeLPS(pattern);

    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}
