#include <bits/stdc++.h>
using namespace std ;
/*
파이어스톰을 얼음판에서 연습 
A[r][c] :  0 얼음이 없는 것 
시전시 단계 L 를 정함 

2^L크기로 나눠서 부분 격자를 시계 방향으로 90도 회전 
이후 얼음이 있는 칸 3이상의 칸과 인접해 있지 않은 칸은 얼음 양이 -1
Q 번 시전 후 
1.남아있는 얼음의 합 
2.남아있는 얼음 중 가장 큰 덩어리가 차지하는 칸의 개수 
두개 출력 
*/
int N, Q, bound;
int board[64][64];
int visited[64][64];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
int temp[64][64];

void func(int L) {
    int sz = (1 << L);
    memset(temp,0,sizeof(temp));
    if(L!=0){
            // 1. 부분 격자 회전
    for (int i = 0; i < bound; i += sz) {
        for (int j = 0; j < bound; j += sz) {
            for (int r = 0; r < sz; r++) {
                for (int c = 0; c < sz; c++) {
                    temp[i + c][j + sz - 1 - r] = board[i + r][j + c];
                }
            }
        }
    }
    memcpy(board, temp, sizeof(board));
    }
    
    // 2. 얼음 녹이기
   for(int r = 0; r < bound; r++) {
       for(int c = 0; c < bound; c++) {
           if(board[r][c] <= 0) 
               continue; // 이미 얼음이 없으면 패스
           int cnt = 0;
           for(int dir = 0; dir < 4; dir++) {
               int nr = r + dx[dir], nc = c + dy[dir];
               if(nr < 0 || nc < 0 || nr >= bound || nc >= bound) continue;
               if(board[nr][nc] > 0) cnt++;
            }
           
        if(cnt < 3) 
            temp[r][c] = (board[r][c]>1)?board[r][c] - 1 : 0; 
        else temp[r][c] = board[r][c];
        }

    }
    memcpy(board, temp, sizeof(board)); // 최종 결과를 board에 반영
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    bound = (1 << N);
    for (int i = 0; i < bound; i++)
        for (int j = 0; j < bound; j++) cin >> board[i][j];

    while (Q--) {
        int L; cin >> L;
        func(L);
    }

    // 결과 계산 (BFS)
    long long total_ice = 0;
    int max_area = 0;
    for (int i = 0; i < bound; i++) {
        for (int j = 0; j < bound; j++) {
            total_ice += board[i][j];
            if (board[i][j] > 0 && !visited[i][j]) {
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = 1;
                int cnt = 0;
                while (!q.empty()) {
                    auto cur = q.front(); q.pop();
                    cnt++;
                    for (int dir = 0; dir < 4; dir++) {
                        int nr = cur.first + dx[dir], nc = cur.second + dy[dir];
                        if (nr < 0 || nc < 0 || nr >= bound || nc >= bound) continue;
                        if (board[nr][nc] > 0 && !visited[nr][nc]) {
                            visited[nr][nc] = 1;
                            q.push({nr, nc});
                        }
                    }
                }
                if(cnt ==1) cnt = 0;
                max_area = max(max_area, cnt);
            }
        }
    }
    cout << total_ice << "\n" << max_area << "\n";
    return 0;
}