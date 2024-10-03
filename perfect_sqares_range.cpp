// Application: Finds the count of perfect squares in the range [L, R].
int countPerfectSquares(int L, int R) {
    return floor(sqrt(R)) - ceil(sqrt(L)) + 1;
}
