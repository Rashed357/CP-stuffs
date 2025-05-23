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


//multiply by int
string string_multiply_int(const string &num, int multiplier) {
    if (multiplier == 0 || num == "0") return "0";

    string res = "";
    int carry = 0;

    for (int i = num.size() - 1; i >= 0; --i) {
        int product = (num[i] - '0') * multiplier + carry;
        res += (product % 10) + '0';
        carry = product / 10;
    }

    while (carry) {
        res += (carry % 10) + '0';
        carry /= 10;
    }

    reverse(res.begin(), res.end());
    return res;
}


//multiply by string
string string_multiply(const string &num1, const string &num2) {
    int n = num1.size(), m = num2.size();
    vector<int> result(n + m, 0);

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + result[p2];

            result[p2] = sum % 10;
            result[p1] += sum / 10;
        }
    }

    // Convert result vector to string and remove leading zeros
    string res = "";
    for (int num : result) {
        if (!(res.empty() && num == 0))
            res += (num + '0');
    }

    return res.empty() ? "0" : res;
}

