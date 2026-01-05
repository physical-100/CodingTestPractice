#include <bits/stdc++.h>
using namespace std ;
/*
상어 각 칸 최대 한마리 -> 크기와 속도를 가짐 
낚시왕의 초기 위치 1번 열의 한칸 왼쪽  
가장 오른쪽 열의 오른쪽 칸이 이동하면 이동을 멈춤 
과정 
    1. 오른쪽으로 한칸 이동 
    2. 낚시왕이 있는 열에서 땅과 가장 가까운 상어를 잡음 
    3. 상어가 이동 
        상어의 이동 -> 격자의 경계를 넘는 경우 방향을 반대로 바꿔서 이동 
상어가 이동을 마친 후에는 한칸에 두마리 이상의 상어가 있을 수 있다 .
이때는 크기가 가장 큰 상어가 나머지 상어를 모두 잡아 먹는다 .

낚시왕이 잡은 상어의 크기의 합을 구하라 
//상어의 크기는 다 다르다. 

*/
struct Shark {
    int s, d, z;
};

// 1:위, 2:아래, 3:오른쪽, 4:왼쪽 (문제 기준 방향)
int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

int R, C, M;
Shark board[102][102]; // 현재 칸에 있는 상어 정보
vector<tuple<int, int, int, int, int>> sharks; // 상어 리스트 (r, c, s, d, z)

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R >> C >> M;

    for (int i = 0; i < M; i++) {
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        sharks.push_back({r, c, s, d, z});
        board[r][c] = {s, d, z};
    }

    int total_cnt = 0;
    for (int fisher = 1; fisher <= C; fisher++) {
        // 1. 상어 잡기
        int caught_z = -1; // 잡힌 상어의 크기 기억 
        for (int r = 1; r <= R; r++) {
            if (board[r][fisher].z > 0) {
                total_cnt += board[r][fisher].z;
                caught_z = board[r][fisher].z; // 잡힌 상어의 크기 기억
                board[r][fisher] = {0, 0, 0};  // 보드에서 제거
                break;
            }
        }

        // 2. 상어 이동 준비
        // 이동 후 결과를 담을 임시 보드 (초기화 필수)
        Shark next_board[102][102];
        for(int r=1; r<=R; r++) 
            for(int c=1; c<=C; c++) 
                next_board[r][c] = {0,0,0};

        vector<tuple<int, int, int, int, int>> next_sharks;

        for (auto& shark : sharks) {
            auto [r, c, s, d, z] = shark;

            // 낚시꾼에게 잡힌 상어
            if (z == caught_z) continue; 
            //상어에게 잡힌 상어 
            if (board[r][c].z != z) continue; 

            int cur_r = r, cur_c = c, cur_d = d;
            
            // 속력 최적화 (제자리로 돌아오는 주기 계산)
            int move = s;
            if (cur_d <= 2) move %= ((R - 1) * 2);
            else move %= ((C - 1) * 2);

            while (move--) {
                int nr = cur_r + dx[cur_d];
                int nc = cur_c + dy[cur_d];

                if (nr < 1 || nr > R || nc < 1 || nc > C) {
                    // 방향 반전 (1<->2, 3<->4)
                    if (cur_d == 1) cur_d = 2;
                    else if (cur_d == 2) cur_d = 1;
                    else if (cur_d == 3) cur_d = 4;
                    else if (cur_d == 4) cur_d = 3;
                    nr = cur_r + dx[cur_d];
                    nc = cur_c + dy[cur_d];
                }
                cur_r = nr; cur_c = nc;
            }

            // 3. 이동을 마친 후 겹침 처리 (큰 놈이 먹음)
            if (next_board[cur_r][cur_c].z < z) {
                next_board[cur_r][cur_c] = {s, cur_d, z};
            }
        }

        // 4. 다음 턴을 위해 리스트와 보드 갱신
        sharks.clear();
        for (int r = 1; r <= R; r++) {
            for (int c = 1; c <= C; c++) {
                board[r][c] = next_board[r][c];
                if (board[r][c].z > 0) {
                    sharks.push_back({r, c, board[r][c].s, board[r][c].d, board[r][c].z});
                }
            }
        }
    }

    cout << total_cnt;
    return 0;
}