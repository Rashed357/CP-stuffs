#include <iostream>
#include <vector>
using namespace std;

// DP solution for Partition Problem (Equal Sum Subset)
bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (int num : nums) sum += num;

    // If the total sum is odd, it cannot be partitioned into two equal subsets
    if (sum % 2 != 0) return false;

    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true; // There's always a way to make sum 0 (no elements)

    for (int num : nums) {
        for (int i = target; i >= num; i--) {
            dp[i] = dp[i] || dp[i - num]; // Check if we can make sum i
        }
    }
    return dp[target]; // Return whether we can partition into two equal subsets
}

int main() {
    vector<int> nums = {1, 5, 11, 5}; // Example set
    if (canPartition(nums)) {
        cout << "Can partition into two subsets with equal sum." << endl;
    } else {
        cout << "Cannot partition into two subsets with equal sum." << endl;
    }
    return 0;
}
