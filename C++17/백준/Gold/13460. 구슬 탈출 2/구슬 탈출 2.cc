#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second 
/*
보드에 빨간 구슬과 파란 구슬을 하나씩 넣은 다음 빨간 구슬을 구멍을 통해 빼내는 게임 
가장 바깥 행 과 열은 모두 막혀있음 
보드에는 구멍이 하나 있다 . 
목표 : 구멍을 통해 빨간 구슬을 빼내는 것 
-> 파란 구슬이 구멍에 들어가면 실패, 동시에 구멍에 빠져도 실패 
더이상 구슬이 움직이지 않으면 기울이기 stop.  
동작 -> 기울이기  왼쪽 위쪽 , 아래 
각각 동작에서 공은 동시에 움직인다 .

최소 몇번만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하라 

.: 빈칸
#: 벽 or 장애물 
0: 구멍
R: 빨간 구슬 
B: 파랑 구슬
배열의 최대 크기 10x10 
*/

int MX = 10; 
char board[10][10];
int dist[10][10][10][10]; //r 좌표(r_X, r_Y) , b 좌표(b_X, b_Y)
int dx[4] = {-1,1,0,0}; // 위 , 아래 , 왼,오 
int dy[4] = {0,0,-1,1};
int  N,M;

pair<int,int> hole, r, b; 

int get_mintime(){
    queue<tuple<int,int,int,int>> q;
    q.push({r.X,r.Y,b.X , b.Y });
    dist[r.X][r.Y][b.X][b.Y] = 0;
    while(!q.empty()){
        auto [r_x,r_y,b_x,b_y] = q.front(); q.pop();
        int cnt =  dist[r_x][r_y][b_x][b_y];
        if (cnt >=10) return -1;
        for(int dir=0;dir <4; dir++){
            //4방향 기울이기 
            int nx_r = r_x;
            int ny_r = r_y;
            int nx_b = b_x;
            int ny_b = b_y;
            //기울이기 이동 
            // 블루 부터 이동  -> 블루가 탈출하면 실패이므로 
            while(board[nx_b + dx[dir]][ny_b + dy[dir]]=='.'){
               // 빈칸이라면 이동한다. 
                //앞에 구멍이 있다면 구멍 전에 멈춤 
                nx_b += dx[dir];
                ny_b += dy [dir];
            }
            //파란 구슬이 들어간 경우 넘어감 
            if(board[nx_b + dx[dir]][ny_b + dy[dir]]=='O') continue;

             while(board[nx_r + dx[dir]][ny_r + dy[dir]]=='.'){
               // 빈칸이라면 이동한다. 
                //앞에 구멍이 있다면 구멍 전에 멈춤 
                nx_r += dx[dir];
                ny_r += dy [dir];
            }
             if(board[nx_r + dx[dir]][ny_r + dy[dir]]=='O') return cnt +1;
            // 구슬이 겹친 경우 늦게 출발한 구슬을 한칸 뒤로 이동 
            if(nx_r ==nx_b && ny_r ==ny_b){
                if(dir ==0) //위
                    r_x > b_x ? nx_r ++: nx_b++;
                else if(dir ==1) //아래
                    r_x > b_x ? nx_b-- : nx_r--;
                else if(dir ==2) //왼 
                    r_y > b_y ? ny_r++ : ny_b++;
                else //오 
                    r_y> b_y ? ny_b-- : ny_r --;
            }

            if(dist[nx_r][ny_r][nx_b][ny_b]!=-1) continue;
            dist[nx_r][ny_r][nx_b][ny_b] = cnt+1;
            q.push({nx_r,ny_r,nx_b,ny_b});
        }
    }  
    return -1;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> N>>M;
    memset(dist , -1, sizeof(dist));
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++){
            cin >> board[i][j];
            if(board[i][j]== 'O') hole = {i,j};
            else if(board[i][j]=='R') {
                r = {i,j};
                board[i][j] = '.';
            }
            else if(board[i][j]=='B'){
                b = {i,j};
                board[i][j] = '.'; //빈칸 처리 
            } 
        }
    cout << get_mintime();
    return 0;
}