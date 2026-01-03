#include <bits/stdc++.h>
using namespace std ;
#define X first
#define Y second 
/*
r x c  격자  -> 미세먼지 양을 실시간으로 모니터링 하는 시스템 개발 
항상 1번 column에 설치 크기는 두행을 차지 
1초동안 하는 일 
    1. 미세먼지 확산 -> 모든 칸에서 동시 
        인접 4방향 확산 
        확산 되는 양 -> A_r,c/5  | 칸이 없으면 제외 
        A_r,c에 남은 미세먼지 양  = A_r,c - [A_r,c/5] * 확산 방향
    2. 공기 청정기 작동 
        바림이 불어 위쪽 바람 -> 반시계 방향 순환 
                아래쪽 바람 시계 방향 순환 
                청청기로 들어간 미세먼지는 모두 정화 
    공기 청정기가 있는 칸은 확산 x 
    
*/
int board[50][50];
int R,C,T;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};

int air_pos[2];
void spread() {
    // 1. 확산된 양을 임시로 저장할 배열
    int add_board[50][50] = {0,};

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            // 미세먼지가 있고, 공기청정기가 아닌 경우
            if (board[i][j] > 0) {
                int val = board[i][j] / 5;
                int count = 0;
                for (int dir = 0; dir < 4; dir++) {
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];
                    if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
                    if (board[nx][ny] == -1) continue;
                    
                    add_board[nx][ny] += val; // 주변 칸에 확산량 기록
                    count++;
                }
                board[i][j] -= (val * count); // 현재 칸에서 확산된 만큼 차감
            }
        }
    }

    // 2. 확산된 양을 원본 배열에 합침 (동시 확산 완성)
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            board[i][j] += add_board[i][j];
        }
    }
}
void upper_air() {
    int r = air_pos[0]; // 위쪽 공기청정기의 행 위치

    // 1. 왼쪽 벽면: 아래로 당기기 (0행부터 청정기 행까지)
    for (int i = r - 1; i > 0; i--)
        board[i][0] = board[i - 1][0];

    // 2. 천장면: 오른쪽에서 왼쪽으로 당기기
    for (int i = 0; i < C - 1; i++)
        board[0][i] = board[0][i + 1];

    // 3. 오른쪽 벽면: 위로 당기기
    for (int i = 0; i < r; i++)
        board[i][C - 1] = board[i + 1][C - 1];

    // 4. 공기청정기 수평 라인: 왼쪽에서 오른쪽으로 당기기
    for (int i = C - 1; i > 1; i--)
        board[r][i] = board[r][i - 1];

    // 5. 공기청정기에서 나가는 공기는 미세먼지 0
    board[r][1] = 0;
}
void lower_air() {
    int r = air_pos[1]; // 아래쪽 공기청정기의 행 위치

    // 1. 왼쪽 벽면: 위로 당기기 (아래쪽 공기청정기 행 + 1부터 바닥까지)
    for (int i = r + 1; i < R - 1; i++)
        board[i][0] = board[i + 1][0];

    // 2. 바닥면: 왼쪽으로 당기기
    for (int i = 0; i < C - 1; i++)
        board[R - 1][i] = board[R - 1][i + 1];

    // 3. 오른쪽 벽면: 아래로 당기기
    for (int i = R - 1; i > r; i--)
        board[i][C - 1] = board[i - 1][C - 1];

    // 4. 공기청정기 수평 라인: 오른쪽으로 당기기
    for (int i = C - 1; i > 1; i--)
        board[r][i] = board[r][i - 1];

    // 5. 공기청정기에서 바로 나가는 바람은 항상 깨끗한 공기(0)
    board[r][1] = 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> R>>C>>T ; 
    bool first_pos = false;
    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++){
            cin >> board[i][j];
            if(board[i][j]==-1 &&!first_pos ) { 
                air_pos[0] = i;
                air_pos[1] = i+1;
                first_pos = true;
            }   
        }
    while(T--){
        //확산
        vector<pair<int,int>> v ;
        for(int i=0;i<R;i++)
            for(int j=0;j<C;j++)
                if(board[i][j]>0) v.push_back({i,j});
        spread();
        //순환 
        upper_air();
        lower_air();
    }
        //count
    int cnt =0;
    for(int i=0;i<R;i++)
            for(int j=0;j<C;j++)
                if(board[i][j]>0) cnt += board[i][j];
    cout<< cnt ;
    return 0;
}