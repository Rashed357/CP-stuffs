//contrast stretching, background slicing
#include <iostream>
using namespace std;

int main() {
    const int SIZE = 3;
    int img[SIZE][SIZE];

    cout << "Enter 3x3 pixel intensity values (0-255):\n";

    int mn = 255, mx = 0;

    // Input
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> img[i][j];

            if (img[i][j] < mn) mn = img[i][j];
            if (img[i][j] > mx) mx = img[i][j];
        }
    }

    // Original Image
    cout << "\nOriginal Pixel Intensities:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << img[i][j] << "\t";
        cout << endl;
    }

    // -----------------------------
    // (a) Contrast Stretching
    // -----------------------------
    int contrast[SIZE][SIZE];

    if (mx == mn) {
        // Avoid division by zero
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                contrast[i][j] = img[i][j];
    } else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                contrast[i][j] = (img[i][j] - mn) * 255 / (mx - mn);
            }
        }
    }

    cout << "\nAfter Contrast Stretching:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << contrast[i][j] << "\t";
        cout << endl;
    }

    // -----------------------------
    // (b) Intensity Slicing
    // Range: 100 - 180
    // -----------------------------
    int low = 100, high = 180;

    int preserve[SIZE][SIZE];
    int highlight[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            // Background Preserving
            if (img[i][j] >= low && img[i][j] <= high)
                preserve[i][j] = 255;
            else
                preserve[i][j] = img[i][j];

            // Background Highlighting
            if (img[i][j] >= low && img[i][j] <= high)
                highlight[i][j] = 255;
            else
                highlight[i][j] = 0;
        }
    }

    cout << "\nIntensity Slicing (Background Preserving):\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << preserve[i][j] << "\t";
        cout << endl;
    }

    cout << "\nIntensity Slicing (Background Highlighting):\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << highlight[i][j] << "\t";
        cout << endl;
    }

    return 0;
}


//adjacency, connectiviy, path
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 5;

int img[N][N];
bool vis[N][N];

// 4-direction
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

//-------------------------------------
// (a) Connectivity
//-------------------------------------
bool isConnected(int sx, int sy, int ex, int ey) {

    if (img[sx][sy] != 1 || img[ex][ey] != 1)
        return false;

    queue<pair<int,int>> q;
    q.push({sx, sy});
    vis[sx][sy] = true;

    while(!q.empty()){

        auto cur = q.front();
        q.pop();

        int x = cur.first;
        int y = cur.second;

        if(x == ex && y == ey)
            return true;

        for(int k=0;k<4;k++){

            int nx = x + dx[k];
            int ny = y + dy[k];

            if(nx>=0 && nx<N && ny>=0 && ny<N &&
               !vis[nx][ny] && img[nx][ny]==1){

                vis[nx][ny]=true;
                q.push({nx,ny});
            }
        }
    }

    return false;
}

//-------------------------------------
// (b) Adjacency
//-------------------------------------
bool isAdjacent(int x1,int y1,int x2,int y2){

    int d = abs(x1-x2)+abs(y1-y2);

    return d==1;      // 4-adjacent
}

//-------------------------------------
// (c) Path
//-------------------------------------
void printPath(int sx,int sy,int ex,int ey){

    queue<pair<int,int>> q;

    bool visited[N][N]={0};
    pair<int,int> parent[N][N];

    q.push({sx,sy});
    visited[sx][sy]=true;
    parent[sx][sy]={-1,-1};

    while(!q.empty()){

        auto cur=q.front();
        q.pop();

        int x=cur.first;
        int y=cur.second;

        if(x==ex && y==ey)
            break;

        for(int k=0;k<4;k++){

            int nx=x+dx[k];
            int ny=y+dy[k];

            if(nx>=0 && nx<N && ny>=0 && ny<N &&
               !visited[nx][ny] && img[nx][ny]==1){

                visited[nx][ny]=true;
                parent[nx][ny]={x,y};
                q.push({nx,ny});
            }
        }
    }

    if(!visited[ex][ey]){
        cout<<"No Path Exists\n";
        return;
    }

    vector<pair<int,int>> path;

    int x=ex,y=ey;

    while(x!=-1){

        path.push_back({x,y});

        auto p=parent[x][y];

        x=p.first;
        y=p.second;
    }

    reverse(path.begin(),path.end());

    cout<<"Path:\n";

    for(auto p:path)
        cout<<"("<<p.first<<","<<p.second<<") ";
    cout<<endl;
}

