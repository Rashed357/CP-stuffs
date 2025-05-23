string add(string a, string b) {
    string res = "";
    int carry = 0;
    int n = max(a.size(), b.size());
    while (a.size() < n) a = '0' + a;
    while (b.size() < n) b = '0' + b;

    for (int i = n - 1; i >= 0; i--) {
        int sum = (a[i]-'0') + (b[i]-'0') + carry;
        carry = sum / 10;
        res += (sum % 10) + '0';
    }
    if (carry) res += carry + '0';
    reverse(res.begin(), res.end());
    return res;
}
