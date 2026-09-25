#include <bits/stdc++.h>
using namespace std;

// Coins can be used multiple times (Unbounded)
int minCoinsMultiple(const vector<int>& coins, int amount) {
    const int INF = amount + 1;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int coin : coins) {
        for (int i = coin; i <= amount; ++i) {
            if (dp[i - coin] != INF) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INF ? -1 : dp[amount];
}

// Each coin can be used at most once (0/1)
int minCoinsOnce(const vector<int>& coins, int amount) {
    const int INF = amount + 1;
    vector<int> dp(amount + 1, INF);
    dp[0] = 0;

    for (int coin : coins) {
        for (int i = amount; i >= coin; --i) {
            if (dp[i - coin] != INF) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INF ? -1 : dp[amount];
}

int main() {
    vector<int> coins = {1, 2, 5};
    int amount = 11;

    cout << minCoinsMultiple(coins, amount) << "\n";
    cout << minCoinsOnce(coins, amount) << "\n";

    return 0;
}
