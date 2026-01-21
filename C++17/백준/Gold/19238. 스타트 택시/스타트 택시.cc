#include <bits/stdc++.h>
using namespace std;

struct Passenger {
    int r, c, dest_r, dest_c;
    bool is_done = false; // 태운 승객 표시
};

int N, M;
long long fuel;
int board[21][21];
vector<Passenger> passengers;
int dx[4] = {-1, 1, 0, 0}; // 상, 하, 좌, 우
int dy[4] = {0, 0, -1, 1};

// 현재 시작점(start_r, start_c)에서 모든 칸까지의 최단 거리 계산
void bfs(int start_r, int start_c, int dist_map[21][21]) {
    for(int i=0; i<N; i++) fill(dist_map[i], dist_map[i]+N, -1);
    
    queue<pair<int, int>> q;
    q.push({start_r, start_c});
    dist_map[start_r][start_c] = 0;

    while(!q.empty()){
        auto [r, c] = q.front(); q.pop();
        for(int i=0; i<4; i++){
            int nr = r + dx[i];
            int nc = c + dy[i];
            if(nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
            if(board[nr][nc] == 1) continue; // 벽
            if(dist_map[nr][nc] != -1) continue; // 이미 방문

            dist_map[nr][nc] = dist_map[r][c] + 1;
            q.push({nr, nc});
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> fuel;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            cin >> board[i][j];

    int taxi_r, taxi_c;
    cin >> taxi_r >> taxi_c;
    taxi_r--; taxi_c--; // 0-base 보정

    for(int i=0; i<M; i++){
        int r, c, dr, dc;
        cin >> r >> c >> dr >> dc;
        passengers.push_back({r-1, c-1, dr-1, dc-1});
    }

    // M명의 승객을 태울 때까지 반복
    for(int i=0; i<M; i++) {
        int dist_map[21][21];
        
        // 1. 택시 위치에서 BFS 수행 (승객 찾기용)
        bfs(taxi_r, taxi_c, dist_map);

        // 2. 가장 가까운 승객 찾기
        int target_idx = -1;
        int min_dist = 2e9;

        for(int k=0; k<M; k++) {
            if(passengers[k].is_done) continue; // 이미 태운 승객 패스

            int p_r = passengers[k].r;
            int p_c = passengers[k].c;
            int dist = dist_map[p_r][p_c];

            if(dist == -1) continue; // 벽 때문에 못 가는 승객

            // 최단 거리 > 행 번호 > 열 번호 우선순위 비교
            if(dist < min_dist) {
                min_dist = dist;
                target_idx = k;
            } else if(dist == min_dist) {
                if(p_r < passengers[target_idx].r) {
                    target_idx = k;
                } else if(p_r == passengers[target_idx].r && p_c < passengers[target_idx].c) {
                    target_idx = k;
                }
            }
        }

        // 태울 수 있는 승객이 없거나 연료 부족 시 종료
        if(target_idx == -1 || fuel < min_dist) {
            cout << -1;
            return 0;
        }

        // 승객에게 이동
        fuel -= min_dist;
        taxi_r = passengers[target_idx].r;
        taxi_c = passengers[target_idx].c;

        // 3. 승객 위치에서 목적지까지 거리 계산
        bfs(taxi_r, taxi_c, dist_map);
        int dest_r = passengers[target_idx].dest_r;
        int dest_c = passengers[target_idx].dest_c;
        int d_dist = dist_map[dest_r][dest_c];

        // 목적지에 도달할 수 없거나 연료 부족 시 종료
        // ★ 중요: d_dist == -1 체크가 반드시 있어야 함
        if(d_dist == -1 || fuel < d_dist) {
            cout << -1;
            return 0;
        }

        // 목적지 도착 및 연료 충전
        fuel -= d_dist;
        fuel += (d_dist * 2);
        
        passengers[target_idx].is_done = true;
        taxi_r = dest_r;
        taxi_c = dest_c;
    }

    cout << fuel;
    return 0;
}