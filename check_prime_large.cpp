#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// (a * b) % mod but safe for big numbers
ll mulmod(ll a, ll b, ll mod) {
    ll result = 0;
    a %= mod;
    while (b) {
        if (b & 1) result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

// (base^exp) % mod
ll binpow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// Checks if n is composite using base 'a'
bool check_composite(ll n, ll a, ll d, int s) {
    ll x = binpow(a, d, n);
    if (x == 1 || x == n - 1) return false;

    for (int r = 1; r < s; r++) {
        x = mulmod(x, x, n);
        if (x == n - 1) return false;
    }
    return true;
}

// Miller-Rabin test
bool isPrime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // Deterministic bases up to 1e18
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (ll a : bases) {
        if (a >= n) break;
        if (check_composite(n, a, d, s)) return false;
    }
    return true;
}

int main() {
    ll n;
    cout << "Enter a number: ";
    cin >> n;

    if (isPrime(n)) cout << n << " is prime ✅\n";
    else cout << n << " is not prime ❌\n";

    return 0;
}
