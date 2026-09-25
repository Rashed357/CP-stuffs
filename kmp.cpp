#include <bits/stdc++.h>
using namespace std;

#define int long long

struct KMP
{
    string pat;
    vector<int> pi;

    // Constructor
    KMP(string p = "")
    {
        pat = p;

        if(!pat.empty())
            build();
    }

    // =========================================================
    // 1. Build Prefix Function / LPS
    // pi[i] = length of longest proper prefix
    //         which is also suffix of pat[0..i]
    // =========================================================
    void build()
    {
        int m = pat.size();
        pi.assign(m, 0);

        for(int i = 1, j = 0; i < m; i++)
        {
            while(j > 0 && pat[i] != pat[j])
                j = pi[j - 1];

            if(pat[i] == pat[j])
                j++;

            pi[i] = j;
        }
    }

    // =========================================================
    // 2. Get Prefix Function of any string
    // =========================================================
    static vector<int> prefix_function(string s)
    {
        int n = s.size();
        vector<int> p(n, 0);

        for(int i = 1, j = 0; i < n; i++)
        {
            while(j > 0 && s[i] != s[j])
                j = p[j - 1];

            if(s[i] == s[j])
                j++;

            p[i] = j;
        }

        return p;
    }

    // =========================================================
    // 3. Check if pattern exists in text
    // =========================================================
    bool contains(string text)
    {
        if(pat.empty())
            return true;

        int n = text.size();
        int m = pat.size();

        for(int i = 0, j = 0; i < n; i++)
        {
            while(j > 0 && text[i] != pat[j])
                j = pi[j - 1];

            if(text[i] == pat[j])
                j++;

            if(j == m)
                return true;
        }

        return false;
    }

    // =========================================================
    // 4. Find first occurrence
    // Returns 0-based index, -1 if not found
    // =========================================================
    int first(string text)
    {
        if(pat.empty())
            return 0;

        int n = text.size();
        int m = pat.size();

        for(int i = 0, j = 0; i < n; i++)
        {
            while(j > 0 && text[i] != pat[j])
                j = pi[j - 1];

            if(text[i] == pat[j])
                j++;

            if(j == m)
                return i - m + 1;
        }

        return -1;
    }

    // =========================================================
    // 5. Find all occurrences
    // Overlapping occurrences are included
    // =========================================================
    vector<int> find_all(string text)
    {
        vector<int> ans;

        if(pat.empty())
        {
            for(int i = 0; i <= (int)text.size(); i++)
                ans.push_back(i);

            return ans;
        }

        int n = text.size();
        int m = pat.size();

        for(int i = 0, j = 0; i < n; i++)
        {
            while(j > 0 && text[i] != pat[j])
                j = pi[j - 1];

            if(text[i] == pat[j])
                j++;

            if(j == m)
            {
                ans.push_back(i - m + 1);

                // Important:
                // allows overlapping matches
                j = pi[j - 1];
            }
        }

        return ans;
    }

    // =========================================================
    // 6. Count all occurrences
    // Overlapping occurrences are included
    // =========================================================
    int count_occurrences(string text)
    {
        if(pat.empty())
            return text.size() + 1;

        int ans = 0;
        int n = text.size();
        int m = pat.size();

        for(int i = 0, j = 0; i < n; i++)
        {
            while(j > 0 && text[i] != pat[j])
                j = pi[j - 1];

            if(text[i] == pat[j])
                j++;

            if(j == m)
            {
                ans++;
                j = pi[j - 1];
            }
        }

        return ans;
    }

    // =========================================================
    // 7. Count non-overlapping occurrences
    // =========================================================
    int count_non_overlapping(string text)
    {
        if(pat.empty())
            return text.size() + 1;

        int ans = 0;
        int n = text.size();
        int m = pat.size();

        for(int i = 0, j = 0; i < n; i++)
        {
            while(j > 0 && text[i] != pat[j])
                j = pi[j - 1];

            if(text[i] == pat[j])
                j++;

            if(j == m)
            {
                ans++;

                // Restart completely
                j = 0;
            }
        }

        return ans;
    }

