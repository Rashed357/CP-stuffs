#include <bits/stdc++.h>
using namespace std;

class StringHash
{
    int p1 = 137, mod1 = 127657753;
    int p2 = 277, mod2 = 987654319;

    vector<pair<int,int>> pw, ipw;
    vector<pair<int,int>> pref;

    int power(long long a, long long b, int mod)
    {
        long long ans = 1;

        while(b)
        {
            if(b & 1)
                ans = ans * a % mod;

            a = a * a % mod;
            b >>= 1;
        }

        return ans;
    }

public:

    StringHash(string &s)
    {
        int n = s.size();

        pw.resize(n);
        ipw.resize(n);
        pref.resize(n);

        pw[0] = {1, 1};

        for(int i = 1; i < n; i++)
        {
            pw[i].first = 1LL * pw[i-1].first * p1 % mod1;
            pw[i].second = 1LL * pw[i-1].second * p2 % mod2;
        }

        int ip1 = power(p1, mod1 - 2, mod1);
        int ip2 = power(p2, mod2 - 2, mod2);

        ipw[0] = {1, 1};

        for(int i = 1; i < n; i++)
        {
            ipw[i].first = 1LL * ipw[i-1].first * ip1 % mod1;
            ipw[i].second = 1LL * ipw[i-1].second * ip2 % mod2;
        }

        for(int i = 0; i < n; i++)
        {
            pref[i].first =
                1LL * s[i] * pw[i].first % mod1;

            pref[i].second =
                1LL * s[i] * pw[i].second % mod2;

            if(i)
            {
                pref[i].first =
                    (pref[i].first + pref[i-1].first) % mod1;

                pref[i].second =
                    (pref[i].second + pref[i-1].second) % mod2;
            }
        }
    }

    pair<int,int> get_hash(int l, int r)
    {
        int h1 = pref[r].first;
        int h2 = pref[r].second;

        if(l)
        {
            h1 = (h1 - pref[l-1].first + mod1) % mod1;
            h2 = (h2 - pref[l-1].second + mod2) % mod2;
        }

        h1 = 1LL * h1 * ipw[l].first % mod1;
        h2 = 1LL * h2 * ipw[l].second % mod2;

        return {h1, h2};
    }
};

int main()
{
    string s = "abracadabra";

    StringHash hs(s);

    auto a = hs.get_hash(0, 2);
    auto b = hs.get_hash(7, 9);

    if(a == b)
        cout << "Same\n";
    else
        cout << "Different\n";
}
