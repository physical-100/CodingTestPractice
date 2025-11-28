#include <bits/stdc++.h>
using namespace std;

/*
서로가 서로를 잡을 수 없는 위치에 놓을 수 있는 비숍의 최대 개수. 
놓을 수 있는 곳 1 아닌곳 0
비숍이 이동할 수 있는 위치 ∣x1−x2∣=∣y1−y2∣
우대각 방향 : col - row의 값이 같음
좌대각 방향 : cor + row의 값이 같음
시간을 줄이기 위해 2개로 나누어 계산.
*/
int n;
int board[11][11];
int max_black, max_white;
vector<pair<int,int>> v[2]; //각각을 ㅈ
bool used[2][22]; 

void Bishop(vector<pair<int,int>> &cells,int idx,int &result , int count) {
    if (idx == cells.size()) {
        result = max(result, count);
        return;
    }

    int x = cells[idx].first;
    int y = cells[idx].second;
    int s = x + y;           // 좌대각
    int d = x - y + 10;      // 우대각 (offset 10)

    // 1. 현재 위치에 비숍을 놓는 경우
    if (!used[0][s] && !used[1][d]) {
        used[0][s] = true;
        used[1][d] = true;
        Bishop(cells,idx+1,result,count+1);
        
        used[0][s] = false;
        used[1][d] = false;
    }

    // 2. 현재 위치에 비숍을 놓지 않는 경우
    Bishop(cells,idx + 1,result,count);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            if (board[i][j]) {
                //홀수칸 짝수 칸으로 나누어 저장 
                //연산량을 줄이기 위함
                if((i+j)%2==0)v[0].push_back({i, j});
                else v[1].push_back({i,j});
            }
        }
    }

    Bishop(v[0],0,max_black,0);
    Bishop(v[1],0,max_white,0);
    cout << max_black+max_white;
    return 0;
}
