#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct Job {
    int id;
    int dead;
    int profit;
};

vector<int> JobScheduling(Job a[], int n) {

    // Sort by profit descending
    sort(a, a + n, [](Job a, Job b) {
        return a.profit > b.profit;
    });

    // Find maximum deadline
    int mx = 0;

    for(int i = 0; i < n; i++) {
        mx = max(mx, a[i].dead);
    }

    // slot[i] = job occupying time slot i
    vector<int> slot(mx + 1, 0);

    int cnt = 0;
    int prof = 0;

    for(int i = 0; i < n; i++) {

        int last = a[i].dead;

        // Put job in the latest available slot
        for(int j = last; j >= 1; j--) {

            if(slot[j] == 0) {

                slot[j] = a[i].id;

                cnt++;
                prof += a[i].profit;

                break;
            }
        }
    }

    return {cnt, prof};
}

int32_t main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    Job a[n];

    for(int i = 0; i < n; i++) {
        cin >> a[i].id >> a[i].dead >> a[i].profit;
    }

    vector<int> ans = JobScheduling(a, n);

    cout << ans[0] << " " << ans[1] << endl;

    return 0;
}
