#include <bits/stdc++.h>
using namespace std;

/*
색종이를 10 x10 인 종이 위에 붙이려고 한다 
0이 적힌 칸에는 색 종이가 있으면 안된다 
색종이는 경계 밖으로 나가서는 안되고 겹쳐도 안댄다
1이 적힌 모든 칸을 붙이는데 필요한 색종이의 최소 개수를 구해보자 .

모두 덮는 것이 불가능한 경우 -1을 출력한다. 

1,2,3,4,5의 크기를 지닌 색종이가 각 5개 

*/
int board[10][10];
int paper[6] = {0, 5, 5, 5, 5, 5}; 
int ans = 1e9; 

// (r, c)에 size 크기의 색종이를 붙일 수 있는지 확인
bool check(int r, int c, int sz) {
    if (r + sz > 10 || c + sz > 10) return false;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (!board[r + i][c + j]) return false;
        }
    }
    return true;
}

// 색종이를 붙이거나(state=0) 떼는(state=1) 함수
void attach(int r, int c, int sz, int state) {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            board[r + i][c + j] = state;
        }
    }
}

void dfs(int r, int c, int cnt) {
    // 현재 찾은 최솟값보다 값이 크면 back.
    if (cnt >= ans) return;

    // 행이 끝나면 다음 행으로
    if (c == 10) {
        dfs(r + 1, 0, cnt);
        return;
    }

    // 모든 칸을 다 확인했으면(성공) 최솟값 갱신
    if (r == 10) {
        ans = min(ans, cnt);
        return;
    }

    // 0인 칸은 그냥 넘어감
    if (board[r][c] == 0) {
        dfs(r, c + 1, cnt);
        return;
    }

    // 1인 칸을 만나면, 큰 색종이(5)부터 작은 색종이(1)까지 시도
    for (int i = 5; i > 0; i--) {
        if (paper[i] > 0 && check(r, c, i)) {
            attach(r, c,i, 0); // 붙임 (0으로 만듦)
            paper[i]--;
            
            dfs(r, c + 1, cnt + 1); // 다음 칸으로 이동
            
            paper[i]++;         // 원상복구 (백트래킹)
            attach(r, c, i, 1); // 뗌 (1로 되돌림)
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            cin >> board[i][j];

    dfs(0, 0, 0);

    if (ans == 1e9) cout << -1;
    else cout << ans;

    return 0;
}