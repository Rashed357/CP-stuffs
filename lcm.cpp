// Application: LCM is used to find the least common multiple of two numbers using the relation LCM(a, b) = |a * b| / GCD(a, b).
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}