    // =========================================================
    // 8. Get matched length after processing each text char
    //
    // match[i] = length of longest prefix of pattern
    //            matching a suffix ending at text[i]
    //
    // Very useful in DP / advanced string problems
    // =========================================================
    vector<int> match_lengths(string text)
    {
        vector<int> match;

        if(pat.empty())
            return vector<int>(text.size(), 0);

        int n = text.size();
        int m = pat.size();

        match.resize(n);

        for(int i = 0, j = 0; i < n; i++)
        {
            while(j > 0 && text[i] != pat[j])
                j = pi[j - 1];

            if(text[i] == pat[j])
                j++;

            match[i] = j;

            if(j == m)
                j = pi[j - 1];
        }

        return match;
    }

    // =========================================================
    // 9. Longest Proper Prefix = Suffix of pattern
    // =========================================================
    int longest_border()
    {
        if(pat.empty())
            return 0;

        return pi.back();
    }

    // =========================================================
    // 10. Length of shortest period
    //
    // Example:
    // pat = "ababab"
    // period = 2
    //
    // Note:
    // If string is not exactly periodic, returns n
    // =========================================================
    int minimal_period()
    {
        int n = pat.size();

        if(n == 0)
            return 0;

        int p = n - pi[n - 1];

        if(n % p == 0)
            return p;

        return n;
    }

    // =========================================================
    // 11. Check whether pattern/string is periodic
    // =========================================================
    bool is_periodic()
    {
        if(pat.empty())
            return false;

        int n = pat.size();
        int p = n - pi[n - 1];

        return (n % p == 0 && p < n);
    }

    // =========================================================
    // 12. Get all border lengths
    //
    // Example:
    // "aaaa"
    // borders = 3, 2, 1
    // =========================================================
    vector<int> all_borders()
    {
        vector<int> ans;

        if(pat.empty())
            return ans;

        int len = pi.back();

        while(len > 0)
        {
            ans.push_back(len);
            len = pi[len - 1];
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }

    // =========================================================
    // 13. Find occurrences of every prefix
    //
    // freq[len] = how many times prefix of length len
    // appears as a substring
    //
    // Useful in prefix-count / string frequency problems
    // =========================================================
    vector<int> prefix_occurrences()
    {
        int n = pat.size();

        vector<int> freq(n + 1, 0);

        if(n == 0)
            return freq;

        for(int i = 0; i < n; i++)
            freq[pi[i]]++;

        for(int len = n; len > 0; len--)
        {
            if(pi[len - 1] != 0)
                freq[pi[len - 1]] += freq[len];
        }

        for(int len = 1; len <= n; len++)
            freq[len]++;

        return freq;
    }
};


// =============================================================
// MAIN
// =============================================================

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pattern;

    cin >> text >> pattern;

    KMP kmp(pattern);

    // 1. Prefix function
    cout << "Prefix Function: ";
    for(auto x : kmp.pi)
        cout << x << ' ';
    cout << '\n';

    // 2. Contains
    cout << "Contains: "
         << (kmp.contains(text) ? "YES" : "NO") << '\n';

    // 3. First occurrence
    cout << "First occurrence: "
         << kmp.first(text) << '\n';

    // 4. All occurrences
    vector<int> pos = kmp.find_all(text);

    cout << "All occurrences: ";
    for(auto x : pos)
        cout << x << ' ';
    cout << '\n';

    // 5. Number of occurrences
    cout << "Count (overlap): "
         << kmp.count_occurrences(text) << '\n';

    // 6. Number of non-overlapping occurrences
    cout << "Count (non-overlap): "
         << kmp.count_non_overlapping(text) << '\n';

    // 7. Longest border
    cout << "Longest border: "
         << kmp.longest_border() << '\n';

    // 8. Minimal period
    cout << "Minimal period: "
         << kmp.minimal_period() << '\n';

    // 9. Periodic?
    cout << "Periodic: "
         << (kmp.is_periodic() ? "YES" : "NO") << '\n';

    // 10. All borders
    vector<int> borders = kmp.all_borders();

    cout << "All borders: ";
    for(auto x : borders)
        cout << x << ' ';
    cout << '\n';

    return 0;
}
