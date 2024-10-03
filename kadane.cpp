// Application: Kadane’s Algorithm is used to find the maximum sum of a contiguous subarray in O(n).
int maxSubArraySum(vector<int>& arr) {
    int max_sum = INT_MIN, current_sum = 0;

    for (int num : arr) {
        current_sum = max(num, current_sum + num);
        max_sum = max(max_sum, current_sum);
    }

    return max_sum;
}
