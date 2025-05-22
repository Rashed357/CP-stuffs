#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first < b.first; // only compare first element
}

int main() {
    vector<pair<int, int>> vp = {{1, 2}, {2, 3}, {2, 5}, {4, 1}};
    sort(vp.begin(), vp.end(), cmp); // sort using the same comparator

    // Custom lower_bound
    pair<int, int> target = {2, INT_MIN}; // second doesn't matter
    auto it = lower_bound(vp.begin(), vp.end(), target, cmp);

    if (it != vp.end())
        cout << "Found: (" << it->first << ", " << it->second << ")\n";
    else
        cout << "Not found\n";

    return 0;
}
