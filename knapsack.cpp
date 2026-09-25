// Application: Solves the 0/1 Knapsack problem where we maximize value without exceeding weight capacity.
int knapsack(vector<int>& weights, vector<int>& values, int W) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0)); // DP table

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W]; // Max value that can be achieved
}


#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1005;
const int W = 10005;

int n, capacity;
int wt[N], val[N];
int dp[N][W];

int solve(int i, int rem)
{
    // Base case
    if(i == n)
        return 0;

    // Already calculated
    if(dp[i][rem] != -1)
        return dp[i][rem];

    // Don't take current item
    int ans = solve(i + 1, rem);

    // Take current item
    if(wt[i] <= rem)
    {
        ans = max(ans,
                  val[i] + solve(i + 1, rem - wt[i]));
    }

    return dp[i][rem] = ans;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> capacity;

    for(int i = 0; i < n; i++)
        cin >> wt[i] >> val[i];

    memset(dp, -1, sizeof(dp));

    cout << solve(0, capacity) << '\n';

    return 0;
}

vector<int> dp(W + 1);
for(int i = 0; i < n; i++)
    for(int w = W; w >= wt[i]; w--)
        dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
