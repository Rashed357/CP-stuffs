#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'



const int N = 1e5 + 9;

int a[N];

struct ST {
  vector<int>t;
  int sz;
  ST(int n) {
   sz = n+1;
   t.resize(4*n,0);
  }

  void build(int n, int b, int e) {
    if (b == e) {
      t[n] = a[b];
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    t[n] = t[l] + t[r]; // Sum segment tree
  }

  void upd(int n, int b, int e, int i, int x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[n] = x; // Update value
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    upd(l, b, mid, i, x);
    upd(r, mid + 1, e, i, x);
    t[n] = t[l] + t[r]; // Update parent nodes
  }

  int query(int n, int b, int e, int i, int j) {
    if (b > j || e < i) return 0; // Return neutral element for sum
    if (b >= i && e <= j) return t[n]; // Fuinty inside range
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    int lq = query(l, b, mid, i, j);
    int rq = query(r, mid + 1, e, i, j);
    return lq + rq; // Sum of left and right parts
  }
};

void solve(){
    int n; cin>>n;
    int m; cin>>m;
    for(int i = 1; i<=n; i++){
      cin>>a[i];
    }

   ST obj(n);
   obj.build(1,1,n);

   while(m--){
      int t; cin>>t;
      if(t==1){
         int id,v;
         cin>>id>>v;
         id++;
         obj.upd(1,1,n,id,v);
      }
      else{
         int l,r;
         cin>>l>>r;
         l++;
         r++;
         cout << obj.query(1,1,n,l,r-1) << endl;
      }
   }
}

int32_t main(){
   ios::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);
   //return 0;
   //int t; cin >> t; while(t--)
   solve();

   return 0;
}
