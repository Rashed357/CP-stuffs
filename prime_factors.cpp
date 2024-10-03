// Application: Finds the prime factorization of a number n in O(sqrt(n)) time.
vector<pair<int, int>> primeFactorization(int n) {
    vector<pair<int, int>> factors;
    for (int p = 2; p * p <= n; p++) {
        int count = 0;
        while (n % p == 0) {
            n /= p;
            count++;
        }
        if (count > 0) {
            factors.push_back({p, count});
        }
    }
    if (n > 1) {
        factors.push_back({n, 1});
    }
    return factors;
}
