#include <bits/stdc++.h>
using namespace std;
 
#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define ll long long
 
const int mx = 1007;
bool vis[mx][mx];
int dist[mx][mx];
pair<int,int> parent[mx][mx];
vector<string>v(mx);
int n,m;
pair<int,int> loc_a, loc_b;
 
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
char path[] = {'D','U','R','L'};
 
bool valid(int x, int y){
 
    return (x>=0 && x<n && y>=0 && y<m && dist[x][y]==-1 && v[x][y]!='#');
}
 
 
 
void solve() {
 
    cin>>n>>m;
 
    for(int i=0; i<n; i++)
        cin>>v[i];
 
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(v[i][j]=='A'){
                loc_a.first = i;
                loc_a.second = j;
            }
 
            if(v[i][j] == 'B'){
                loc_b.first = i;
                loc_b.second = j;
            }
        }
    }
 
    memset(dist,-1,sizeof(dist));
    dist[loc_a.first][loc_a.second] = 0;
    parent[loc_a.first][loc_a.second] = loc_a;
    
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
 
    pq.push({0,loc_a});
 
    while(!pq.empty()){
 
        auto it = pq.top();
        pq.pop();
 
        int cur_dist = it.first;
        int x = it.second.first;
        int y = it.second.second;
 
        if(x==loc_b.first && y==loc_b.second)
            break;
 
        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
 
            if(valid(nx,ny)){
                dist[nx][ny] = cur_dist+1;
                parent[nx][ny] = {x,y};
                pq.push({cur_dist+1,{nx,ny}});
            }
        }
    }
 
    if(dist[loc_b.first][loc_b.second]==-1){
        cout<<"NO"<<endl;
        return;
    }
 
    cout<<"YES"<<endl;
    cout<<dist[loc_b.first][loc_b.second]<<endl;
 
    string way = "";
 
    pair<int,int> cur = loc_b;
 
    while(cur!=loc_a){
 
        pair<int,int>prev = parent[cur.first][cur.second];
 
        for(int i=0; i<4; i++){
            if(prev.first+dx[i]==cur.first && prev.second+dy[i]==cur.second){
                way += path[i];
                break;
            }
        }
 
        cur = prev;
    }
 
    reverse(way.begin(),way.end());
 
    cout<<way<<endl;
 
    
}
 
int main() {
    fastio;
 
    solve();
 
    return 0;
}
