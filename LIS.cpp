int longestIncreasingSubsequence(vector<int>& nums) {
    if (nums.empty()) return 0; // Handle empty input
    
    int n = nums.size();
    vector<int> dp(n, 1); // Initialize dp array, where dp[i] is the length of LIS ending at i

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1); // Update LIS length at i
            }
        }
    }

    return *max_element(dp.begin(), dp.end()); // Return the maximum value in dp array
}
