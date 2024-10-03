#include <iostream>
#include <vector>
using namespace std;

// DP solution for the Coin Change Problem
int coinChangeWays(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, 0); // DP table
    dp[0] = 1; // There is one way to make amount 0 (using no coins)

    // For each coin, update the number of ways to make every amount
    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }
    return dp[amount]; // Return the number of ways to make the amount
}

int main() {
    vector<int> coins = {1, 2, 5}; // Available coin denominations
    int amount = 11; // Total amount
    cout << "Number of ways to make " << amount << " = " << coinChangeWays(coins, amount) << endl;
    return 0;
}
