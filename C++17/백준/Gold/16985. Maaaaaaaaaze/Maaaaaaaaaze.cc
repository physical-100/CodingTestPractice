#include <bits/stdc++.h>
using namespace std;

int dx[6] = {1,-1,0,0,0,0};
int dy[6] = {0,0,1,-1,0,0};
int dz[6] = {0,0,0,0,1,-1};

int board[5][5][5][4]; // [layer][x][y][rotation]
int ans = 1e9;

/* 90도 회전 */
void rotate_layer(int layer, int r){
    int tmp[5][5];
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            tmp[i][j] = board[layer][i][j][r-1];

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            board[layer][j][4-i][r] = tmp[i][j];
}

/* BFS 최단거리 */
void bfs(const vector<int>& order, const vector<int>& rot){
    // 시작/끝 불가능
    if(!board[order[0]][0][0][rot[0]]) return;
    if(!board[order[4]][4][4][rot[4]]) return;

    int dist[5][5][5];
    memset(dist, -1, sizeof(dist));

    queue<tuple<int,int,int>> q;
    q.push({0,0,0});
    dist[0][0][0] = 0;

    while(!q.empty()){
        auto [x,y,z] = q.front(); q.pop();

        if(dist[x][y][z] >= ans) return;

        if(x==4 && y==4 && z==4){
            ans = min(ans, dist[x][y][z]);
            return;
        }

        for(int d=0; d<6; d++){
            int nx = x + dx[d];
            int ny = y + dy[d];
            int nz = z + dz[d];

            if(nx<0||ny<0||nz<0||nx>=5||ny>=5||nz>=5) continue;
            if(dist[nx][ny][nz] != -1) continue;

            int layer = order[nx];
            int r = rot[nx];

            if(!board[layer][ny][nz][r]) continue;

            dist[nx][ny][nz] = dist[x][y][z] + 1;
            q.push({nx,ny,nz});
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 입력
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            for(int k=0;k<5;k++)
                cin >> board[i][j][k][0];

    // 회전 미리 계산
    for(int i=0;i<5;i++)
        for(int r=1;r<4;r++)
            rotate_layer(i, r);

    vector<int> order = {0,1,2,3,4};
    vector<int> rot(5);

    do{
        for(rot[0]=0;rot[0]<4;rot[0]++)
        for(rot[1]=0;rot[1]<4;rot[1]++)
        for(rot[2]=0;rot[2]<4;rot[2]++)
        for(rot[3]=0;rot[3]<4;rot[3]++)
        for(rot[4]=0;rot[4]<4;rot[4]++){
            bfs(order, rot);
            if(ans == 12){ // 최단 가능값
                cout << 12;
                return 0;
            }
        }
    } while(next_permutation(order.begin(), order.end()));

    if(ans == 1e9) cout << -1;
    else cout << ans;
    return 0;
}
