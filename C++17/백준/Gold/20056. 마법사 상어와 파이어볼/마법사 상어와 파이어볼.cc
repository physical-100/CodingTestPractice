#include <bits/stdc++.h>
using namespace std;
/*
파이어볼  M개 발사 -> 각자 위치에서 이동 대기 
각 파이어볼의 위치  , 질량 m_i , 방향 d_i , 속력 s_i
파이어볼 인접 8개의 칸 이동 -> 방향 정해져있음 
격자의 행과 열이 연결되있다 -> 반대쪽에서 다시 나타남 
연결 구현 
next_r=(r+(s×dr)(modN)+N)(modN)
next_c=(c+(s×dc)(modN)+N)(modN)

이동 
    1. 파이어볼이 자신의 방향, 속력으로 이동 
    2. 이동이 끝난뒤 2개이상의 파이어볼이 있을 때
        a. 같은 칸 -> 하나로 합쳐짐 
        b. 4개로 나누어짐 
        c. 나누어진 파이어볼의 질량 속력 방향 
            질량 :  합쳐진 파이어볼의 질량의 합 /5
            속력:  속력의 합 / 개수 
            방향이 모두 홀수 || 짝수 => 0,2,4,6 
            그렇지 않으면 1,3,5,7
        d. 질량이 0인 파이어볼은 소멸 
k번 이동한뒤 남아 있는 파이어볼 질량의 합을 구해보자 
*/
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int n, m, k;
vector<tuple<int,int,int>> board[51][51];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    while (m--) {
        int r, c, w, s, d;
        cin >> r >> c >> w >> s >> d;
        // 문제의 좌표는 1~N이므로 0~N-1로 보정
        board[r - 1][c - 1].push_back({w, s, d});
    }

    while (k--) {
        vector<tuple<int,int,int>>tmp_board[51][51];

        // 1. 모든 파이어볼 이동
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (board[r][c].empty()) continue;
                for (auto [w,s,d]: board[r][c]) {
                    // 음수 좌표 처리를 위해 +n을 반복하거나 파이썬 식 나머지 연산 활용
                    int nr = (r + (s * dr[d]) % n + n) % n;
                    int nc = (c + (s * dc[d]) % n + n) % n;
                    tmp_board[nr][nc].push_back({w,s,d});
                }
            }
        }

        // 2. 이동 후 2개 이상 모인 칸 처리 (분할 로직)
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                board[r][c].clear(); // 기존 board 비우기

                if (tmp_board[r][c].empty()) continue;

                if (tmp_board[r][c].size() == 1) {
                    board[r][c].push_back(tmp_board[r][c][0]);
                    continue;
                }

                // 2개 이상일 때 합치기
                int sum_m = 0, sum_s = 0;
                int cnt = tmp_board[r][c].size();
                bool even = false, odd = false;

                for (auto[w,s,d]: tmp_board[r][c]) {
                    sum_m += w;
                    sum_s += s;
                    if (d % 2 == 0) even = true;
                    else odd = true;
                }

                int next_m = sum_m / 5;
                int next_s = sum_s / cnt;

                if (next_m == 0) continue; // 질량 0이면 소멸 (board에 안 넣음)

                // 방향 결정 (모두 홀수거나 모두 짝수면 0,2,4,6 아니면 1,3,5,7)
                int start_d = (even && odd) ? 1 : 0; // 둘다 true  -> 1부터 시작 
                for (int i = 0; i < 4; i++) {
                    board[r][c].push_back({next_m, next_s, start_d + i * 2});
                }
            }
        }
    }

    // 최종 질량 합 계산
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (auto[w,s,d] : board[i][j]) ans += w;
        }
    }

    cout << ans;

    return 0;
}