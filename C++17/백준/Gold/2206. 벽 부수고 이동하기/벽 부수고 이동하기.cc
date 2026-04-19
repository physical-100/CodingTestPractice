#include<bits/stdc++.h>
using namespace std;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};
char board[1001][1001];
int dist[1001][1001][2];
int n,m;
int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >>m ;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>board[i][j];
            //dist[i][j][0]=dist[i][j][1]=-1;
            }
    }
    queue<tuple<int,int,int>> Q;
    dist[0][0][0]=1;
    //dist[0][0][1]=1;
    Q.push({0,0,0});
    while(!Q.empty()){
        auto [x,y,broken] = Q.front();
        Q.pop();
        if(x==n-1&&y==m-1){
            cout <<dist[x][y][broken] ;
            return 0;
        }
        int nextdist = dist[x][y][broken]+1;
        for(int dir=0;dir<4;dir++){
            int nx = x+dx[dir];
            int ny = y+dy[dir];
            //먼저 조건을 확인
            if(nx<0||ny<0||nx>=n||ny>=m) continue;
            //벽을 깨지 않을 때
            if(board[nx][ny]=='0' && dist[nx][ny][broken]==0){
                dist[nx][ny][broken] = nextdist;
                Q.push({nx,ny,broken});
            }
            if(!broken && board[nx][ny]=='1' && dist[nx][ny][broken]==0){
                dist[nx][ny][1] = nextdist;
                Q.push({nx,ny,1});
            }
        }
    }
    cout <<"-1"; 
    return 0;
}