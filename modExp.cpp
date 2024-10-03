// Application: Efficiently calculates a^b % m in O(log b) using exponentiation by squaring.
int modExp(int a, int b, int m) {
    int res = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res * a) % m;
        }
        a = (a * a) % m;
        b /= 2;
    }
    return res;
}
