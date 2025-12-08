
#include <bits/stdc++.h>
using namespace std;

/*
주사위가 이동했을 때마다 상단에 쓰여있는 값을 구하는 프로그램 작성
지도의 좌표 r(행), c(열)
놓여있는 곳의 좌표 x,y
가장 처음에 주사위의 모든 면에 0이 써져있다
이동한 칸에 쓰여있는 수가 0이면 주사위 바닥면의 수가 복사된다.
0이 아닌 경우에는 칸에 쓰여있는 수가 주사위 바닥면으로 복사되며 칸의 수는 0이 된다.
바깥으로 나가는 명령은 무시
지도의 수  0~9
동 -> 1, 서 -> 2, 북 -> 3, 남 -> 4
*/

int board[21][21];
int N, M, x, y, k;
vector<int> dir;
int cur_x, cur_y;

struct Dice {
    // 면 값 (초기엔 모두 0)
    int T = 0; // Top
    int B = 0; // Bottom
    int N = 0; // North
    int S = 0; // South
    int W = 0; // West (Left)
    int E = 0; // East (Right)

    void rollEast() { // 동: 왼쪽(W)가 위로, 오른쪽(E)가 아래로
        int t = T;
        T = W;
        W = B;
        B = E;
        E = t;
        // N, S unchanged
    }
    void rollWest() { // 서: 오른쪽(E)가 위로, 왼쪽(W)가 아래로
        int t = T;
        T = E;
        E = B;
        B = W;
        W = t;
        // N, S unchanged
    }
    void rollNorth() { // 북: 남쪽(S)가 위로, 북쪽(N)가 아래로
        int t = T;
        T = S;
        S = B;
        B = N;
        N = t;
        // W, E unchanged
    }
    void rollSouth() { // 남: 북쪽(N)가 위로, 남쪽(S)가 아래로
        int t = T;
        T = N;
        N = B;
        B = S;
        S = t;
        // W, E unchanged
    }
};

Dice dice; // 전역 주사위 객체

bool ispossible(int cmd) {
    // 범위를 확인하여 될 때만 현재 좌표 갱신
    int tmp_y = cur_y;
    int tmp_x = cur_x;
    switch (cmd) {
        case 1: // 동
            tmp_y += 1;
            break;
        case 2: // 서
            tmp_y -= 1;
            break;
        case 3: // 북
            tmp_x -= 1;
            break;
        case 4: // 남
            tmp_x += 1;
            break;
        default:
            return false;
    }

    if (tmp_x >= 0 && tmp_x < N && tmp_y >= 0 && tmp_y < M) {
        cur_x = tmp_x;
        cur_y = tmp_y;
        return true;
    } else {
        return false;
    }
}

// 주사위를 굴리고, 보드/주사위 바닥을 규칙에 맞게 갱신한 뒤 Top을 출력
void dice_func(int cmd) {
    // 1) 방향에 따라 주사위 굴리기
    if (cmd == 1) dice.rollEast();
    else if (cmd == 2) dice.rollWest();
    else if (cmd == 3) dice.rollNorth();
    else if (cmd == 4) dice.rollSouth();

    // 2) 현재 칸과 주사위 바닥(B) 상호작용
    if (board[cur_x][cur_y] == 0) {
        board[cur_x][cur_y] = dice.B;
    } else {
        dice.B = board[cur_x][cur_y];
        board[cur_x][cur_y] = 0;
    }

    // 3) 윗면 출력
    cout << dice.T << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> x >> y >> k;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> board[i][j];

    dir.reserve(k);
    for (int i = 0; i < k; ++i) {
        int m;
        cin >> m;
        dir.push_back(m);
    }

    cur_x = x;
    cur_y = y;

    for (auto cmd : dir) {
        if (!ispossible(cmd)) continue; // 바깥 이동은 무시
        dice_func(cmd);
    }
    return 0;
}
