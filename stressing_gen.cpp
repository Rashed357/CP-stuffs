#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)


const int mod = 1e9+7;
const int mx = 2e5+5;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int my_rand(int l, int r)
{
    return uniform_int_distribution<int>(l, r) (rng);
}
void solve() {
    int n = my_rand(5,5);
    cout<<n<<endl;
    for(int i=1; i<=n; i++){
        int x = my_rand(1,5);
        cout<<x<<' ';
    }
    cout<<endl;
}

int main() {
    fastio;
    //int t; t = my_rand(1,1);cout<<t<<endl; while(t--)
    solve();
    return 0;
}
