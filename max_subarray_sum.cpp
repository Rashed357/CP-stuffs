// Application: Sliding window is used to find maximum sum of a subarray of fixed size k in O(n).
int maxSumSubarray(vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return -1;

    // Find the sum of the first window
    int max_sum = 0;
    for (int i = 0; i < k; i++) {
        max_sum += arr[i];
    }

    int window_sum = max_sum;

    // Slide the window over the array
    for (int i = k; i < n; i++) {
        window_sum += arr[i] - arr[i - k];
        max_sum = max(max_sum, window_sum);
    }

    return max_sum;
}
