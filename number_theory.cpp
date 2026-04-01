#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

/*---------------------------------------------------
 | 1. BINARY EXPONENTIATION (FAST POWER)
 | Task: Compute (a^b % mod)
 | Time: O(log b)
 ---------------------------------------------------*/
ll binpow(ll a, ll b, ll mod = MOD) {
    a %= mod;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

/*---------------------------------------------------
 | 2. GCD & LCM
 | Task: Find gcd(a,b), lcm(a,b)
 | Time: O(log n)
 ---------------------------------------------------*/
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

/*---------------------------------------------------
 | 3. EXTENDED GCD
 | Task: Solve ax + by = gcd(a,b)
 | Time: O(log n)
 ---------------------------------------------------*/
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

/*---------------------------------------------------
 | 4. MODULAR INVERSE
 | (a) When mod is PRIME → Fermat
 | Time: O(log mod)
 ---------------------------------------------------*/
ll modinv_prime(ll a, ll mod = MOD) {
    return binpow(a, mod - 2, mod);
}

/*---------------------------------------------------
 | (b) General case using Extended GCD
 | Time: O(log n)
 ---------------------------------------------------*/
ll modinv_general(ll a, ll mod) {
    ll x, y;
    ll g = ext_gcd(a, mod, x, y);
    if (g != 1) return -1; // no inverse
    return (x % mod + mod) % mod;
}

/*---------------------------------------------------
 | 5. SIEVE OF ERATOSTHENES
 | Task: Generate primes up to N
 | Time: O(n log log n)
 ---------------------------------------------------*/
vector<bool> is_prime(MAXN, true);
vector<int> primes;

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i < MAXN; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i)
                is_prime[j] = false;
        }
    }
    for (int i = 2; i < MAXN; i++)
        if (is_prime[i]) primes.push_back(i);
}

/*---------------------------------------------------
 | 6. SMALLEST PRIME FACTOR (SPF)
 | Task: Fast factorization
 | Time: O(n log log n)
 ---------------------------------------------------*/
int spf[MAXN];

void build_spf() {
    for (int i = 1; i < MAXN; i++) spf[i] = i;

    for (int i = 2; i * i < MAXN; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAXN; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

/*---------------------------------------------------
 | 7. PRIME FACTORIZATION (using SPF)
 | Task: Factorize n in O(log n)
 ---------------------------------------------------*/
vector<pair<int,int>> factorize(int n) {
    vector<pair<int,int>> res;

    while (n > 1) {
        int p = spf[n], cnt = 0;
        while (spf[n] == p) {
            n /= p;
            cnt++;
        }
        res.push_back({p, cnt});
    }
    return res;
}

/*---------------------------------------------------
 | 8. COUNT DIVISORS
 | Time: O(log n)
 ---------------------------------------------------*/
ll count_divisors(int n) {
    auto f = factorize(n);
    ll ans = 1;
    for (auto [p, e] : f) ans *= (e + 1);
    return ans;
}

/*---------------------------------------------------
 | 9. SUM OF DIVISORS
 | Time: O(log n)
 ---------------------------------------------------*/
ll sum_divisors(int n) {
    auto f = factorize(n);
    ll ans = 1;

    for (auto [p, e] : f) {
        ll term = 1, cur = 1;
        for (int i = 0; i < e; i++) {
            cur *= p;
            term += cur;
        }
        ans *= term;
    }
    return ans;
}

/*---------------------------------------------------
 | 10. EULER TOTIENT (single n)
 | Time: O(sqrt n)
 ---------------------------------------------------*/
ll phi(int n) {
    ll result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

/*---------------------------------------------------
 | 11. TOTIENT SIEVE (1 to N)
 | Time: O(n log log n)
 ---------------------------------------------------*/
vector<int> phi_arr(MAXN);

void phi_sieve() {
    for (int i = 0; i < MAXN; i++) phi_arr[i] = i;

    for (int i = 2; i < MAXN; i++) {
        if (phi_arr[i] == i) {
            for (int j = i; j < MAXN; j += i)
                phi_arr[j] -= phi_arr[j] / i;
        }
    }
}

/*---------------------------------------------------
 | 12. nCr (COMBINATORICS with MOD)
 | Task: Fast combination queries
 | Precompute: O(n)
 | Query: O(1)
 ---------------------------------------------------*/
ll fact[MAXN], invfact[MAXN];

void init_nCr() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i-1] * i % MOD;

    invfact[MAXN-1] = binpow(fact[MAXN-1], MOD-2);
    for (int i = MAXN-2; i >= 0; i--)
        invfact[i] = invfact[i+1] * (i+1) % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n-r] % MOD;
}

/*---------------------------------------------------
 | 13. PRIMALITY TEST (basic)
 | Time: O(sqrt n)
 ---------------------------------------------------*/
bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

/*---------------------------------------------------
 | 14. MODULAR OPERATIONS
 | Time: O(1)
 ---------------------------------------------------*/
ll add(ll a, ll b, ll mod = MOD) {
    return (a + b) % mod;
}

ll sub(ll a, ll b, ll mod = MOD) {
    return (a - b + mod) % mod;
}

ll mul(ll a, ll b, ll mod = MOD) {
    return (a * b) % mod;
}

/*---------------------------------------------------
 | MAIN FUNCTION (TESTING AREA)
 ---------------------------------------------------*/
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // Example usage:

    // sieve();
    // build_spf();
    // init_nCr();

    // cout << binpow(2, 10) << "\n";
    // cout << gcd(12, 18) << "\n";
    // cout << nCr(5, 2) << "\n";

    return 0;
}
