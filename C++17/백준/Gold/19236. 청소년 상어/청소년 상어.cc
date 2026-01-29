#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
/*
한칸에 물고기가 한마리 존재 
각 물고기는 번호와 방향이 있다.
번호는 1<= x <=16
방향  = > 8 방향
0,0의 물고기를 먹고 0,0에 들어가게 된다. 
    방향은 0,0에 있던 물고기의 방향과 같음 . -> 물고기 이동 

번호가 작은 물고기 부터 순서대로 이동 
    한칸 이동 가능 -> 빈칸 , 다른 물고기가 있는 칸 
각 물고기는 방향이 이동할 수 있는 칸을 향할 때 까지 반시계 45도 회전 
    이동할 수 있는 칸이 없으면 이동 x 
    물고기가 다른 물고기가 있는 칸으로 이동을 할때는 서로의 위치를 바꾸는 방식 
물고기의 이동이 끝나면 상어가 이동 
    한번에 여러 칸 이동 가능 -> 물고기가 있는 칸으로 이동햇다면  그 칸의 물고기를 먹고
    해당 방향을 가짐 (지나가는 칸은 먹지 않음)
    물고기가 없는 칸으로는 이동 x  => 상어가 이동할 수 있는 칸이 없으면 집으로 이동 

상어의 이동 후 물고기가 이동 
상어가 먹을 수 있는 물고기 번호의 합의 최댓값을 구하자 
상어는 이동 방향중에 물고기가 있다면  경우의 수가 가능. 
*/

const int shark = -1;
int dx[8]= { -1,-1,0,1,1,1,0,-1};
int dy[8] = {0,-1,-1,-1,0,1,1,1};

int ans; 

//pair<int,int> shark_pos;

bool check(int r, int c){
    return(r>=0&&c>=0&&r<4&&c<4);
}

void func(pair<int,int> board[4][4],int r,int c,int total){
    
    pair<int,int> cur_board[4][4];
    //복사
    for(int i=0; i<4; i++) 
        for(int j=0; j<4; j++) 
            cur_board[i][j] = board[i][j];
    
    int eaten = cur_board[r][c].X;
    //상어 위치 
    int s_dir = cur_board[r][c].Y-1;
    total += eaten;
    ans =  max(ans,total);
    cur_board[r][c].X = shark; // 상어 표시 
    
    // 2. 물고기 이동
    for (int f = 1; f <= 16; f++) {
        int fx = -1, fy = -1;
        // 보드에서 직접 f번 물고기 찾기 (전역 변수 오염 방지)
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (cur_board[i][j].X == f) { fx = i; fy = j; break; }
            }
            if (fx != -1) break;
        }
        if (fx == -1) continue;

        int f_dir = cur_board[fx][fy].Y - 1;
        for (int d = 0; d < 8; d++) {
            int nd = (f_dir + d) % 8;
            int nx = fx + dx[nd];
            int ny = fy + dy[nd];

            // 경계 안이고 상어(-1)가 아니면 이동
            if (check(nx, ny) && cur_board[nx][ny].X != shark) {
                cur_board[fx][fy].Y = nd + 1; // 바뀐 방향 저장
                swap(cur_board[fx][fy], cur_board[nx][ny]);
                break;
            }
        }
    }
    
   // 4. 상어 이동 시도
    cur_board[r][c].X = 0; // 물고기 이동이 끝났으니 상어가 있던 자리는 빈칸
    for(int i=1; i<=3; i++) {
        int nr = r + dx[s_dir] * i;
        int nc = c + dy[s_dir] * i;

        if(check(nr, nc)) {
            if(cur_board[nr][nc].X > 0) { // 물고기가 있는 칸만 이동 가능
                func(cur_board, nr, nc, total);
            }
        } else break;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pair<int, int> board[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            int a,b;
            cin>> a>>b;
            board[i][j] = {a,b};
            //물고기를 순서대로 저장 
        }
    func(board,0,0,0);
    cout<<ans;
    return 0;
}