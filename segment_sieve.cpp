// Application: Finds all primes in the range [L, R] using a segmented sieve in O((R - L + 1) log log R) time.
vector<int> segmentedSieve(int L, int R) {
    int limit = sqrt(R) + 1;
    vector<bool> isPrime = sieve(limit);
    vector<bool> isPrimeSegment(R - L + 1, true);

    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
                isPrimeSegment[j - L] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = L; i <= R; i++) {
        if (isPrimeSegment[i - L] && i > 1) {
            primes.push_back(i);
        }
    }
    return primes;
}
