#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

class SGT
{
public:
    vector<int> seg;
    SGT(int n){
        seg.resize(4*n+7);
    }
    //each node represents a segment low to high.
    //construct from leaf node.
    void build(int node, int low, int high, int a[]){
        if(low==high){
            seg[node] = a[low];
            return;
        }

        int mid = (low+high)>>1;
        int lf = 2*node;
        int rt = lf+1;
        build(lf,low,mid,a);
        build(rt,mid+1,high,a);
        seg[node] = min(seg[lf],seg[rt]);
    }

    //consider 3 cases.
    int query(int node, int low, int high, int l, int r){
        //overlap
        if(l<=low and high<=r)
            return seg[node];
        //no overlap
        if(high<l or low>r)
            return INT_MAX; //return avoidable value.

        //partial overlap and go both part
        int mid = (low+high)>>1;
        int lf = 2*node;
        int rt = lf+1;

        int x = query(lf,low,mid,l,r);
        int y = query(rt, mid+1,high,l,r);

        return min(x,y);
    }

    //keep going untill reach idx.
    void update(int node, int low, int high, int idx, int val){
        if(low==high){
            seg[node] = val;
            return;
        }

        int mid = (low+high)>>1;

        int lf = 2*node;
        int rt = lf+1;

        if(idx<=mid)
            update(lf,low,mid,idx,val);
        else
            update(rt,mid+1,high,idx,val);

         seg[node] = min(seg[lf],seg[rt]);
    }
    
};

void solve(){

    int n,q;
    cin>>n>>q;
    int a[n+1];
    a[0] = 0;
    for(int i=1; i<=n; i++)
        cin>>a[i];

    SGT obj(n);
    obj.build(1,1,n,a);

    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int idx,val;
            cin>>idx>>val;
            idx++;
            obj.update(1,1,n,idx,val);
        }

        else{
            int l,r;
            cin>>l>>r;
            l++;
            cout<<obj.query(1,1,n,l,r)<<endl;
        }
    }
}

int main() {
    
    ios::sync_with_stdio(false); 
    cin.tie(NULL); cout.tie(NULL);

    //int t; cin>>t; while(t--)
    solve();

    return 0;
}