int main(){

    cout<<"Enter 5x5 matrix (0/1):\n";

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            cin>>img[i][j];

    int sx,sy,ex,ey;

    cout<<"\nEnter source pixel (row col): ";
    cin>>sx>>sy;

    cout<<"Enter destination pixel (row col): ";
    cin>>ex>>ey;

    //---------------- Connectivity ----------------
    if(isConnected(sx,sy,ex,ey))
        cout<<"\nConnected\n";
    else
        cout<<"\nNot Connected\n";

    //---------------- Adjacency ----------------
    if(isAdjacent(sx,sy,ex,ey))
        cout<<"Adjacent (4-neighbor)\n";
    else
        cout<<"Not Adjacent\n";

    //---------------- Path ----------------
    printPath(sx,sy,ex,ey);

    return 0;
}


//Equalization and matching
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int SIZE = 3;
const int LEVEL = 8; // Intensity levels: 0-7

int main() {

    int img[SIZE][SIZE];

    cout << "Enter 3x3 image (values 0-7):\n";

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            cin>>img[i][j];

    //---------------- Histogram ----------------

    int hist[LEVEL]={0};

    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            hist[img[i][j]]++;

    cout<<"\nHistogram\n";

    for(int i=0;i<LEVEL;i++)
        cout<<i<<" : "<<hist[i]<<endl;

    //---------------- Equalization ----------------

    int total=SIZE*SIZE;

    float pdf[LEVEL];
    float cdf[LEVEL];

    for(int i=0;i<LEVEL;i++)
        pdf[i]=(float)hist[i]/total;

    cdf[0]=pdf[0];

    for(int i=1;i<LEVEL;i++)
        cdf[i]=cdf[i-1]+pdf[i];

    int mapEq[LEVEL];

    for(int i=0;i<LEVEL;i++)
        mapEq[i]=round((LEVEL-1)*cdf[i]);

    cout<<"\nEqualization Mapping\n";

    for(int i=0;i<LEVEL;i++)
        cout<<i<<" -> "<<mapEq[i]<<endl;

    cout<<"\nEqualized Image\n";

    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++)
            cout<<mapEq[img[i][j]]<<" ";
        cout<<endl;
    }

    //---------------- Matching ----------------

    cout<<"\nEnter Target Histogram ("<<LEVEL<<" values):\n";

    int targetHist[LEVEL];

    for(int i=0;i<LEVEL;i++)
        cin>>targetHist[i];

    float targetPDF[LEVEL], targetCDF[LEVEL];

    for(int i=0;i<LEVEL;i++)
        targetPDF[i]=(float)targetHist[i]/total;

    targetCDF[0]=targetPDF[0];

    for(int i=1;i<LEVEL;i++)
        targetCDF[i]=targetCDF[i-1]+targetPDF[i];

    int mapMatch[LEVEL];

    for(int i=0;i<LEVEL;i++){

        float mn=1000;

        for(int j=0;j<LEVEL;j++){

            if(fabs(cdf[i]-targetCDF[j])<mn){

                mn=fabs(cdf[i]-targetCDF[j]);
                mapMatch[i]=j;
            }
        }
    }

    cout<<"\nMatching Mapping\n";

    for(int i=0;i<LEVEL;i++)
        cout<<i<<" -> "<<mapMatch[i]<<endl;

    cout<<"\nMatched Image\n";

    for(int i=0;i<SIZE;i++){

        for(int j=0;j<SIZE;j++)
            cout<<mapMatch[img[i][j]]<<" ";

        cout<<endl;
    }

    return 0;
}



//high pass filter
#include <iostream>
using namespace std;

const int N = 5;

int main() {

    int img[N][N];

    cout << "Enter 5x5 image matrix:\n";

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            cin>>img[i][j];

    int kernel[3][3]={
        {-1,-1,-1},
        {-1, 8,-1},
        {-1,-1,-1}
    };

    int output[N][N]={0};

    // Ignore border pixels
    for(int i=1;i<N-1;i++){

        for(int j=1;j<N-1;j++){

            int sum=0;

            for(int x=-1;x<=1;x++){

                for(int y=-1;y<=1;y++){

                    sum += img[i+x][j+y] * kernel[x+1][y+1];

                }
            }

            // Clamp values between 0 and 255
            if(sum<0) sum=0;
            if(sum>255) sum=255;

            output[i][j]=sum;
        }
    }

    cout<<"\nOutput after High Pass Filter:\n";

    for(int i=0;i<N;i++){

        for(int j=0;j<N;j++)
            cout<<output[i][j]<<" ";

        cout<<endl;
    }

    return 0;
}
