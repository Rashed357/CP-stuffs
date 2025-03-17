#include <bits/stdc++.h>
#include <cassert>
using namespace std;

#define endl '\n'
#define ll long long

// Maximum size for precomputed arrays (should be greater than maximum string length)
const int N = 1e6 + 9;
// Bases and moduli for double hashing
const int p1 = 137, mod1 = 127657753;
const int p2 = 277, mod2 = 987654319;

// Fast modular exponentiation: computes b^p mod mod correctly.
ll power(ll b, ll p, ll mod) {
    ll ans = 1;
    b %= mod;
    if (b < 0)
        b += mod;
    while (p) {
        if (p & 1)
            ans = (ans * b) % mod;
        b = (b * b) % mod;  // Always square b
        p /= 2;
    }
    return ans;
}

// Global arrays for storing powers and inverse powers for both hash functions
// pw[i] = (p1^i mod mod1, p2^i mod mod2)
pair<ll,ll> pw[N];
// ipw[i] = (inverse of p1^i mod mod1, inverse of p2^i mod mod2)
pair<ll,ll> ipw[N];

// Precompute the powers and inverse powers for the bases.
void prec(){
    // Initialize the zeroth power to 1
    pw[0] = {1, 1};
    for (int i = 1; i < N; i++){
        pw[i].first = (pw[i-1].first * p1) % mod1;
        pw[i].second = (pw[i-1].second * p2) % mod2;
    }

    // Compute modular inverses for p1 and p2 using Fermat's little theorem
    ll inv_p1 = power(p1, mod1 - 2, mod1);
    ll inv_p2 = power(p2, mod2 - 2, mod2);

    // Precompute inverse powers
    ipw[0] = {1, 1};
    for (int i = 1; i < N; i++){
        ipw[i].first = (ipw[i-1].first * inv_p1) % mod1;
        ipw[i].second = (ipw[i-1].second * inv_p2) % mod2;  // Corrected: use inv_p2 here.
    }
}

// Compute the hash of an entire string 's' (normalized as if starting at index 0)
pair<ll,ll> string_hash(string &s){
    pair<ll,ll> val = {0, 0};
    int n = s.size();
    for (int i = 0; i < n; i++){
        // Multiply character's ASCII value by the corresponding power.
        val.first = (val.first + s[i] * pw[i].first) % mod1;
        val.second = (val.second + s[i] * pw[i].second) % mod2;
    }
    return val;
}

// Global prefix hash array for string 'a'
// pref[i] stores hash of the substring a[0...i] (non-normalized)
pair<ll,ll> pref[N];

// Build the prefix hash array for string 's'
void build(string &s){
    int n = s.size();
    // For the first character, the hash is simply the character times pw[0] (which is 1)
    pref[0].first = (s[0] * pw[0].first) % mod1;
    pref[0].second = (s[0] * pw[0].second) % mod2;
    for (int i = 1; i < n; i++){
        // Current character's contribution at position i
        ll cur1 = (s[i] * pw[i].first) % mod1;
        ll cur2 = (s[i] * pw[i].second) % mod2;
        // Add to previous prefix hash
        pref[i].first = (pref[i-1].first + cur1) % mod1;
        pref[i].second = (pref[i-1].second + cur2) % mod2;
    }
}

// Compute the hash of the substring s[i...j] and normalize it (divide by p^i)
pair<ll,ll> sub_hash(int i, int j){
    assert(i <= j); // Ensure valid indices
    pair<ll,ll> val;
    
    // Calculate hash for first component
    val.first = pref[j].first;
    if(i > 0)
        val.first = (val.first - pref[i-1].first + mod1) % mod1;
    // Normalize by dividing by p^i (i.e. multiply by inverse power)
    val.first = (val.first * ipw[i].first) % mod1;
    
    // Calculate hash for second component
    val.second = pref[j].second;
    if(i > 0)
        val.second = (val.second - pref[i-1].second + mod2) % mod2;
    // Normalize by dividing by p^i
    val.second = (val.second * ipw[i].second) % mod2;
    
    return val;
}

// Solve the problem: count the number of positions where the pattern occurs in the text.
void solve(){
    string a, b;
    cin >> a >> b;
    int n = a.size();
    int m = b.size();
    
    // Precompute the powers and inverse powers needed for hashing.
    prec();
    
    // Build the prefix hash for the text string 'a'
    build(a);
    
    // Compute the hash of the pattern string 'b' (this is already normalized for index 0)
    pair<ll,ll> hashB = string_hash(b);
    
    ll cnt = 0;
    // Check every possible starting index in 'a' for a substring of length m
    for (int i = 0; i <= n - m; i++){
        // Get the normalized hash of the substring a[i...i+m-1]
        pair<ll,ll> hashA = sub_hash(i, i + m - 1);
        if (hashA == hashB)
            cnt++;
    }
    
    cout << cnt << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
    return 0;
}
