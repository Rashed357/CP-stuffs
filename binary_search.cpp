int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1; // Initialize the search range

    while (left <= right) {
        int mid = left + (right - left) / 2; // Calculate the middle index to avoid overflow

        if (arr[mid] == target) {
            return mid; // Return the index if target is found
        } else if (arr[mid] < target) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return -1; // Return -1 if the target is not found
}
