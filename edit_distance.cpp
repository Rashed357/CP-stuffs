#include <iostream>
#include <vector>
#include <string>
using namespace std;

// DP solution for Edit Distance (Levenshtein Distance)
int editDistance(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // DP table

    // Initialize base cases
    for (int i = 0; i <= m; i++) dp[i][0] = i; // Deleting all characters of s1
    for (int j = 0; j <= n; j++) dp[0][j] = j; // Inserting all characters of s2

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No operation needed if characters match
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}); // Take the minimum of insert, remove, replace
            }
        }
    }
    return dp[m][n]; // Return the edit distance
}

int main() {
    string s1 = "sunday";
    string s2 = "saturday";
    cout << "Edit Distance = " << editDistance(s1, s2) << endl;
    return 0;
}
