// Application: Finds modular inverse of a under mod m using Fermat’s Little Theorem in O(log m) time.
int modInverseFermat(int a, int m) {
    return modExp(a, m - 2, m); // a^(m-2) % m is the modular inverse when m is prime
}
