__int128 stoint128(string s) {
    __int128 x = 0;
    for(char c : s)
        x = x * 10 + (c - '0');
    return x;
}

string toString(__int128 x) {
    if(x == 0) return "0";

    bool neg = x < 0;
    if(neg) x = -x;

    string s;
    while(x) {
        s += '0' + x % 10;
        x /= 10;
    }

    if(neg) s += '-';

    reverse(s.begin(), s.end());
    return s;
}
