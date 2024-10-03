// Application: Finds the number of divisors of n in O(sqrt(n)) time.
int countDivisors(int n) {
    int count = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i == n / i) {
                count += 1;
            } else {
                count += 2;
            }
        }
    }
    return count;
}
