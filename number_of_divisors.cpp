int number_of_divisors(int n) {
    int res = 1;
    while (n > 1) {
        int prime = spf[n];
        int count = 0;
        while (n % prime == 0) {
            n /= prime;
            count++;
        }
        res *= (count + 1);
    }
    return res;
}
