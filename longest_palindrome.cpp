// Application: Manacher’s Algorithm is used to find the longest palindromic substring in O(n) time.
string longestPalindrome(string s) {
    int n = s.length();
    if (n == 0) return "";

    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }

    int len = t.length();
    vector<int> p(len, 0);  // p[i] = radius of palindrome centered at i
    int center = 0, right = 0;

    for (int i = 0; i < len; i++) {
        int mirror = 2 * center - i;
        if (i < right) {
            p[i] = min(right - i, p[mirror]);
        }

        while (i + p[i] + 1 < len && i - p[i] - 1 >= 0 && t[i + p[i] + 1] == t[i - p[i] - 1]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }

    int maxLen = 0, start = 0;
    for (int i = 0; i < len; i++) {
        if (p[i] > maxLen) {
            maxLen = p[i];
            start = (i - maxLen) / 2;
        }
    }

    return s.substr(start, maxLen);
}
