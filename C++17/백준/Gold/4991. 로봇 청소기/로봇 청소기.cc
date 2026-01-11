#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second 
/*
유저가 직접 경로 설정 가능
한번 움직일때 인접한 칸으로 이동 가능하며 같은 칸을 여러 번 방문가능 
필요한 이동 횟수의 최솟값을 구하는 프로그램 작성
w: 가로
h: 세로 
.: 깨끗
*: 더러운칸 
x: 가구
o: 시작 위치 

*/
const int INF = 1e9;

// 격자 범위 체크를 위한 전역 w/h
int w, h;

// 4방향 이동 (하, 우, 상, 좌)
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool check(int r, int c) {
    return (0 <= r && r < h && 0 <= c && c < w);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (true) {
        cin >> w >> h;
        if (w == 0 && h == 0) break;

        // 격자 입력 (줄 단위로 받아 처리)
        vector<string> board(h);
        for (int i = 0; i < h; ++i) cin >> board[i];

        deque<pair<int,int>> points;

        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                if (board[r][c] == 'o') points.push_front({r,c});
                else if (board[r][c] == '*') points.push_back({r, c});
            }    
        }
        
        // 더러운 칸이 없으면 이동 0
        int N = points.size() -1 ;
        if (N == 0) {
            cout << 0 << '\n';
            continue;
        }

        // 모든 관심 지점에서 BFS를 수행해 dist 행렬 구성 (N+1 x N+1)
        vector<vector<int>> dist(N + 1, vector<int>(N + 1, INF));
        bool unreachable = false;

        for (int i = 0; i <= N; ++i) {
            // BFS: points[i]에서 모든 칸까지의 최단거리
            vector<vector<int>> dgrid(h, vector<int>(w, -1));
            queue<pair<int,int>> q;
            auto [sr, sc] = points[i];
            dgrid[sr][sc] = 0;
            q.push({sr, sc});

            while (!q.empty()) {
                auto cur = q.front(); q.pop();
                for (int dir = 0; dir < 4; ++dir) {
                    int nr = cur.X + dx[dir];
                    int nc = cur.Y + dy[dir];
                    if (!check(nr, nc)) continue;
                    if (board[nr][nc] == 'x') continue;      // 가구(벽)는 통과 불가
                    if (dgrid[nr][nc] != -1) continue;       // 이미 방문
                    dgrid[nr][nc] = dgrid[cur.X][cur.Y] + 1;
                    q.push({nr, nc});
                }
            }

            // 이 BFS 결과로부터 관심 지점들까지의 거리 채우기
            for (int j = 0; j <= N; ++j) {
                auto [tr, tc] = points[j];
                int d = dgrid[tr][tc];
                dist[i][j] = (d == -1 ? INF : d);
            }
        }

        // 시작점에서 어떤 더러운 칸으로도 못 가면 -1
        for (int j = 1; j <= N; ++j) {
            if (dist[0][j] >= INF) {
                unreachable = true;
                break;
            }
        }
        if (unreachable) {
            cout << -1 << '\n';
            continue;
        }

        // 비트마스크 DP: dp[mask][last]
        // mask: 방문한 더러운 칸 집합 (0..N-1)
        // last: 마지막으로 방문한 더러운 칸 인덱스 (0..N-1)
        vector<vector<int>> dp(1 << N, vector<int>(N, INF));

        // 초기화: 시작점 -> 각 더러운 칸
        for (int i = 0; i < N; ++i) {
            dp[1 << i][i] = dist[0][i + 1]; // points[0] -> points[i+1]
        }

        // 전이
        for (int mask = 0; mask < (1 << N); ++mask) {
            for (int i = 0; i < N; ++i) {
                if (!(mask & (1 << i))) continue;   // i가 방문 집합에 없으면 스킵
                int cur = dp[mask][i];
                if (cur >= INF) continue;

                for (int j = 0; j < N; ++j) {
                    if (mask & (1 << j)) continue;  // 이미 방문한 j는 스킵
                    int d = dist[i + 1][j + 1];     // points[i+1] -> points[j+1]
                    if (d >= INF) continue;         // 이동 불가
                    int new_mask = mask | (1 << j);
                    dp[new_mask][j] = min(dp[new_mask][j], cur + d);
                }
            }
        }

        // 정답: 모든 더러운 칸 방문 상태(full)에서 최소값
        int full = (1 << N) - 1;
        int ans = INF;
        for (int i = 0; i < N; ++i) {
            ans = min(ans, dp[full][i]);
        }
        cout << (ans >= INF ? -1 : ans) << '\n';
    }

    return 0;
}
