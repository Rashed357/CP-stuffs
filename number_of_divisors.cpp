int number_of_divisors(int n) {
    int res = 1;
    while (n > 1) {
        int prime = spf[n];
        int count = 0;
        while (n % prime == 0) {
            n /= prime;
            count++;
        }
        res *= (count + 1);
    }
    return res;
}

//from 1 to n.
#include<bits/stdc++.h>
using namespace std;

int d[104];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n = 100;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      d[j]++;
      // d[j] += i // for sum of divisors
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << d[i] << ' ';
  }
  return 0;
}
