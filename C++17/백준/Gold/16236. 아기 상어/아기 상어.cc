#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
/*
물고기 M 마리 아기 상어 1마리  
한 칸에는 최대 1마리 존재 
아기 상어 초기 크기 : 2 (1초에 상하좌우로 인접한 한 칸 이동)
크기가 같은 물고기는 먹을 수 없지만  해당 칸 지나갈 수는 있음
이동 방법
    1. 물고기가 공간에 없으면 엄마에게 도움 
    2. 물고기가 1마리라면 물고기를 먹으러 간다 
    3. 1마리 이상의 물고기라면 거리가 가장 가까운 물고기를 먹으러 간다. 
        거리 : 칸의 최솟값
        거리가 동일 -> 위 , 왼쪽 우선 순위 
물고기의 섭취와 이동은 동시에 이뤄짐 

아기 상어 -> 자신의 크기와 같은 수의 물고기를 먹을 때마다 크기가 1증가 

몇 초 동안 엄마 상어에게 도움을 요청하지 않고 물고기를 먹을 수 있는지 구하라

*/
int  cnt,N,eating;// eating는 잡아먹은 물고기의 수 , cnt : 시간 ,N : 영역 크기 
int shark_sz = 2;

int dx[4] = {1, 0, -1, 0}; // 상, 좌, 하, 우 순서 (약간의 최적화)
int dy[4] = {0, 1, 0, -1};

int board[21][21];
int dist[21][21];

pair<int, int> s_pos;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 9) {
                s_pos = {i, j};
                board[i][j] = 0; // [중요] 시작 위치는 반드시 0으로 비워야 함
            }
        }
    }

    while (true) {
        memset(dist, -1, sizeof(dist));
        bool can_Eat = false; // 지역 변수로 변경 권장
        queue<pair<int, int>> q;
        
        q.push({s_pos.X, s_pos.Y});
        dist[s_pos.X][s_pos.Y] = 0;
        
        tuple<int,int,int> min_val  = {401,401,401};

        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            auto [d,x,y] = min_val;
            // [중요] 이미 찾은 최소 거리보다 더 멀리 탐색할 필요 없음
            if (dist[cur.X][cur.Y] >= d) break; 

            for (int dir = 0; dir < 4; dir++) {
                int nx = cur.X + dx[dir];
                int ny = cur.Y + dy[dir];

                if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
                if (dist[nx][ny] >= 0 || board[nx][ny] > shark_sz) continue;

                dist[nx][ny] = dist[cur.X][cur.Y] + 1;

                // 먹을 수 있는 물고기 발견
                if (board[nx][ny] > 0 && board[nx][ny] < shark_sz) {
                    min_val = min(min_val , {dist[nx][ny],nx,ny});
                }
                q.push({nx, ny});
            }
        }

        // 더 이상 먹을 물고기가 없으면 종료
        auto [d,x,y] = min_val;
        if (d==401)  break;

        //물고기 처리 및 상어 이동
        cnt += d;           // 이동 시간 더하기
        board[x][y] = 0; // 물고기 냠냠 (맵에서 지우기)
        s_pos = {x,y};       // 상어 위치 이동
        
        eating++;
        if (eating == shark_sz) {
            shark_sz++;
            eating = 0;
        }
    }

    cout << cnt;
    return 0;
}