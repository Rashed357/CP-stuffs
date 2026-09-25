```cpp
#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr)

const int N = 1007;

int n, m;

// dist[x][y] = shortest distance from A to (x, y)
// -1 means not visited
int dist[N][N];

// parent[x][y] = previous cell used to reach (x, y)
pair<int, int> parent[N][N];

vector<string> grid;

// Positions of A and B
pair<int, int> A, B;

// Down, Up, Right, Left
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

// Character corresponding to each direction
char moveChar[] = {'D', 'U', 'R', 'L'};


// ------------------------------------------------------------
// Check whether (x, y) is a valid cell to visit
// ------------------------------------------------------------
bool valid(int x, int y)
{
    return x >= 0 && x < n &&
           y >= 0 && y < m &&
           grid[x][y] != '#' &&
           dist[x][y] == -1;
}


// ------------------------------------------------------------
// BFS: find shortest path from A to B
// ------------------------------------------------------------
void bfs()
{
    queue<pair<int, int>> q;

    // Start from A
    dist[A.first][A.second] = 0;
    parent[A.first][A.second] = A;

    q.push(A);

    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        // We can stop once B is reached
        if(make_pair(x, y) == B)
            break;

        for(int dir = 0; dir < 4; dir++)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if(valid(nx, ny))
            {
                // Distance of neighbor
                dist[nx][ny] = dist[x][y] + 1;

                // Remember where we came from
                parent[nx][ny] = {x, y};

                q.push({nx, ny});
            }
        }
    }
}


// ------------------------------------------------------------
// Reconstruct path from B -> A using parent[]
// Then reverse it to get A -> B
// ------------------------------------------------------------
string getPath()
{
    string path;

    pair<int, int> cur = B;

    while(cur != A)
    {
        auto prev = parent[cur.first][cur.second];

        // Find which direction takes prev -> cur
        for(int dir = 0; dir < 4; dir++)
        {
            if(prev.first + dx[dir] == cur.first &&
               prev.second + dy[dir] == cur.second)
            {
                path += moveChar[dir];
                break;
            }
        }

        cur = prev;
    }

    reverse(path.begin(), path.end());

    return path;
}


// ------------------------------------------------------------
// Solve
// ------------------------------------------------------------
void solve()
{
    cin >> n >> m;

    grid.resize(n);

    for(int i = 0; i < n; i++)
    {
        cin >> grid[i];

        for(int j = 0; j < m; j++)
        {
            if(grid[i][j] == 'A')
                A = {i, j};

            if(grid[i][j] == 'B')
                B = {i, j};
        }
    }

    // Initially, nobody is visited
    memset(dist, -1, sizeof(dist));

    // Find shortest path
    bfs();

    // B was never reached
    if(dist[B.first][B.second] == -1)
    {
        cout << "NO\n";
        return;
    }

    // B is reachable
    cout << "YES\n";
    cout << dist[B.first][B.second] << '\n';

    string path = getPath();

    cout << path << '\n';
}


int main()
{
    fastio;

    solve();

    return 0;
}
```
