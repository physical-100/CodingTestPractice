#include <bits/stdc++.h>
using namespace std;
/*
집의 각각의 칸은 빈칸이거나 벽 

회전 3가지 방향 
 -
 | 
 \  
 파이프는 밀어서 이동 (단 벽을 긁으면 안 된다)
 밀면서 회전 가능  (45도 )
 가로 세로의 경우 2가지
 대각 -> 3가지 경우의 수 가능 
 가장 처음 (1,1) , (1,2) - 방향 

 파이프의 한쪽 끝을 (N,N) 으로 이동시키는 방법의 개수를 구해보자 
 방법은 항상 int 범위 
 
*/
int N ; 
int board[17][17];
int ans; 

int dp[17][17][3];


void func(int r, int c , int dir);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            cin >> board[i][j];
        }
    }
#if(0) //DP

    //초기화 -> 나머지는  0으로 초기화 되어있음 
    //  0 : -  1: | 2: \
    dp[1][2][0] = 1;
    // 이동마다 비어 있어야하는 칸의 개수가 다르다 
    for(int i =0;i<=N)
    
    
    cout<< max(dp[N][N] , dp[N][N]+3);
    return 0;
}
#else  //back Traking
    if (board[N][N] == 1) { // 목적지가 벽이면 갈 수 없음
        cout << 0 << "\n";
        return 0;
    }
    func(1,2,0);
    cout << ans ;
    return 0;
}

void func(int r, int c, int dir) {
    if (r == N && c == N) {
        ans++; // 목적지 도달 시 카운트 증가
        return;
    }

    // 1. 가로로 이동 (현재 가로(0)거나 대각선(2)일 때 가능)
    if (dir == 0 || dir == 2) {
        if (c + 1 <= N && board[r][c + 1] == 0) {
            func(r, c + 1, 0);
        }
    }

    // 2. 세로로 이동 (현재 세로(1)거나 대각선(2)일 때 가능)
    if (dir == 1 || dir == 2) {
        if (r + 1 <= N && board[r + 1][c] == 0) {
            func(r + 1, c, 1);
        }
    }

    // 3. 대각선으로 이동 (항상 가능하지만 3칸 체크 필수)
    if (r + 1 <= N && c + 1 <= N) {
        if (board[r + 1][c] == 0 && board[r][c + 1] == 0 && board[r + 1][c + 1] == 0) {
            func(r + 1, c + 1, 2);
        }
    }
}
#endif