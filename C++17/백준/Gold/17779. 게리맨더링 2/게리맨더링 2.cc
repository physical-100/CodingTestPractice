#include <bits/stdc++.h>
using namespace std;
/*
5개의 구획으로 나누고 각 구역은 한가지에 속한다,
선거구는 적어도 하나의 구역을 포함 -> 선거구에 포함된 구역은 모두
연결
인접한 구역에서 선거구를 갈 수 있을 때 연결
중간에 통하는 인접한 구역은 0개 이상
선거구를 나누는 방법 => 기준점 x,y
경계의 길이 d1,d2
    1번 경계선: (x, y), (x+1, y-1), ..., (x+d1, y-d1)
    2번 경계선: (x, y), (x+1, y+1), ..., (x+d2, y+d2)
    3번 경계선: (x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
    4번 경계선: (x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
구역 r.c의 인구 A[r][c] == > 선거구의 인구 -> 각 구역의 인구를 합한값
인구가 가장 많은 선거구와 적은 선거구의 최솟값을 구해보자 ,
*/
int N;
int ans = 1e9;
int p[21][21];
int num_board[21][21];
int total_people = 0;

void solve(int x, int y, int d1, int d2) {
    // 1. 매번 보드를 0으로 초기화하고 경계선(5)만 그립니다.
    memset(num_board, 0, sizeof(num_board));
    
    for (int i = 0; i <= d1; i++) {
        num_board[x + i][y - i] = 5;
        num_board[x + d2 + i][y + d2 - i] = 5;
    }
    for (int i = 0; i <= d2; i++) {
        num_board[x + i][y + i] = 5;
        num_board[x + d1 + i][y - d1 + i] = 5;
    }

    int val[5] = {0, 0, 0, 0, 0};

    // 2. 1번 구역: (1, 1) 방향에서 내려오며 5를 만나면 중단
    for (int r = 1; r < x + d1; r++) {
        for (int c = 1; c <= y; c++) {
            if (num_board[r][c] == 5) break; 
            val[0] += p[r][c];
        }
    }

    // 3. 2번 구역: (1, N) 방향에서 내려오며 5를 만나면 중단
    for (int r = 1; r <= x + d2; r++) {
        for (int c = N; c > y; c--) {
            if (num_board[r][c] == 5) break;
            val[1] += p[r][c];
        }
    }

    // 4. 3번 구역: (N, 1) 방향에서 올라오며 5를 만나면 중단
    for (int r = x + d1; r <= N; r++) {
        for (int c = 1; c < y - d1 + d2; c++) {
            if (num_board[r][c] == 5) break;
            val[2] += p[r][c];
        }
    }

    // 5. 4번 구역: (N, N) 방향에서 올라오며 5를 만나면 중단
    for (int r = x + d2 + 1; r <= N; r++) {
        for (int c = N; c >= y - d1 + d2; c--) {
            if (num_board[r][c] == 5) break;
            val[3] += p[r][c];
        }
    }

    // 6. 5번 구역: 전체 인구 - (1+2+3+4번 합)
    // 마름모 내부와 경계선에 해당하는 모든 인구가 한 번에 계산됩니다.
    int sum_1234 = val[0] + val[1] + val[2] + val[3];
    val[4] = total_people - sum_1234;

    sort(val, val + 5);
    ans = min(ans, val[4] - val[0]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    if (!(cin >> N)) return 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> p[i][j];
            total_people += p[i][j];
        }
    }

    // i: x, j: y, z: d1, k: d2
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int z = 1; z <= N; z++) {
                for (int k = 1; k <= N; k++) {
                    // 문제의 제약 조건
                    if (i + z + k <= N && 1 <= j - z && j + k <= N) {
                        solve(i, j, z, k);
                    }
                }
            }
        }
    }

    cout << ans;
    return 0;
}