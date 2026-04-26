#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(){
    int n; cin >> n;
    vector<string> v(n+1);

    for(int i = 1; i <= n; i++){
        string s; cin >> s;
        v[i] = " " + s;
    }

    int ans = 0;

    for(int i = 1; i <= n/2; i++){
        for(int j = 1; j <= n/2; j++){

            vector<pair<int,int>> cells = {
                {i, j},
                {j, n + 1 - i},
                {n + 1 - i, n + 1 - j},
                {n + 1 - j, i}
            };

            int zero = 0, one = 0;

            for(auto [x, y] : cells){
                if(v[x][y] == '0') zero++;
                else one++;
            }

            ans += min(zero, one);
        }
    }

    // middle layer when n is odd
    if(n % 2){
        int mid = (n + 1) / 2;

        for(int j = 1; j <= n/2; j++){
            vector<pair<int,int>> cells = {
                {mid, j},
                {j, mid},
                {mid, n + 1 - j},
                {n + 1 - j, mid}
            };

            int zero = 0, one = 0;

            for(auto [x, y] : cells){
                if(v[x][y] == '0') zero++;
                else one++;
            }

            ans += min(zero, one);
        }
    }

    cout << ans << '\n';
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while(t--) solve();
}

problem : https://codeforces.com/contest/1703/problem/E
