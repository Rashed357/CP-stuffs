// Application: Checks if a number is a palindrome.
bool isPalindrome(int n) {
    int original = n, reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + n % 10; // Construct the reversed number
        n /= 10; // Remove the last digit
    }
    return original == reversed; // Check if the original and reversed are the same
}
