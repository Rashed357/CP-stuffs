// Application: Computes the sum of digits of a number.
int sumOfDigits(int n) {
    int sum = 0;
    while (n) {
        sum += n % 10; // Add the last digit to the sum
        n /= 10; // Remove the last digit
    }
    return sum;
}
