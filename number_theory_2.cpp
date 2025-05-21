//divisibility by large numbers
#include<bits/stdc++.h>
using namespace std;

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string a; int b; cin >> a >> b;
  int ans = 0;
  for (int i = 0; i < a.size(); i++) {
    ans = (ans * 10LL % b + (a[i] - '0')) % b;
  }
  // ans = a % b;
  if (ans == 0) {
    cout << "a is divisible by b\n";
  }
  else {
    cout << "sad\n";
  }
  return 0;
}



// count of x such that p^x divides n
#include<bits/stdc++.h>
using namespace std;

int legendre(long long n, long long p) {
  int ans = 0;
  while (n) {
    ans += n / p;
    n /= p;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  return 0;
}

//big gcd
int gcd(int a, string b) {
    int mod = 0;
    for (char ch : b) {
        mod = (mod * 10 + (ch - '0')) % a;
    }
    return __gcd(a, mod);
}
