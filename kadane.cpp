// Returns: {max_sum, left_index, right_index}
tuple<long long, int, int> kadane(vector<long long> &a) {
    int n = a.size();
    
    long long max_sum = a[0];
    long long cur_sum = a[0];
    
    int l = 0, r = 0;      // final answer range
    int temp_l = 0;        // temporary start
    
    for (int i = 1; i < n; i++) {
        if (cur_sum + a[i] < a[i]) {
            cur_sum = a[i];
            temp_l = i;
        } else {
            cur_sum += a[i];
        }
        
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
            l = temp_l;
            r = i;
        }
    }
    
    // converting to 1-based index
    return {max_sum, l + 1, r + 1};
}
