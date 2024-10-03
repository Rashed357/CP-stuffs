// Application: GCD is used to find the greatest common divisor of two integers in O(log(min(a, b))).
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
