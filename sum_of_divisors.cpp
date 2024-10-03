// Application: Finds the sum of all divisors of n in O(sqrt(n)) time.
int sumDivisors(int n) {
    int sum = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i == n / i) {
                sum += i;
            } else {
                sum += i + n / i;
            }
        }
    }
    return sum;
}
