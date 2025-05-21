const int N = 1e6 + 5;
int spf[N];

void sieve_spf() {
    for (int i = 2; i < N; ++i) {
        if (spf[i] == 0) { // i is prime
            for (int j = i; j < N; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}

vector<int> get_factors(int n) {
    vector<int> res;
    while (n > 1) {
        res.push_back(spf[n]);
        n /= spf[n];
    }
    return res;
}

