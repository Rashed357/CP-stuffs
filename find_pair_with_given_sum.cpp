// Application: Two-pointer technique is used to find pairs in a sorted array that sum to a given target efficiently in O(n).
bool findPairWithSum(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];

        if (sum == target) {
            cout << "Pair found: (" << arr[left] << ", " << arr[right] << ")" << endl;
            return true;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return false; // No pair found
}
